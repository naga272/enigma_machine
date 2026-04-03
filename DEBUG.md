# How to debug with gdb

go to into the path bin/ and do this command:

```
gdb

add-symbol-file ../build/kernelfull.o 0x100000
(y or n) y

break kernel.c: <num_row>

target remote | qemu-system-i386 -hda ./os.bin -S -gdb stdio

c                   // significa continue
next                // vai alla prossima istruzione
print <name_var>    // stampa a schermo qualcosa

```