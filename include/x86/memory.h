#ifndef __X86_MEMORY_H__
#define __X86_MEMORY_H__

#define SEG_CODEDATA            1
#define SEG_32BIT               1
#define SEG_4KB_GRANULARITY     1
#define SEG_TSS_32BIT           0x9

#define DPL_KERNEL              0
#define DPL_USER                3

#define SEG_WRITABLE            0x2
#define SEG_READABLE            0x2
#define SEG_EXECUTABLE          0x8


#define NR_SEGMENTS             3
#define SEG_KERNEL_CODE         1 
#define SEG_KERNEL_DATA         2

struct GateDescriptor {
	uint_32 offset_15_0      : 16;
	uint_32 segment          : 16;
	uint_32 pad0             : 8;
	uint_32 type             : 4;
	uint_32 system           : 1;
	uint_32 privilege_level  : 2;
	uint_32 present          : 1;
	uint_32 offset_31_16     : 16;
};

struct TrapFrame {
	uint_32 edi, esi, ebp, xxx, ebx, edx, ecx, eax;
	int_32 irq;
};

#endif
