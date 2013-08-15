#include <memory.h>

struct block top;
struct block children[1 << ORDER_LIMIT];
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

void memset(void *ptr, char val, int size)
{
	for(int i = 0; i < size; i++)
	{
		((char *)ptr)[i] = val;
	}
}

void memcpy(void *dest, const void *src, int size)
{
	char* d = (char*)dest;
	char *s = (char*)src;
	for(int i = 0; i < size; i++)
	{
		d[i] = s[i];
	}
		
}


struct block top;
struct block children[1 << ORDER_LIMIT];


void mm_init(void *memstart)
{
	top.addr = memstart;
	top.order = ORDER_LIMIT;
	top.parent = 0;
	top.children[0] = -1;
	top.children[1] = -1;
	top.free = 1;
	memset(children, 0, (1<<ORDER_LIMIT) * sizeof(struct block));
}

int create_child(struct block *parent, char pos)
{
	struct block child;
	child.parent = parent;
	child.free = 1;
	child.order = parent->order - 1;
	child.pos = pos;
	child.addr = parent->addr + pos*((1 << child.order) * BLOCK_MIN * 1024);
	child.children[0] = -1;
	child.children[1] = -1;
	int i = 0;
	while(children[i].addr != 0) {i++;};
	memcpy(&children[i], &child, sizeof(child));;
	return i;
}

void block_parents(struct block *child)
{
	struct block *newparent = child->parent;
	while(newparent != 0)
	{
		newparent->free = 0;
		newparent = newparent->parent;
	}
}

int d = 0;
struct block *find_order(unsigned int order, struct block *start)
{
	if(start->order == order)
	{
		d++;
		if(start->free)
		{
			return start;
		}
		else
			return 0;
	}
	else if(start->children[0] > -1)
	{
		struct block *child;
		child = find_order(order, &(children[start->children[0]])); 
		if(child)
			return child;

		child = find_order(order, &(children[start->children[1]])); 
		if(child)
			return child;
	
		return 0;
	}
	else if(start->order != 0)
	{
		start->children[0] = create_child(start,0);
		start->children[1] = create_child(start,1);
		return find_order(order, start);
	}
	return 0;
}


void *find_block(unsigned int size)
{
	//Okay, this is messy and annoying. Basically I work out how many times size
	//goes into a minimum block, then figure out the log2 of that to get the order needed.
	int order_required = 0;
	int size_temp = (size-1) / (BLOCK_MIN*1024);
	if(size_temp != 0)
	{
		while(size_temp != 0)
		{
			size_temp >>= 1;
			order_required++;
		}
	}
	if(order_required == ORDER_LIMIT && top.free)
		return top.addr;

	struct block *suitable_block = find_order(order_required, &top);
	if(suitable_block->addr)
	{
		suitable_block->free = 0;
		block_parents(suitable_block);
		return suitable_block->addr;
	}
	else
		return 0;
}

struct block *find_by_addr(void *addr, struct block *start)
{
	if(start->addr == addr)
	{
		if(start->children[0] == -1)
		{
			printf("Found a suitable block: 0x%x", start);
			return start;
		}
		else
			return find_by_addr(addr, &(children[start->children[0]]));
	}
	else
	{
		// Which side of the starting node should it be on?
		if(addr < start->addr + (1 << (start->order-1))*BLOCK_MIN*1024)
			return find_by_addr(addr, &(children[start->children[0]]));
		else
			return find_by_addr(addr, &(children[start->children[1]]));
	}
}


void *malloc(unsigned int size)
{
	if(size > ((1 << ORDER_LIMIT) * BLOCK_MIN * 1024)) //Erp, it's too big!
		return 0;

	return find_block(size);
}

void free(void *ptr)
{
	if(ptr < top.addr || ptr > (top.addr + (1 << ORDER_LIMIT) * BLOCK_MIN * 1024) || (unsigned int)ptr % 4096 != 0) //Invalid address
		return;
	struct block *blk = find_by_addr(ptr, &top);
	int otherpos = ~(blk->pos | 0xFFFFFFFE); // Lol bit twiddling. This makes sure that blk->pos is filled with 1's except for the LSB, which is the one we're interested in.
	if(children[blk->parent->children[otherpos]].free)
	{
		struct block *parent = blk->parent;
		parent->children[0] = -1;
		parent->children[1] = -1;
		parent->free = 1;
		blk->addr = 0;
		children[blk->parent->children[otherpos]].addr = 0;
	}
	else
		blk->free = 1;
}

void *realloc(void *ptr, size_t size)
{
	void *new = malloc(size);
	memcpy(new, ptr, size);
	free(ptr);

	return new;
}
