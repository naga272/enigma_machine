UTILITIES = ./build/stdlib/stdlib.o ./build/string/string.o ./build/shell/command.o ./build/video/video.o ./build/book/book.o ./build/atomic/atomic.o

SETUP = ./build/setup/setup.o ./build/markov/markov.o

MASTER_IDT = ./build/idt/body_int/master/pit.o ./build/idt/body_int/master/input_keyboard.o
SLAVE_IDT = ./build/idt/body_int/slave/rtc_orologio.o
SYSCALL = ./build/idt/body_int/syscalls/syscall.o ./build/test_int80h.asm.o ./build/idt/body_int/syscalls/write/write.o ./build/idt/body_int/syscalls/reboot/reboot.o
IDT = ./build/idt/idt.asm.o ./build/idt/idt.o $(MASTER_IDT) $(SLAVE_IDT) $(SYSCALL)

HEAP = ./build/memory/kheap_creation.o ./build/memory/heap_creation.o ./build/memory/malloc.o

PAGING = ./build/memory/paging.o ./build/memory/paging.asm.o

NET_DRIVERS = ./build/net/drivers/rtl8139.o
NET = ./build/net/net.o $(NET_DRIVERS)
PCI = ./build/pci/pci.o $(NET)

DISK = ./build/fs/pparser.o ./build/disk/disk.o ./build/disk/streamer.o ./build/fs/file.o $(FAT16)
FAT16 = ./build/fs/fat/fat16.o

TASK = ./build/gdt/gdt.asm.o ./build/gdt/gdt.o ./build/task/tss.asm.o ./build/task/task.o

FILES = ./build/kernel.asm.o ./build/kernel.o $(TASK) $(HEAP) $(PAGING) $(UTILITIES) $(IDT) $(DISK) $(SETUP) $(PCI) ./build/io/io.asm.o ./build/enigma/enigma.o


INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc


all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=1048576 count=16 >> ./bin/os.bin
	sudo mount -t vfat ./bin/os.bin /mnt/d
	# Copy a file over
	sudo cp ./hello.txt /mnt/d
	sudo umount /mnt/d
./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o


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


./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o


./build/kernel.o: ./src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -I/usr/include/python3.12 -c ./src/kernel.c -o ./build/kernel.o


./build/io/io.asm.o: ./src/utilities/io/io.asm
	nasm -f elf -g ./src/utilities/io/io.asm -o ./build/io/io.asm.o


# ==== FILES FOR PROCESS SCHEDULER ====
./build/gdt/gdt.asm.o: ./src/utilities/gdt/gdt.asm
	nasm -f elf -g ./src/utilities/gdt/gdt.asm -o ./build/gdt/gdt.asm.o


./build/gdt/gdt.o: ./src/utilities/gdt/gdt.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/gdt/gdt.c -o ./build/gdt/gdt.o


./build/task/tss.asm.o: ./src/utilities/task/tss.asm
	nasm -f elf -g ./src/utilities/task/tss.asm -o ./build/task/tss.asm.o


./build/task/task.o: ./src/utilities/task/task.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/task/task.c -o ./build/task/task.o


# ==== FILES FOR HEAP ====
./build/memory/kheap_creation.o: ./src/utilities/memory/heap/kheap_creation.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/memory/heap/kheap_creation.c -o ./build/memory/kheap_creation.o


./build/memory/heap_creation.o: ./src/utilities/memory/heap/heap_creation.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/memory/heap/heap_creation.c -o ./build/memory/heap_creation.o


./build/memory/malloc.o: ./src/utilities/memory/heap/malloc.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/memory/heap/malloc.c -o ./build/memory/malloc.o


# ==== FILES FOR FS and FILES FOR ACCESS DISK ==== 

./build/fs/pparser.o: ./src/utilities/fs/pparser.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/fs/pparser.c -o ./build/fs/pparser.o

./build/setup/setup.o: ./src/utilities/setup/setup.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/setup/setup.c -o ./build/setup/setup.o


./build/disk/disk.o: ./src/utilities/disk/disk.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/disk/disk.c -o ./build/disk/disk.o


./build/disk/streamer.o: ./src/utilities/disk/streamer.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/disk/streamer.c -o ./build/disk/streamer.o


./build/fs/file.o: ./src/utilities/fs/file.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/fs/file.c -o ./build/fs/file.o


./build/fs/fat/fat16.o: ./src/utilities/fs/fat/fat16.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/fs/fat/fat16.c -o ./build/fs/fat/fat16.o


# ==== FILES FOR PAGING ====

