#include "elfSys.h"
#include "viewLib.h"
#include "type.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static u8 isLittle = 0;

void view_EhdrIdent(Ehdr_Ident*	e_id)
{
	u8* EI_DATA_VALUE[]= {"ELFDATANONE","ELFDATA2LSB","ELFDATA2MSB","NONE"};
	u8* EI_CLASS[] = {"ELFCLASSNONE", "ELFCLASS32", "ELFCLASS64","NONE"};
	printf(SEGFORMAT, "Ehdr_Ident");
	viewNchars("magic: %s\n",e_id->magic, 4);
	printf("EI_CLASS: %02x %s\n", e_id->EI_CLASS, EI_CLASS[e_id->EI_CLASS & 0x03]);
	printf("EI_DATA : %02x %s\n", e_id->EI_DATA, EI_DATA_VALUE[e_id->EI_DATA & 0x03]);
	printf("EI_VERSION : %02x\n", e_id->EI_VERSION);
	viewNhex("EI_PAD : %s\n", VIEWFORMAT(e_id->EI_PAD));
}

void view_Ehdr(Elf32_Ehdr* eh)
{
	u8* e_type_value[] = {"ET_NONE","ET_REL","ET_EXEC","ET_DYN"};
	printf(SEGFORMAT, "Elf32_Ehdr");
	view_EhdrIdent(&eh->e_ident);
	printf("e_type: %04x %s\n", eh->e_type, e_type_value[eh->e_type & 0x03]);
	printf("e_machine: %04x\n", eh->e_machine);
	printf("e_version: %08x\n", eh->e_version);
	printf("e_entry: %08x\n", eh->e_entry);
	printf("e_phoff: %08x\n", eh->e_phoff);
	printf("e_shoff: %08x\n", eh->e_shoff);
	printf("e_flags: %08x\n", eh->e_flags);
	printf("e_ehsize: %04x\n", eh->e_ehsize);
	printf("e_phentsize: %04x\n", eh->e_phentsize);
	printf("e_phnum: %04x\n", eh->e_phnum);
	printf("e_shentsize: %04x\n", eh->e_shentsize);
	printf("e_shnum: %04x\n", eh->e_shnum);
	printf("e_shstrndx: %04x\n", eh->e_shstrndx);
}

u8* SecType[] = 
{
	"SHT_NULL",
	"SHT_PROGBITS~",
	"SHT_SYMTAB",
	"SHT_STRTAB",
	"SHT_RELA",
	"SHT_HASH",
	"SHT_DYNAMIC",
	"SHT_NOTE",
	"SHT_NOBITS~",
	"SHT_REL",
	"SHT_SHLIB~",
	"SHT_EXT~",
};
u8* getSecType(u32 type)
{
	u8 off = 0;
	if(type > sizeof(SecType)/sizeof(u8*))
		type = sizeof(SecType)/sizeof(u8*)-1;
	return SecType[type];
}
u8 SecAttr[100];
u8* getSecAttrByFlags(u32 flags)
{
	u8 off = 0;
	if(flags & 0x01)
	{
		SecAttr[off++] = 'W';
		SecAttr[off++] = '|';
	}
	if(flags & 0x02)
	{
		SecAttr[off++] = 'A';
		SecAttr[off++] = '|';
	}
	if(flags & 0x04)
	{
		SecAttr[off++] = 'X';
		SecAttr[off++] = '|';
	}
	if(flags & 0xfffffff8)
	{
		SecAttr[off++] = '~';
		SecAttr[off++] = '|';
	}
	SecAttr[off-1] = 0;
	return SecAttr;
}

void view_SecTable(Elf32_SecTable* Sectab, u32 strNum)
{
	u16 i = Sectab->SecNum;
	u16 j = 0;
	Elf32_Sec* pSec = Sectab->Section;
	Elf32_Sec* pSecStr = Sectab->Section + strNum;
	printf(SEGFORMAT, "SecTable");
	printf("SecTable num: %d\n", Sectab->SecNum);
	while(i--)
	{	
		printf("======%d======%d======\n", j++, pSec->dataSize);
		printf("sh_name: %08x %s\n", pSec->shdr.sh_name, pSecStr->data + pSec->shdr.sh_name);
		printf("sh_type: %08x %s\n", pSec->shdr.sh_type, getSecType(pSec->shdr.sh_type));
		printf("sh_flags: %08x %s\n", pSec->shdr.sh_flags, getSecAttrByFlags(pSec->shdr.sh_flags));
		printf("sh_addr: %08x\n", pSec->shdr.sh_addr);
		printf("sh_offset: %08x\n", pSec->shdr.sh_offset);
		printf("sh_size: %08x\n", pSec->shdr.sh_size);
		printf("sh_link: %08x\n", pSec->shdr.sh_link);
		printf("sh_info: %08x\n", pSec->shdr.sh_info);
		printf("sh_addralign: %08x\n", pSec->shdr.sh_addralign);
		printf("sh_entsize: %08x\n", pSec->shdr.sh_entsize);
		viewNhex("data_hex: %s\n", pSec->data, pSec->dataSize);
		pSec++;
	}
}

