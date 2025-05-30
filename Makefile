
FILES = ./build/kernel.asm.o ./build/kernel.o ./build/io/io.asm.o ./build/stdlib/stdlib.o ./build/string/string.o ./build/video/video.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/enigma/enigma.o
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc


all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin


iso: ./bin/os.bin
	mkdir -p ./iso/boot/grub
	cp ./bin/os.bin ./iso/boot/os.bin
	echo 'menuentry "My OS" {' > ./iso/boot/grub/grub.cfg
	echo '  multiboot /boot/os.bin' >> ./iso/boot/grub/grub.cfg
	echo '  boot' >> ./iso/boot/grub/grub.cfg
	echo '}' >> ./iso/boot/grub/grub.cfg
	grub-mkrescue -o ./bin/os.iso ./iso
	rm -rf ./iso


./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin


./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o


./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o


./build/kernel.o: ./src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -I/usr/include/python3.12 -c ./src/kernel.c -o ./build/kernel.o


./build/io/io.asm.o: ./src/io/io.asm
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o


./build/video/video.o: ./src/video/video.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/video/video.c -o ./build/video/video.o


./build/idt/idt.asm.o: ./src/idt/idt.asm
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o


./build/stdlib/stdlib.o: ./src/stdlib/stdlib.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/stdlib/stdlib.c -o ./build/stdlib/stdlib.o


./build/string/string.o: ./src/string/string.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/string/string.c -o ./build/string/string.o


./build/idt/idt.o: ./src/idt/idt.c 
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt/idt.o


./build/enigma/enigma.o: ./src/enigma/enigma.c
	# nasm -f elf -g ./src/enigma/enigma.asm -o ./build/enigma/enigma.o
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/enigma/enigma.c -o ./build/enigma/enigma.o


run:
	qemu-system-x86_64 -hda ./bin/os.bin


clean:
	clear
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/os.bin
	rm -rf ${FILES}
	rm -rf ./build/kernel
