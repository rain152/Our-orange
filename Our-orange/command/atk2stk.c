#include "stdio.h"
#include "type.h"
#include "string.h"
#include "sys/const.h"

#include "poc_code.h"

int i;

// test flow to stack
void test(char *str) {
    char buf[300];
	*(u8 **)(str + 0x138) = str;
    strcpy(buf, str);
    printf("%d %d\n", strlen(buf), strlen(str));
    // asm ("xchg %bx, %bx");
    for(i = 0; i < 1000000; i++);
    return;
}

int main(int argc, char argv[]) {
    u8 str[0x13d];
    str[0x13c] = 0;
    for(i = 0; i < 0x138; i++)
        str[i] = i < poc_code_bin_len ? poc_code_bin[i] : '#';
    test(str);
    return 0;
}
