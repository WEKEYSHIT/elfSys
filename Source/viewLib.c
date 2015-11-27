#include "viewLib.h"
#include "type.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

u16 viewGetNum16(void* numData, u8 islittle)
{
	u16 retNum;
	u8* data = numData;
	if(islittle)
		retNum = *(u16*)data;
	else
		retNum = (data[0]<<8)|(data[1]);
	return retNum;
}

u32 viewGetNum(void* numData, u8 islittle)
{
	u32 retNum;
	u8* data = numData;
	if(islittle)
		retNum = *(u32*)data;
	else
		retNum = (data[0]<<24)|(data[1]<<16)|(data[2]<<8)|(data[3]);
	return retNum;

}

u32 viewAtoi(u8* numStr)
{
	return atoi(numStr);
}

void viewNhex(u8* fmt, void* vhex, u32 len)
{
	u8 viewBuff[1024*3];
	u32 viewOff = 0;
	u8* hex = (u8*)vhex;
	if(fmt == NULL || vhex == NULL || len == 0 || len > sizeof(viewBuff)/3)
		return;
	while(len--)
		viewOff += sprintf(viewBuff + viewOff, "%02x ", *hex++);
	viewBuff[viewOff-1] = 0;
	printf(fmt, viewBuff);
}

void viewNchars(u8* fmt, u8* str, u8 len)
{
	u8 viewBuff[257];
	memcpy(viewBuff, str, len);
	viewBuff[len] = 0;
	printf(fmt,viewBuff);
}
