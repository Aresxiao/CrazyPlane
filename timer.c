#include "game.h"

void
init_100hz_timer(void) {
	out_byte(0x43, 0x34);
	out_byte(0x40, 11932 % 256);
	out_byte(0x40, 11932 / 256);
}
