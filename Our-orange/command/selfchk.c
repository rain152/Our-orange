#include "stdio.h"

#define magic_tag 0xaf02022

void self_check(int tag) {
	if(tag == magic_tag) return;
	printf("Oops! Something bad happen!\n");
	exit(1);
}

void test(char *s) {
	int tag = magic_tag;
	char buf[10];
	strcpy(buf, s);
	self_check(tag);
	return;
}

int main() {
	test("adasasfasfdasfafafsfadsfdsafadsfhjadsfgasdfsdf");
	return 0;
}
