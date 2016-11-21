#include "versatilepb.h"
#include "asm.h"


void bwputs(char *s)
{
	while(*s)
    {
		while(*(UART0 + UARTFR) & UARTFR_TXFF);
		*UART0 = *s;
		s++;
	}
}

/* User program test */
void first(void)
{
    bwputs("In user mode\n");
    syscall();
    bwputs("We back boyz\n");
    while(1) syscall();
}

void task(void)
{
    bwputs("In the other tast\n");
    while(1) syscall();
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
    tasks[0] = activate(tasks[0]);
    tasks[1] = activate(tasks[1]);

    activate(tasks[0]);

	while(1); /* We can't exit, there's nowhere to go */
	return 0;
}
