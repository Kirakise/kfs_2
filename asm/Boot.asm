bits 32

section .multiboot
        dd 0x1BADB002
        dd 0x0
	dd - (0x1BADB002 + 0x0)

section .text
global _start
extern kernel_entry

_start:
        cli
        mov esp, stack_end ; 0x015FFFFF
        call kernel_entry
        hlt

section .bss
stack_begin:
  resb 16000
stack_end:
