#pragma once
#include "kernel.h"
typedef volatile struct tss
{
	uint16 link;
	uint16 link_h;

	uint32 esp0;
	uint16 ss0;
	uint16 ss0_h;

	uint32 esp1;
	uint16 ss1;
	uint16 ss1_h;

	uint32 esp2;
	uint16 ss2;
	uint16 ss2_h;

	uint32 cr3;
	uint32 eip;
	uint32 eflags;

	uint32 eax;
	uint32 ecx;
	uint32 edx;
	uint32 ebx;

	uint32 esp;
	uint32 ebp;
	
	uint32 esi;
	uint32 edi;

	uint16 es;
	uint16 es_h;

	uint16 cs;
	uint16 cs_h;

	uint16 ss;
	uint16 ss_h;

	uint16 ds;
	uint16 ds_h;

	uint16 fs;
	uint16 fs_h;

	uint16 gs;
	uint16 gs_h;

	uint16 ldt;
	uint16 ldt_h;

	uint16 trap;
	uint16 iomap;
} __attribute__((packed)) tss_t;

extern void tss_set_kernel_stack(unsigned int stack);
extern void tss_install(signed int num, uint16 ss0, uint16 esp0);
extern void tss_switch();


