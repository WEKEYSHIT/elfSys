#include <stdio.h>
#include "file.h"
#include "type.h"

u32 getFileSize(u8* fileName)
{
	u32 retLen = 0;
	FILE* fp;
	if(fileName == NULL)
		goto end;
	fp = fopen(fileName,"rb");
	if(fp == NULL)
	{
		goto end;
	}
	fseek(fp, 0, SEEK_END);
	retLen = ftell(fp);
end:
	if(fp)
		fclose(fp);
	return retLen;
}

u32 fileRead(u8* fileName, u8* buff, u32 buffSize)
{
	u32 retLen = 0;
	u32 fileSize;
	FILE* fp = NULL;
	fileSize = getFileSize(fileName);
	if(fileSize==0 || fileSize > buffSize)
		goto end;
	fp = fopen(fileName,"rb");
	if(fp == NULL)
		goto end;
	if(fread(buff, sizeof(u8), fileSize, fp) != fileSize)
		goto end;
	retLen = fileSize;

end:
	if(fp)
		fclose(fp);
	return retLen;
}
