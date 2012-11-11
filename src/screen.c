#include <screen.h>

uint16_t position = 0;
uint16_t cursor_x,cursor_y = 0;
uint8_t *video = (uint8_t *)0xB8000;
uint8_t attr = 0x0F;

void move_cursor(uint16_t crs_x, uint16_t crs_y)
{
	uint16_t pos = 80*crs_y + crs_x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos&0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos>>8)&0xFF));
	position = pos*2;
	cursor_x = crs_x;
	cursor_y = crs_y;
}

void cls()
{
	memset(video, 0, 80*25);
}

void increment_cursor()
{
	if(cursor_x != 80) cursor_x++;
	else if (cursor_y != 25)
	{
		cursor_x = 0;
		cursor_y++;
	}
	else 
	{
		/* Handle this in a bit */
	}
	move_cursor(cursor_x, cursor_y);	
}

void putc(char c)
{
	if (c == '\n') {
		move_cursor(0, ++cursor_y);
		return;
	}
	video[position] = c;
	video[++position] = attr;
	increment_cursor();
}

void puts(char *s)
{
	uint32_t i = 0;
	while(s[i] != 0) 
	{
		putc(s[i]);
		i++;
	}
}


static const char nybble_chars[] = "0123456789ABCDEF";
void puthex(uint32_t hex)
{
	puts("0x");
	uint8_t *bytes = (uint8_t *)&hex;
	for(int i = 3; i >=  0; i--)
	{
		putc(nybble_chars[(bytes[i] >> 4) & 0xF]);
		putc(nybble_chars[bytes[i] & 0x0F]);
	}
}



