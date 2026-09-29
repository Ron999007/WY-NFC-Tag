#ifndef _A9225A_H_
#define _A9225A_H_

#include "typedef.h"

#define A9225_DEVICE_ADDR  0x55
#define IIC_SPEED 1			
//-----------------------------------------------------------------
#define	A9225A_SCL		_pb4
#define	A9225A_SCLDIR	_pbc4
#define A9225A_SCLPU	_pbpu4

#define	A9225A_SDA		_pb2
#define	A9225A_SDADIR	_pbc2
#define	A9225A_SDAPU	_pbpu2
//-----------------------------------------------------------------
void A9225A_IIC_StartBit(void);
void A9225A_IIC_StopBit(void);
u8  A9225A_IIC_DataOutput(u8 da);
u8  A9225A_IIC_DataInput(u8 ack);
void A9225A_InterfaceConfigure(void);
u8 A9225A_RegisterRead(u8 MEMadr,u8 REGadr,u8 *rval);
u8 A9225A_MemoryRead(u8 adr,u8 *rval);
void A9225A_RegisterWrite(u8 MEMadr,u8 REGadr,u8 MASK,u8 val);
u8 A9225A_MemoryWrite(u8 adr,u8 *val);
void NFC_Tag_PassThrough_Init(void);
void Process_NFC_Data(void);

#endif   /* _BC7262_H_ */