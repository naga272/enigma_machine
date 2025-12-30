# EnigmaOS

![Language](https://img.shields.io/badge/Language-C-black?style=flat) 
![Language](https://img.shields.io/badge/Language-asm-brown?style=flat)
![Language](https://img.shields.io/badge/Language-ld-white?style=flat)
![Language](https://img.shields.io/badge/Language-bash-green?style=flat) 
![Testing](https://img.shields.io/badge/Test-Pass-true)

**EnigmaOS** è un sistema operativo a 32 bit minimale scritto in Assembly e C, progettato per emulare il comportamento della storica macchina crittografica Enigma utilizzata durante la Seconda Guerra Mondiale.

## Contesto Storico

La macchina **Enigma** fu utilizzata dalle forze armate tedesche per cifrare messaggi sensibili. Era considerata inizialmente "invincibile" dal punto di vista crittografico, ma venne infine decifrata grazie al lavoro di matematici polacchi e britannici.

Questo sistema operativo è un omaggio all'enigma della seconda guerra mondiale, simulando la logica interna della macchina Enigma direttamente a basso livello, senza dipendere da sistemi operativi esterni.


## Funzionalità Principali

- Emulazione della **plugboard**, dei **rotori** e del **riflettore** (vedi file in `src/enigma/enigma.c` e `src/enigma/enigma.h`).
- Input utente tramite interfaccia a linea di comando testuale.
- Algoritmo di cifratura fedele alla logica Enigma.
- Interfaccia interattiva minimale.

## Requisiti

- [x] **Cross C compiler**
- [x] **NASM** assembler 
- [x] **Make** 
- [x] **QEMU**
- [ ] Preferibilmente Macchina Linux (su Windows provateci pure ma vi dico che e' un bagno di sangue)


## Come Compilare ed Eseguire

```bash
# passare permessi a build.sh per poter compilare 
sudo chmod 777 ./build.sh && ./build.sh
# esegue qemu
make run
```

## Dimostrazione pratica

video dimostrazione: https://youtu.be/-zRdcrr9HHw

## Fonti

- Wikipedia: https://en.wikipedia.org/wiki/Enigma_machine
- OsDev: https://wiki.osdev.org/Expanded_Main_Page
- Kernel source code Linux: https://github.com/torvalds/linux/
