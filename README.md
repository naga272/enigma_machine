# EnigmaOS

## 🔐 About the project

**EnigmaOS** è un sistema operativo che emula il comportamento della macchina Enigma. Una volta avviato tramite virtualizzatore come qemu o virtual box, si aprirà una schermata dove sarà possibile premere dei tasti tramite la tastiera hw. I tasti premuti vengono criptati secondo il criterio dell'algoritmo della macchina Enigma vera e propria.


## Funzionamento della macchina enigma
Fu un dispositivo elettromeccanico per cifrare messaggi che fu usato dai tedeschi durante la seconda guerra mondiale. 
All'epoca veniva considerata una delle macchine migliori per la crittografia, un vero rompicapo.



## ⚙️ Requirements

- A **32-bit or higher** CPU architecture
- **QEMU** virtualizzatore
- **C cross compiler** (guarda [OSDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler) per il setup)
- **NASM** assembler
- **Make** comando (installabile tramite `apt` su Unix-like system)

## 🚀 Installazione e Esecuzione

1. Givva i permessi al file `bash.sh` script e eseguilo:
   ```sh
   chmod +x bash.sh && ./bash.sh
   ```
   *(questo produrrà in automatico i file binari)*

2. Run the OS in QEMU:
   ```sh
   make run
   ```

## 📜 License

Questo progetto è open-source, siete liberi di modificare come volete il progetto

## 👤 Author

- **naga272**
