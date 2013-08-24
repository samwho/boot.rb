#include <stdlib.h>
#include <panic.h>

void exit(int status)
{
	__halt_with_message("Exit: %i", status);
}

void abort(void)
{
	__halt_with_message("Abort");
}
