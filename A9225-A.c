#include <HT66L2540A.H>
//----------------------------------------------------------------------------
// Name     : A9225-A.c
// Purpose  : I2C Driver for A9225 / BC7161 NFC Tag
// Note(s)  : 1. Fixed Push-Pull collision (True Open-Drain implementation)
//            2. Added Clock Stretching detection
//            3. Added 3-retry mechanism for NACK handling
//----------------------------------------------------------------------------
#include "SW_Lib/HT8_Type.h"
#include "A9225-A.h"
#include "sys_tick.h"

volatile bit NFC_ActiveSts;
volatile bit NFC_RdCmdFinish;
volatile bit NFC_WrCmdFinish;
volatile bit NFC_WrMemFinish;

/* Buffers for 64-byte SRAM data (16 bytes per block) */
u8 g_SRAM_Data_1[16];
u8 g_SRAM_Data_2[16];
u8 g_SRAM_Data_3[16];
u8 g_SRAM_Data_4[16];

#define A9225A_IIC_WRITE_DADDR  (A9225_DEVICE_ADDR << 1)
#define A9225A_IIC_READ_DADDR   ((A9225_DEVICE_ADDR << 1) | 0x01)

/* =========================================================================
 * CRITICAL FIX: True Open-Drain Emulation
 * To drive High: Set direction to INPUT (let external pull-up handle it).
 * To drive Low: Set data to 0, then set direction to OUTPUT.
 * =========================================================================*/
#define A9225A_IIC_SCL_HIGH()   { A9225A_SCLDIR = INPUT; }
#define A9225A_IIC_SCL_LOW()    { A9225A_SCL = 0; A9225A_SCLDIR = OUTPUT; }
#define A9225A_IIC_SDA_HIGH()   { A9225A_SDADIR = INPUT; }
#define A9225A_IIC_SDA_LOW()    { A9225A_SDA = 0; A9225A_SDADIR = OUTPUT; }
#define A9225A_IIC_SDA_IN()     (A9225A_SDA)
#define A9225A_IIC_SCL_IN()     (A9225A_SCL)

extern void DelayXmSec(u8 xs);

/**
 * @brief  Initialize MCU & A9225A I2C Interface.
 *         Releases the bus to High (Input mode).
 * @param  None
 * @retval None
 */
void A9225A_InterfaceConfigure(void)
{
    A9225A_IIC_SDA_HIGH();
    A9225A_IIC_SCL_HIGH();
}

/**
 * @brief  Generate I2C Start Condition.
 * @param  None
 * @retval None
 */
void A9225A_IIC_StartBit(void)
{
    A9225A_IIC_SDA_HIGH();
    A9225A_IIC_SCL_HIGH();
    GCC_DELAY(IIC_SPEED);
    A9225A_IIC_SDA_LOW();
    GCC_DELAY(IIC_SPEED);
    A9225A_IIC_SCL_LOW();
}

/**
 * @brief  Generate I2C Stop Condition.
 * @param  None
 * @retval None
 */
void A9225A_IIC_StopBit(void)
{
    A9225A_IIC_SCL_LOW();
    GCC_DELAY(IIC_SPEED);
    A9225A_IIC_SDA_LOW();
    GCC_DELAY(IIC_SPEED);
    
    A9225A_IIC_SCL_HIGH();
    while (A9225A_IIC_SCL_IN() == 0) { GCC_CLRWDT(); } /* Wait for Clock Stretching */
    GCC_DELAY(IIC_SPEED);
    
    A9225A_IIC_SDA_HIGH();
    GCC_DELAY(IIC_SPEED);
}

/**
 * @brief  Output one byte of data to the I2C bus and read the ACK bit.
 * @param  da: Data byte to transmit.
 * @retval u8: TRUE(1) if ACK received, FALSE(0) if NACK received.
 */
u8 A9225A_IIC_DataOutput(u8 da)
{
    u8 i;
    u8 ack;
    
    A9225A_IIC_SCL_LOW();
    for (i = 0; i < 8; i++)
    {
        if (da & 0x80) {
            A9225A_IIC_SDA_HIGH();
        } else {
            A9225A_IIC_SDA_LOW();
        }
        GCC_DELAY(IIC_SPEED);
        
        A9225A_IIC_SCL_HIGH();
        while (A9225A_IIC_SCL_IN() == 0) { GCC_CLRWDT(); } /* Wait for Clock Stretching */
        
        da <<= 1;
        GCC_DELAY(IIC_SPEED);
        A9225A_IIC_SCL_LOW();
    }
    
    /* Release SDA to input to read ACK */
    A9225A_IIC_SDA_HIGH(); 
    GCC_DELAY(IIC_SPEED);
    A9225A_IIC_SCL_HIGH();
    while (A9225A_IIC_SCL_IN() == 0) { GCC_CLRWDT(); } /* Wait for Clock Stretching */
    GCC_DELAY(IIC_SPEED);
    
    /* Check ACK/NACK status: SDA low means ACK */
    ack = A9225A_IIC_SDA_IN() ? FALSE : TRUE;
    
    A9225A_IIC_SCL_LOW();
    GCC_DELAY(IIC_SPEED);
    
    return ack;
}

