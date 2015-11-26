#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "file.h"
#include "libSys.h"

u8 fileName[100];
int main(int argc, char* argv[])
{
	u8* fileData = NULL;
	u32 fileSize;
	scanf("%s", fileName);
	fileSize = getFileSize(fileName);
	if(!fileSize)
		goto end;
	fileData = malloc(fileSize);
	if(fileData == NULL)
		goto end;
	fileSize = fileRead(fileName, fileData, fileSize);
	if(!fileSize)
		goto end;
	libSys(fileData);
end:
	if(fileData)
	{
		free(fileData);
		fileData = NULL;
	}
	getchar();
	return 0;
}