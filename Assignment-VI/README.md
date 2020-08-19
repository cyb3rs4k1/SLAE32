# Assignment-VI - Polymorphic Shellcode

Introduction
Polymorphism is the ability of an object to take on many forms. For pushing the value 0x6e69622f(nib/) into the stack will alert the IPS/AV. Instead we can go around the clock and push the dword 0x6e69622e and add a corresponding 0x00000001 so that it will be hard for the IDS/IPS/AV to detect the code for any possible execves.


### Challenge 1 : Analyzing Linux x86 execve("/bin/sh") - 28 bytes
http://shell-storm.org/shellcode/files/shellcode-811.php