void init_Ehdr(Elf32_Ehdr* ehdr, u8* buff)
{
#define buffOffset(Mem)	(buff + GetOffByMem(Elf32_Ehdr, Mem))
	memcpy(&ehdr->e_ident, buffOffset(e_ident), sizeof(Ehdr_Ident));
	isLittle = ehdr->e_ident.EI_DATA&0x01;
	ehdr->e_type = viewGetNum16(buffOffset(e_type), isLittle);
	ehdr->e_machine = viewGetNum16(buffOffset(e_machine), isLittle);
	ehdr->e_version = viewGetNum(buffOffset(e_version),isLittle);
	ehdr->e_entry = viewGetNum(buffOffset(e_entry),isLittle);
	ehdr->e_phoff = viewGetNum(buffOffset(e_phoff),isLittle);
	ehdr->e_shoff = viewGetNum(buffOffset(e_shoff),isLittle);
	ehdr->e_flags = viewGetNum(buffOffset(e_flags),isLittle);
	ehdr->e_ehsize = viewGetNum16(buffOffset(e_ehsize),isLittle);
	ehdr->e_phentsize = viewGetNum16(buffOffset(e_phentsize),isLittle);
	ehdr->e_phnum = viewGetNum16(buffOffset(e_phnum),isLittle);
	ehdr->e_shnum = viewGetNum16(buffOffset(e_shnum),isLittle);
	ehdr->e_version = viewGetNum16(buffOffset(e_version),isLittle);
	ehdr->e_shstrndx = viewGetNum16(buffOffset(e_shstrndx),isLittle);
#undef	buffOffset
}

/*
*	@para1	section table pointer
*	@para2	section header's number
*	@para3	file buffer
*	@para4	section header's file offset
*/
void init_SectionTable(Elf32_Sec* secTable, u16 shNum, u8* buff, u32 shdOff)
{
	Elf32_Shdr* pShdr = (Elf32_Shdr*)(buff + shdOff);
	Elf32_Sec* pSec = secTable;
	while(shNum--)
	{
		pSec->shdr.sh_name = viewGetNum(&pShdr->sh_name, isLittle);
		pSec->shdr.sh_type = viewGetNum(&pShdr->sh_type, isLittle);
		pSec->shdr.sh_flags = viewGetNum(&pShdr->sh_flags, isLittle);
		pSec->shdr.sh_addr = viewGetNum(&pShdr->sh_addr, isLittle);
		pSec->shdr.sh_offset = viewGetNum(&pShdr->sh_offset, isLittle);
		pSec->shdr.sh_size = viewGetNum(&pShdr->sh_size, isLittle);
		pSec->shdr.sh_link = viewGetNum(&pShdr->sh_link, isLittle);
		pSec->shdr.sh_info = viewGetNum(&pShdr->sh_info, isLittle);
		pSec->shdr.sh_addralign = viewGetNum(&pShdr->sh_addralign, isLittle);
		pSec->shdr.sh_entsize = viewGetNum(&pShdr->sh_entsize, isLittle);
		pSec->data = buff + pSec->shdr.sh_offset;
		pSec->dataSize = pSec->shdr.sh_size;
		pShdr ++;
		pSec ++;
	}
}

void elfSys(u8* buff)
{
	Elf32_SecTable secs;
	Elf32_Ehdr elf_header;
	init_Ehdr(&elf_header, buff);
	printf("Elf32_Ehdr: %d Ehdr_Ident:%d e_type offset: %d\n", sizeof(Elf32_Ehdr), sizeof(Ehdr_Ident), (u32)&((Elf32_Ehdr*)0)->e_type);
	view_Ehdr(&elf_header);
	secs.SecNum = elf_header.e_shnum;
	secs.Section = malloc(secs.SecNum*sizeof(Elf32_Sec));
	if(secs.Section == NULL)
		goto end;

	init_SectionTable(secs.Section, secs.SecNum, buff, elf_header.e_shoff);
	view_SecTable(&secs, elf_header.e_shstrndx);
end:
	if(secs.Section)
		free(secs.Section);
}