/**
 * @brief  Read one byte of data from the I2C bus and send ACK/NACK.
 * @param  ack: TRUE(1) to send ACK, FALSE(0) to send NACK.
 * @retval u8: Received data byte.
 */
u8 A9225A_IIC_DataInput(u8 ack)
{
    u8 i, da;
    da = 0;
    
    A9225A_IIC_SDA_HIGH(); /* Release SDA to input to receive data */
    
    for (i = 0; i < 8; i++)
    {
        GCC_DELAY(IIC_SPEED);
        da <<= 1;
        
        A9225A_IIC_SCL_HIGH();
        while (A9225A_IIC_SCL_IN() == 0) { GCC_CLRWDT(); } /* Wait for Clock Stretching */
        GCC_DELAY(IIC_SPEED);
        
        if (A9225A_IIC_SDA_IN()) 
        {
            da |= 0x01;
        }
        A9225A_IIC_SCL_LOW();
    }
    
    /* Send ACK/NACK */
    if (ack) {
        A9225A_IIC_SDA_LOW();  /* Send ACK (Pull Low) */
    } else {
        A9225A_IIC_SDA_HIGH(); /* Send NACK (Release High) */
    }
    
    GCC_DELAY(IIC_SPEED);
    A9225A_IIC_SCL_HIGH();
    while (A9225A_IIC_SCL_IN() == 0) { GCC_CLRWDT(); } /* Wait for Clock Stretching */
    GCC_DELAY(IIC_SPEED);
    
    A9225A_IIC_SCL_LOW();
    GCC_DELAY(IIC_SPEED);
    
    return da;
}

/**
 * @brief  Read register from A9225A with a 3-retry mechanism.
 * @param  MEMadr: Memory address.
 * @param  REGadr: Register address.
 * @param  rval: Pointer to store the read value.
 * @retval u8: TRUE(1) if successful, FALSE(0) if failed after 3 retries.
 */
u8 A9225A_RegisterRead(u8 MEMadr, u8 REGadr, u8 *rval)
{
    u8 ack = FALSE;
    u8 retry = 3;

    while (retry > 0)
    {
        A9225A_IIC_StartBit();
        ack = A9225A_IIC_DataOutput(A9225A_IIC_WRITE_DADDR);
        if (ack)
        {
            ack = A9225A_IIC_DataOutput(MEMadr);    /* Write memory address */
            if (ack)
            {
                ack = A9225A_IIC_DataOutput(REGadr); /* Write register address */
            }
            
            A9225A_IIC_StopBit();
            
            if (ack)
            {
                A9225A_IIC_StartBit();              /* IIC restart bit for read */
                ack = A9225A_IIC_DataOutput(A9225A_IIC_READ_DADDR);
                if (ack)
                {
                    *rval = A9225A_IIC_DataInput(FALSE);
                }
            }
        }
        
        A9225A_IIC_StopBit(); /* Ensure bus is released */
        
        if (ack)
        {
            break; /* Success, exit retry loop */
        }
        
        retry--;
        GCC_DELAY(100); /* Short delay before the next retry */
    }
    return ack;
}

/**
 * @brief  Read a 16-byte memory block from A9225A with a 3-retry mechanism.
 * @param  adr: Memory start address.
 * @param  rval: Pointer to the buffer to store read data.
 * @retval u8: TRUE(1) if successful, FALSE(0) if failed after 3 retries.
 */
u8 A9225A_MemoryRead(u8 adr, u8 *rval)
{
    u8 ack = FALSE;
    u8 leng;
    u8 retry = 3;
    u8 *ptr;

    while (retry > 0)
    {
        leng = 16;     /* Reset length for each retry */
        ptr = rval;    /* Reset pointer for each retry */
        
        A9225A_IIC_StartBit();           /* IIC start bit */
        ack = A9225A_IIC_DataOutput(A9225A_IIC_WRITE_DADDR);
        if (ack)
        {
            ack = A9225A_IIC_DataOutput(adr); /* Write register address */
            A9225A_IIC_StopBit();
            
            if (ack)
            {
                A9225A_IIC_StartBit();        /* IIC restart bit for read */
                ack = A9225A_IIC_DataOutput(A9225A_IIC_READ_DADDR);
                if (ack)
                {
                    for (; leng > 1; leng--)
                    {
                        *ptr = A9225A_IIC_DataInput(TRUE);
                        ptr++;
                    }
                    *ptr = A9225A_IIC_DataInput(FALSE);
                }
            }
        }
        
        A9225A_IIC_StopBit(); /* Ensure bus is released */
        
        if (ack)
        {
            break; /* Success, exit retry loop */
        }
        
        retry--;
        GCC_DELAY(100); /* Short delay before the next retry */
    }
    return ack;
}

