#ifndef __X86_CPU_H__
#define __X86_CPU_H__

#include "game.h"

/* put the CPU into idle, waiting for next interrupt */
static inline void
idle_cpu() {
	asm volatile("hlt");
}

/* modify the value of IDTR */
static inline void
save_idt(void *addr, uint_32 size) {
	static uint_16 data[3];
	data[0] = size - 1;
	data[1] = (uint_32)addr;
	data[2] = ((uint_32)addr) >> 16;
	asm volatile("lidt (%0)" : : "r"(data));
}

/* the interrupt management */
static inline void
enable_interrupt(void) {
	asm volatile("sti");
}

static inline void
disable_interrupt(void) {
	asm volatile("cli");
}

#define asmlinkage __attribute__((regparm(0)))

#define NR_IRQ    256

#endif
