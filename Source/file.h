#ifndef __MFILE__
#define __MFILE__

#include "type.h"

u32 getFileSize(u8* fileName);
u32 fileRead(u8* fileName, u8* buff, u32 buffSize);

#endif