/**
 * @brief  Write data to A9225A register with a 3-retry mechanism.
 * @param  MEMadr: Memory address.
 * @param  REGadr: Register address.
 * @param  MASK: Bit mask for the operation.
 * @param  val: Data to write.
 * @retval None
 */
void A9225A_RegisterWrite(u8 MEMadr, u8 REGadr, u8 MASK, u8 val)
{
    u8 ack = FALSE;
    u8 retry = 3;

    while (retry > 0)
    {
        A9225A_IIC_StartBit();           /* IIC start bit */
        ack = A9225A_IIC_DataOutput(A9225A_IIC_WRITE_DADDR);
        if (ack)
        {
            ack = A9225A_IIC_DataOutput(MEMadr);    /* Write memory address */
            if (ack)
            {
                ack = A9225A_IIC_DataOutput(REGadr);  /* Write register address */
                if (ack)
                {
                    ack = A9225A_IIC_DataOutput(MASK);  /* Write mask */
                    if (ack)
                    {
                        ack = A9225A_IIC_DataOutput(val); /* Write data */
                    }
                }
            }
        }
        
        A9225A_IIC_StopBit(); /* Ensure bus is released */
        
        if (ack)
        {
            break; /* Success, exit retry loop */
        }
        
        retry--;
        GCC_DELAY(100); /* Short delay before the next retry */
    }
}

/**
 * @brief  Write a 16-byte memory block to A9225A with a 3-retry mechanism.
 * @param  adr: Memory start address.
 * @param  val: Pointer to the write data array.
 * @retval u8: TRUE(1) if successful, FALSE(0) if failed after 3 retries.
 */
u8 A9225A_MemoryWrite(u8 adr, u8 *val)
{
    u8 ack = FALSE;
    u8 leng;
    u8 retry = 3;
    u8 *ptr;

    while (retry > 0)
    {
        leng = 16;    /* Reset length for each retry */
        ptr = val;    /* Reset pointer for each retry */
        
        A9225A_IIC_StartBit();           /* IIC start bit */
        ack = A9225A_IIC_DataOutput(A9225A_IIC_WRITE_DADDR);
        if (ack)
        {
            ack = A9225A_IIC_DataOutput(adr);    /* Write register address */
            while (ack && (leng > 0))
            {
                ack = A9225A_IIC_DataOutput(*ptr);
                ptr++;
                leng--;
            }
        }
        
        A9225A_IIC_StopBit(); /* Ensure bus is released */
        
        if (ack)
        {
            break; /* Success, exit retry loop */
        }
        
        retry--;
        GCC_DELAY(100); /* Short delay before the next retry */
    }
    return ack;
}

/**
 * @brief  Initialize NFC Tag Pass-Through mode and clear FD pin deadlock.
 * @note   This safely bypasses the SRAM arbitration lock to perform a dummy read,
 *         ensuring the FD pin is released to High before entering HALT mode.
 * @retval None
 */
void NFC_Tag_PassThrough_Init(void)
{
    u8 dummy_buf[16];
    
    A9225A_RegisterWrite(0xED, 0x01, 0x40, 0x40);

    /* 1. Force SRAM ownership to I2C side (Disable PTHRU, set DIR to I2C) */
    A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x01);
    
    /* Short delay for internal Tag state machine switching */
    SysTick_DelayMs(10); 

    /* 2. Dummy read the last SRAM block (0xFB) to force FD pin release */
    /* Because ownership is now I2C, this will ACK and read successfully */
    A9225A_MemoryRead(0xFB, dummy_buf);

    /* 3. Hand SRAM ownership back to NFC side and enable Pass-Through */
    /* 0x7D = PTHRU_ON | FD_OFF(11b) | FD_ON(11b) | TRANSFER_DIR(NFC->I2C) */
    A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x7D);
}

/**
 * @brief  Process incoming NFC SRAM data via Software I2C.
 * @retval None
 */
void Process_NFC_Data(void)
{
    if (_pa3 == 0) 
    {
        GCC_CLRWDT();

        /* Step 1: Switch SRAM reading direction to I2C */
        A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x01);
        SysTick_DelayMs(5); 

        /* Step 2: Fetch 64 bytes payload from 0xF8 to 0xFB */
        A9225A_MemoryRead(0xF8, g_SRAM_Data_1);
        A9225A_MemoryRead(0xF9, g_SRAM_Data_2);
        A9225A_MemoryRead(0xFA, g_SRAM_Data_3);
        A9225A_MemoryRead(0xFB, g_SRAM_Data_4);

        /* Step 3: Switch SRAM reading direction back to NFC */
        A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x7D);

        /* Step 4: Add your custom payload parsing logic here */
    }
}