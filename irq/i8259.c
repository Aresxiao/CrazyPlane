#include "x86/x86.h"

/* Oh, magic numbers! I don't like them.
   I think you don't them either. */
#define PORT_PIC_MASTER 0x20
#define PORT_PIC_SLAVE  0xA0
#define IRQ_SLAVE       2

/* What hell is this? This is some hardware-related codes.
   Sets up the intel 8259 interrupt controller.
   Just ignore them. It just places the right interrupt
   of right number into the CPU. */
void
init_intr(void) {
	out_byte(PORT_PIC_MASTER + 1, 0xFF);
	out_byte(PORT_PIC_SLAVE + 1 , 0xFF);
	out_byte(PORT_PIC_MASTER, 0x11);
	out_byte(PORT_PIC_MASTER + 1, 32);
	out_byte(PORT_PIC_MASTER + 1, 1 << 2);
	out_byte(PORT_PIC_MASTER + 1, 0x3);
	out_byte(PORT_PIC_SLAVE, 0x11);
	out_byte(PORT_PIC_SLAVE + 1, 32 + 8);
	out_byte(PORT_PIC_SLAVE + 1, 2);
	out_byte(PORT_PIC_SLAVE + 1, 0x3);

	out_byte(PORT_PIC_MASTER, 0x68);
	out_byte(PORT_PIC_MASTER, 0x0A);
	out_byte(PORT_PIC_SLAVE, 0x68);
	out_byte(PORT_PIC_SLAVE, 0x0A);
}
