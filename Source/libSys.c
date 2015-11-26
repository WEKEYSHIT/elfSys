#include <stdio.h>
#include <string.h>
#include "viewLib.h"
#include "libSys.h"
#include "elfSys.h"
#include "type.h"

void view_ObjSecHeader(ObjSecHeader* osh)
{
	viewNchars("Name: %s\n", VIEWFORMAT(osh->Name));
	viewNchars("Time: %s\n", VIEWFORMAT(osh->Time));
	viewNchars("UserID: %s\n", VIEWFORMAT(osh->UserID));
	viewNchars("GroupID: %s\n", VIEWFORMAT(osh->GroupID));
	viewNchars("Mode: %s\n", VIEWFORMAT(osh->Mode));
	viewNchars("Size: %s\n", VIEWFORMAT(osh->Size));
	viewNhex("EndOfHeader: %s\n", VIEWFORMAT(osh->EndOfHeader));
}

void view_FirstSecData(FirsetSec* sec)
{
	u32 i = sec->SymbolNum;
	printf("SymbolNum : %d\n", i);
	while(i--)
	{
		printf("%s : %08x\n", sec->SymbolName, viewGetNum(sec->SymbolOffset, 0));
		sec->SymbolOffset++;
		sec->SymbolName += (strlen(sec->SymbolName)+1);
	}
}

void initFirstSec(FirsetSec* sec, u8* data)
{
	u32 *intdata = (u32*)data;
	sec->SymbolNum = viewGetNum(intdata++, 0);
	sec->SymbolOffset = intdata;
	sec->SymbolName = (u8*)(intdata + sec->SymbolNum);
}

void libSys(u8* buff)
{
	LibStruct lib;

	lib.psig = (Signature*)buff;
	lib.firstSec.header = (ObjSecHeader*)(buff + 8);
	lib.firstSec.data = (u8*)lib.firstSec.header + sizeof(ObjSecHeader);
	initFirstSec(&lib.firstSecData, lib.firstSec.data);

	lib.secondSec.header = (ObjSecHeader*)(lib.firstSec.data + viewAtoi(lib.firstSec.header->Size));
	lib.secondSec.data = (u8*)lib.secondSec.header + sizeof(ObjSecHeader);

	viewNchars("Signature: %s\n", VIEWFORMAT(lib.psig->sig));
	printf(SEGFORMAT, "First Sec");
	view_ObjSecHeader(lib.firstSec.header);

	printf(SEGFORMAT, "First Sec Data");
	view_FirstSecData(&lib.firstSecData);

	printf(SEGFORMAT, "Second Sec");
	view_ObjSecHeader(lib.secondSec.header);
	
	printf(SEGFORMAT, "Second Sec Data");
	elfSys(lib.secondSec.data);
}