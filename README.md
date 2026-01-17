# EnigmaOS

![Language](https://img.shields.io/badge/Language-C-black?style=flat) 
![Language](https://img.shields.io/badge/Language-asm-brown?style=flat)
![Language](https://img.shields.io/badge/Language-ld-white?style=flat)
![Language](https://img.shields.io/badge/Language-bash-green?style=flat) 
![Language](https://img.shields.io/badge/Language-python-yellow?style=flat) 
![Testing](https://img.shields.io/badge/Test-Pass-true)

**EnigmaOS** è un sistema operativo a 32 bit minimale scritto in Assembly e C, progettato per emulare il comportamento della storica macchina crittografica Enigma utilizzata durante la Seconda Guerra Mondiale.

## Contesto Storico

La macchina **Enigma** fu utilizzata dalle forze armate tedesche per cifrare messaggi sensibili. Era considerata inizialmente "invincibile" dal punto di vista crittografico, ma venne infine decifrata grazie al lavoro di matematici polacchi e britannici.

Questo sistema operativo è un omaggio all'enigma della seconda guerra mondiale, simulando la logica interna della macchina Enigma direttamente a basso livello, senza dipendere da sistemi operativi esterni.


## Funzionalità Principali

- Emulazione della **plugboard**, dei **rotori** e del **riflettore** (vedi file in `src/utilities/enigma/enigma.c` e `src/utilities/enigma/enigma.h`).
- Input utente tramite interfaccia a linea di comando testuale.
- Algoritmo di cifratura fedele alla logica Enigma.
- Interfaccia interattiva minimale.

## Funzionalità aggiuntive

Ho aggiunto dei comandi base come `QUIT` e `RELOAD` per spegnere o riavviare la macchina.

## Requisiti

- [x] **Cross C compiler**
- [x] **NASM** assembler 
- [x] **Make** 
- [x] **QEMU**
- [ ] Macchina Linux


## Come Compilare ed Eseguire

```bash
# passare permessi a build.sh per poter compilare 
sudo chmod 777 ./build.sh && ./build.sh
# esegue qemu
make run
```

## Dimostrazione pratica

video dimostrazione: https://youtu.be/xO2j2PmpR_k

## Fonti

- Wikipedia: https://en.wikipedia.org/wiki/Enigma_machine
- OsDev: https://wiki.osdev.org/Expanded_Main_Page
- Chromium: https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/syscalls/#x86-32-bit
- Kernel source code Linux: https://github.com/torvalds/linux/
- szhou42: https://github.com/szhou42/osdev