./build/memory/paging.o: ./src/utilities/memory/paging/paging.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/memory/paging/paging.c -o ./build/memory/paging.o


./build/memory/paging.asm.o: ./src/utilities/memory/paging/paging.asm
	nasm -f elf -g ./src/utilities/memory/paging/paging.asm -o ./build/memory/paging.asm.o


# ==== DEFINIZIONE LIBRERIE STANDARD ====
./build/stdlib/stdlib.o: ./src/utilities/stdlib/stdlib.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/stdlib/stdlib.c -o ./build/stdlib/stdlib.o


./build/string/string.o: ./src/utilities/string/string.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/string/string.c -o ./build/string/string.o


./build/atomic/atomic.o: ./src/utilities/atomic/atomic.c
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/atomic/atomic.c -o ./build/atomic/atomic.o


####


./build/shell/command.o: ./src/utilities/shell/command.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/shell/command.c -o ./build/shell/command.o


./build/video/video.o: ./src/utilities/video/video.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/video/video.c -o ./build/video/video.o


./build/book/book.o: ./src/utilities/book/book.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/book/book.c -o ./build/book/book.o


./build/idt/body_int/master/pit.o: ./src/utilities/idt/body_int/master/pit.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/idt/body_int/master/pit.c -o ./build/idt/body_int/master/pit.o


./build/idt/body_int/master/input_keyboard.o: ./src/utilities/idt/body_int/master/input_keyboard.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/idt/body_int/master/input_keyboard.c -o ./build/idt/body_int/master/input_keyboard.o


./build/idt/body_int/slave/rtc_orologio.o: ./src/utilities/idt/body_int/slave/rtc_orologio.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/idt/body_int/slave/rtc_orologio.c -o ./build/idt/body_int/slave/rtc_orologio.o


./build/idt/idt.asm.o: ./src/utilities/idt/idt.asm
	nasm -f elf -g ./src/utilities/idt/idt.asm -o ./build/idt/idt.asm.o


./build/idt/idt.o: ./src/utilities/idt/idt.c 
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/idt/idt.c -o ./build/idt/idt.o

####

### SYSCALLS
./build/idt/body_int/syscalls/write/write.o: ./src/utilities/idt/body_int/syscalls/write/write.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/idt/body_int/syscalls/write/write.c -o ./build/idt/body_int/syscalls/write/write.o


./build/idt/body_int/syscalls/reboot/reboot.o: ./src/utilities/idt/body_int/syscalls/reboot/reboot.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/idt/body_int/syscalls/reboot/reboot.c -o ./build/idt/body_int/syscalls/reboot/reboot.o


./build/idt/body_int/syscalls/syscall.o: ./src/utilities/idt/body_int/syscalls/syscall.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/idt/body_int/syscalls/syscall.c -o ./build/idt/body_int/syscalls/syscall.o


# ==== PCI ====
./build/pci/pci.o: ./src/utilities/pci/pci.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/pci/pci.c -o ./build/pci/pci.o

# ==== NET ====
./build/net/net.o: ./src/utilities/net/net.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/net/net.c -o ./build/net/net.o

# ==== NET DRIVER ====
./build/net/drivers/rtl8139.o: ./src/utilities/net/drivers/rtl8139.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/net/drivers/rtl8139.c -o ./build/net/drivers/rtl8139.o

# ==== Markov ====
./build/markov/markov.o: ./src/utilities/markov/markov.c
	i686-elf-gcc $(INCLUDES) -I./src/video $(FLAGS) -std=gnu99 -c ./src/utilities/markov/markov.c -o ./build/markov/markov.o


# ==== TEST INT80H syscall ====
./build/test_int80h.asm.o: ./src/test_int80h.asm
	nasm -f elf -g ./src/test_int80h.asm -o ./build/test_int80h.asm.o

####

# ==== FILE X ENIGMA ALG ====
./build/enigma/enigma.o: ./src/utilities/enigma/enigma.c
	# nasm -f elf -g ./src/utilities/enigma/enigma.asm -o ./build/enigma/enigma.o
	i686-elf-gcc $(INCLUDES) -I./src/stdlib $(FLAGS) -std=gnu99 -c ./src/utilities/enigma/enigma.c -o ./build/enigma/enigma.o

####


run:
	qemu-system-x86_64 -hda ./bin/os.bin \
	-net nic,model=rtl8139 -net user \
	-vga std


generate_int: ./src/utilities/idt/body_int/syscalls/generate_base_syscall.py
	python3 ./src/utilities/idt/body_int/syscalls/generate_base_syscall.py


clean:
	clear
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/os.bin
	rm -rf ${FILES}
	rm -rf ./build/kernel
