# EnigmaOS

![EnigmaOS Banner](https://your-image-link.com/banner.png) <!-- Replace with an actual image link -->

## 🔐 About

**EnigmaOS** is an operating system that emulates the behavior of the **Enigma machine**. Once launched in a virtualizer, key presses on your keyboard will be displayed on the screen, encrypted according to the Enigma machine's algorithm.

## ⚙️ Requirements

Before running EnigmaOS, ensure you have the following:

- A **32-bit or higher** CPU architecture
- **QEMU** virtualizer
- **C cross compiler** (Refer to [OSDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler) for installation and setup)
- **NASM** assembler
- **Make** command (installable via `apt` on Debian-based systems)

## 🚀 Installation & Execution

1. Grant execution permissions to the `bash.sh` script and run it:
   ```sh
   chmod +x bash.sh && ./bash.sh
   ```
   *(This will automatically compile EnigmaOS.)*

2. Run the OS in QEMU:
   ```sh
   make run
   ```

## 📜 License

This project is open-source. Feel free to explore, modify, and improve it.

## 👤 Author

- **naga272**  

---

_Enjoy cryptographic nostalgia with EnigmaOS! 🛡️🔢_

