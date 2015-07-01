#include "x86/x86.h"
#include "game.h"

/* Do you know why we are doing this? */
static void (*do_timer)(void);
static void (*do_keyboard)(int);

void
set_timer_intr_handler( void (*ptr)(void) ) {
	do_timer = ptr;
}
void
set_keyboard_intr_handler( void (*ptr)(int) ) {
	do_keyboard = ptr;
}

/* asmlinkage makes sure that the optimizer will always find *tf
   in the stack, because *tf is set by our assembly code. */
asmlinkage void
irq_handle(struct TrapFrame *tf) {
	if (tf->irq == 1000) {
		do_timer();
	} else if (tf->irq == 1001) {
		uint_32 code = in_byte(0x60);
		uint_32 val = in_byte(0x61);
		out_byte(0x61, val | 0x80);
		out_byte(0x61, val);
		do_keyboard(code);
	}
}

