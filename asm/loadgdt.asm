bits 32

section .text
global loadgdt

gdtr	DW 0
	DD 0
	

loadgdt:
	mov eax, [esp + 4]
	mov [gdtr + 2], eax
	mov ax, [esp + 8]
	dec ax
	mov [gdtr], ax
	lgdt [gdtr]
	ret
