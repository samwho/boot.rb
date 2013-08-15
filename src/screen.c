#include <screen.h>

uint16_t cursor_x,cursor_y = 0;
uint16_t *video = (uint16_t *)0xb8000;
uint8_t attr = 0x0F;

void scroll()
{
	uint16_t blank = 0x20 | (attr << 8);

	if(cursor_y >= 25)
	{
		int i;
		for(i = 0; i < 24*80; i++)
		{
			video[i] = video[i+80];
		}

		for(i = 24*80; i < 25*80; i++)
		{
			video[i]=blank;
		}

		cursor_y = 24;
	}
}

void move_cursor()
{
	uint16_t pos = 80*cursor_y + cursor_x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos&0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos>>8)&0xFF));
}

void cls()
{
	memset(video, 0, 80*25);
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

void putc(char c)
{
	if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
		move_cursor();
		scroll();
		return;
	} 
	else if (c == '\b')
	{
		if(cursor_x > 0)
			cursor_x--;
		move_cursor();
		return;
	}
	uint16_t attribute = attr << 8;
	uint16_t *position = video + ( cursor_y * 80 + cursor_x);
	*position = c | attribute;
	if(cursor_x != 80) cursor_x++;
	else 
	{
		cursor_x = 0;
		cursor_y++;
	}
	scroll();
	move_cursor();
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


// TODO: Is this even remotely correct?
size_t fwrite(const void *ptr, size_t size, size_t nmemb,
                     FILE *stream)
{
	// Always assume stream == stdout.

	int i;

	for (i = 0; i < size; i++) {
		puts((char*)(ptr + i));
	}

	return i;
}
