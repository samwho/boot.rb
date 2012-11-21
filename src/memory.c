#include <memory.h>
void print_mmap_info(multiboot_info_t *mbd)
{
	if(mbd->flags & MULTIBOOT_INFO_MEM_MAP)
	{
		multiboot_memory_map_t *mmap = mbd->mmap_addr;
		int i = 1;
		while(mmap < mbd->mmap_addr + mbd->mmap_length)
		{
			printf("ENTRY #%d:\n", i);
			printf("Memory map base address: 0x%x%x\n", (uint32_t)mmap->addr >> 32, (uint32_t)mmap->addr & 0xfffffff);
			printf("Memory map length: 0x%x%x\n", (uint32_t)mmap->len >> 32, (uint32_t)mmap->len & 0xffffffff);
			printf("Memory map size: 0x%x\n", mmap->size);
			printf("Memory map type: 0x%x\n", mmap->type);
			mmap = (multiboot_memory_map_t *) ((unsigned int)mmap + mmap->size + sizeof(mmap->size));
			i++;
		}

		printf("Got %d mmap entries\n", i);
	}
}

void print_mmap_entry(multiboot_info_t *mbd, uint32_t n)
{
	printf("ENTRY #%d\n", n);
	if(mbd->flags & MULTIBOOT_INFO_MEM_MAP)	
	{
		multiboot_memory_map_t *mmap = mbd->mmap_addr + (mmap->size + sizeof(mmap->size))*n;
		printf("Memory map base address: 0x%x%x\n", (uint32_t)mmap->addr >> 32, (uint32_t)mmap->addr & 0xfffffff);
		printf("Memory map length: 0x%x%x\n", (uint32_t)mmap->len >> 32, (uint32_t)mmap->len & 0xffffffff);
		printf("Memory map size: 0x%x\n", mmap->size);
		printf("Memory map type: %s\n", mmap->type == 1 ? "AVAILABLE" : "RESERVED");
	}
}

