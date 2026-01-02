#ifndef INTERRUPTS_H
#define INTERRUPTS_H 

/* INTERRUPT CPU EXCEPTION */
extern void int0h();
extern void int1h();
extern void int2h();
extern void int3h();
extern void int4h();
extern void int5h();
extern void int6h();
extern void int7h();
extern void int8h();
extern void int9h();
extern void intah();
extern void intbh();
extern void intch();
extern void intdh();
extern void inteh();
extern void intfh();
extern void int10h();
extern void int11h();
extern void int12h();
extern void int13h();
extern void int14h();
extern void int15h();
extern void int16h();
extern void int17h();
extern void int18h();
extern void int19h();
extern void int1ah();
extern void int1bh();
extern void int1ch();
extern void int1dh();
extern void int1eh();
extern void int1fh();
/* INTERRUPT PIC MASTER */
extern void int20h();       
extern void int21h();       
extern void int22h();       
extern void int23h();       
extern void int24h();       
extern void int25h();       
extern void int26h();       
extern void int27h();  
/* INTERRUPT PIC SLAVE */     
extern void int28h();       
extern void int29h();       
extern void int2ah();       
extern void int2bh();       
extern void int2ch();       
extern void int2dh();       
extern void int2eh();       
extern void int2fh();     
/* SYSCALLS */
extern void int80h();

#endif