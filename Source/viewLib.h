#ifndef __VIEWLIB__
#define __VIEWLIB__

#include "type.h"

#define SEGFORMAT	"---------------%s---------------\n"
#define VIEWFORMAT(NAME)	NAME, sizeof(NAME)
#define VIEWFORMATV(NAME)	&NAME, sizeof(NAME)

#define GetOffByMem(STRUCT,MEM)	((u32)&((STRUCT*)0)->MEM)

void viewNhex(u8* fmt, void* vhex, u32 len);
void viewNchars(u8* fmt, u8* str, u8 len);
u32 viewAtoi(u8* numStr);
u32 viewGetNum(void* numData, u8 islittle);
u16 viewGetNum16(void* numData, u8 islittle);

#endif
