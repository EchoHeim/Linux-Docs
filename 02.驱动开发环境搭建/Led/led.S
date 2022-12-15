.text
 .globl _start
 _start:
 ldr r0, =0x110002E0 //GPM4CON
 ldr r1, =0x1111 //output
 str r1, [r0]
 ldr r0, =0x110002E4 //GPM4DAT
 mov r1, #0x0 //0000
 str r1, [r0]
 loop:
 b loop
