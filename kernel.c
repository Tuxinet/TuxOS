#include "versatilepb.h"
#include "asm.h"

/* User program test */
void first(void)
{
    bwputs("In user mode\n");
    while(1) syscall();
}

void task(void)
{
    bwputs("In the other tast\n");
    while(1) syscall();
}


void bwputs(char *s)
{
	while(*s)
    {
		while(*(UART0 + UARTFR) & UARTFR_TXFF);
		*UART0 = *s;
		s++;
	}
}

int main(void)
{
    unsigned int stacks[2][256];
    unsigned int *tasks[2];

    tasks[0] = stacks[0] + 256 - 16;
    tasks[0][0] = 0x10;
    tasks[0][1] = (unsigned int)&first;

    tasks[1] = stacks[1] + 256 - 16;
    tasks[1][0] = 0x10;
    tasks[1][1] = (unsigned int)&task;

	bwputs("Starting...\n");
    activate(tasks[0]);
    activate(tasks[1]);

	while(1); /* We can't exit, there's nowhere to go */
	return 0;
}
