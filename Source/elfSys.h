#ifndef __ELFSYS__
#define __ELFSYS__

#include "type.h"

typedef u32 Elf32_Addr;
typedef u16 Elf32_Half;
typedef u32 Elf32_Off;
typedef s32 Elf32_Sword;
typedef u32 Elf32_Word;

#define EI_NIDENT 16
typedef struct
{
	u8 magic[4];
	u8 EI_CLASS;
	u8 EI_DATA;
	u8 EI_VERSION;
	u8 EI_PAD[9];
}Ehdr_Ident;

typedef struct
{
	Ehdr_Ident	e_ident;
	Elf32_Half	e_type;
	Elf32_Half	e_machine;
	Elf32_Word	e_version;
	Elf32_Addr	e_entry;
	Elf32_Off	e_phoff;
	Elf32_Off	e_shoff;
	Elf32_Word	e_flags;
	Elf32_Half	e_ehsize;
	Elf32_Half	e_phentsize;
	Elf32_Half	e_phnum;
	Elf32_Half	e_shentsize;
	Elf32_Half	e_shnum;
	Elf32_Half	e_shstrndx;
}Elf32_Ehdr;

typedef struct
{
	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off  sh_offset;
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
}Elf32_Shdr;

typedef struct
{
	Elf32_Shdr shdr;
	u32 dataSize;
	u8*	data;
}Elf32_Sec;

typedef struct
{
	u16 SecNum;
	Elf32_Sec* Section;
}Elf32_SecTable;

void elfSys(u8* buff);

#endif
