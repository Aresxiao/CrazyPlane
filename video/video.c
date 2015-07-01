#include "video.h"

/* The ``vmem'' is just a pointer pointing to a magic memory area. */
uint_8 *vmem = (uint_8*)0xA0000;

inline void
draw_pixel(int x, int y, int color) {
	if (x >= 0 && y >= 0 && x < 200 && y < 320)
		/* this is a dialect of vmem[x * 320 + y] = color; */
		vmem[(x << 8) + (x << 6) + y] = color;
}

