#ifndef __LIBSYS__
#define __LIBSYS__

#include "type.h"

typedef struct
{
	u8 Name[16];
	u8 Time[12];
	u8 UserID[6];
	u8 GroupID[6];
	u8 Mode[8];
	u8 Size[10];
	u8 EndOfHeader[2];
}ObjSecHeader;

typedef struct
{
	u32	 SymbolNum;
	u32* SymbolOffset;
	u8*  SymbolName;
}FirsetSec;

typedef struct
{
	ObjSecHeader* header;
	u8*	data;
}ObjSec;

typedef struct
{
	u8 sig[8];
}Signature;

typedef struct
{
	Signature* psig;
	ObjSec	firstSec;
	FirsetSec firstSecData;
	ObjSec	secondSec;	
}LibStruct;

void libSys(u8* buff);

#endif
