#ifndef __X86_IO_H__
#define __X86_IO_H__

#include "game.h"

/* read a byte from the port */
static inline uint_8
in_byte(uint_16 port) {
	uint_8 data;
	asm volatile("in %1, %0" : "=a"(data) : "d"(port));
	return data;
}

/* write a byte to the port */
static inline void
out_byte(uint_16 port, uint_8 data) {
	asm volatile("out %%al, %%dx" : : "a"(data), "d"(port));
}

#endif
