# EnigmaOS

**EnigmaOS** è un sistema operativo a 32 bit minimale scritto in Assembly e C, progettato per emulare il comportamento della storica macchina crittografica Enigma utilizzata durante la Seconda Guerra Mondiale.

## Contesto Storico

La macchina **Enigma** fu utilizzata dalle forze armate tedesche per cifrare messaggi sensibili. Era considerata inizialmente "invincibile" dal punto di vista crittografico, ma venne infine decifrata grazie al lavoro di matematici polacchi e britannici.

Questo sistema operativo è un omaggio a quel contesto storico, simulando la logica interna della macchina Enigma direttamente a basso livello, senza dipendere da sistemi operativi esterni.


## Funzionalità Principali

- Emulazione dei **rotori** e del **riflettore**.
- Input utente tramite interfaccia a linea di comando testuale.
- Algoritmo di cifratura fedele alla logica Enigma.
- Interfaccia interattiva minimale.


## Architettura Tecnica

- **Bootloader**: scritto in Assembly x86 (16-bit). Lo trovi all'interno della cartella ./src/boot/. Serve per switchare il sistema operativo dalla real mode alla protected mode, caricare il kernel in ram e eseguire il jmp.
- **Kernel**: l'entry point del kernel e' il file ./src/kernel.asm. Da quel file switcho tutto il contesto all'interno del file ./src/kernel.c.
- **Settings schermo**: la configurazione per la visualizzazione della schermata si trova all'interno della directory ./src/video/
- **Interrupts**: gli interrupt sono gestiti interamente all'interno della cartella ./src/idt/.


## Requisiti

- [x] **cross C compiler**
- [x] **NASM** compiler 
- [x] **Make** 
- [x] **QEMU** o **VirtualBox**
- [ ] Python (solo se usato per script di configurazione opzionali)
- [ ] Preferibilmente Macchina Linux (su Windows e' un bagno di sangue)


## Come Compilare ed Eseguire

```bash
# givvare permessi a build.sh per poter compilare 
sudo chmod 777 ./build.sh && ./build.sh
# esegue qemu
make run
```

## Fonti

- Wikipedia: https://en.wikipedia.org/wiki/Enigma_machine
- OsDev: https://wiki.osdev.org/Expanded_Main_Page
