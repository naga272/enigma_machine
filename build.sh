#/bin/bash

rm ./tmp/os_iso/*


export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

make all

# serve per la ISO (sto cercando ancora di capire come fare)

cp ./bin/os.bin ./tmp/os_iso/
mkisofs -o os.iso -b os.bin -c boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table ./tmp/os_iso/


# cp ./bin/os.bin ./iso/boot/
# grub-mkrescue -o myos.iso iso
