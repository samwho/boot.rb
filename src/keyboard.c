#include <isr.h>
#include <keysym.h>
#include <text.h>
#include <keyboard.h>

uint8_t buffer[256];
uint32_t buffer_pos = 0;

void read_scancode()
{
	char scancode = inb(0x60);
	if(!(scancode & 0x80))
	{
		buffer[buffer_pos] = scancode;
		buffer_pos++;
	}
}

void keyboard_handler(registers_t regs)
{
	read_scancode();
}

void keyboardInit()
{
	memset(&buffer, 0, 256);
	register_interrupt_handler(IRQ1, keyboard_handler);
}

uint32_t readBuffer(int len, char *out)
{
	if(buffer_pos != 0)
	{
		for(int i = 0; i < len; i++)
		{
			out[i] = keysym_us[buffer[i]];
		}
		buffer_pos -= len;
		return 1;
	}
	return 0;
}

char *readUntilReturn()
{
	char *buff = "";
	char currentChar = 0;
	uint32_t i = 0;
	while(currentChar != '\n')
	{
		if(readBuffer(1, &currentChar)) {
			if(currentChar != '\b') {
				putc(currentChar);
				buff[i] = currentChar;
				i++;
			}
			else
			{
				putc(currentChar);
				i--;
			}
		}
	}
	buff[i-1] = '\0';
	return buff;
}



int getchar()
{
  char *tmp = malloc(1);
  fgets(1, tmp);
  return (int)(tmp[0]);
}

