#include "game.h"

/* This program runs in computer without any operating system support,
   so you cannot use any system library (although some might work,
   most will have unexpected behavior). */

void
game_init(void) {
	/* Setting up a 100Hz timer */
	init_100hz_timer();

	/* Setting up the interrupt descriptor table, 
	   this procedure installs ``actual'' interrupt handlers */
	init_idt();

	/* Setting up the interrupt controller i8259,
	   the interrupt code will start at 32,
	   and i8259 will send end-of-interrupt signal automatically */
	init_intr();

	/* Setting up the game interrupt handlers.
	   the start_frame and key_stroke procedures are wrapped by
	   our interrupt handler to make interrupts transparent.
	   For implementation, you simply need to know that start_frame
	   is called for every timer interrupt, and so does key_stroke
	   for every keyboard interrupt (press or release). */
	set_timer_intr_handler(start_frame);
	set_keyboard_intr_handler(key_stroke);

	/* Calls the game logic.
	   All game logic related codes are in game.c */
	init_game();

	/* Just a ``sti'' instruction */
	enable_interrupt();

	/* The main loop now needs to do nothing but wait for
	   coming endless interrupts.
	   All game tasks are done in the interrupt handler. */
	while (1) {
		idle_cpu();
	}
}
