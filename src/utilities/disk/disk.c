
#include "utilities/io/io.h"
#include "utilities/disk/disk.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/memory/heap/malloc.h"
#include "errors_no.h"


/*
 * Driver ATA PIO per accesso a basso livello al disco.
 *
 * Gestisce:
 * - lettura di settori
 * - scrittura di settori
 * - inizializzazione del disco
 * - recupero del disco principale del sistema
 *
 * Il modulo comunica direttamente con il controller ATA tramite
 * porte I/O usando outb(), insb(), outw() e insw().
 *
 * ata_wait_ready():
 * - attende che il controller non sia occupato
 * - interrompe l'attesa in caso di errore ATA
 *
 * ata_wait_drq():
 * - attende che il controller segnali dati pronti
 * - verifica anche eventuali errori
 *
 * disk_read_sector():
 * - legge uno o più settori tramite modalità ATA PIO
 * - configura LBA, comando e numero di settori
 * - attende che il disco sia pronto
 * - legge 256 word (512 byte) per settore
 *
 * disk_write_sector():
 * - scrive uno o più settori sul disco
 * - invia i dati 16 bit alla volta
 * - esegue un flush finale per assicurare la scrittura
 *
 * disk_search_and_init():
 * - inizializza la struttura globale del disco
 * - imposta tipo, dimensione settore e filesystem rilevato
 *
 * disk_get():
 * - restituisce il disco principale se l'indice richiesto è valido
 *
 * disk_read_block():
 * - verifica che il disco richiesto sia quello gestito dal driver
 * - inoltra la lettura ai settori ATA
*/


struct disk disk;


O3 static inline ainline void ata_wait_ready(void)
{
    u8 s;
    do {
        s = insb(ATA_STATUS);
        if (s & ATA_ERR)
            return;
    } while (s & ATA_BSY);
}


O3 static inline ainline void ata_wait_drq(void)
{
    u8 s;
    for (;;) {
        s = insb(ATA_STATUS);
        if (s & ATA_ERR)
            return;
        if (!(s & ATA_BSY) && (s & ATA_DRQ))
            return;
    }
}


i32 disk_read_sector(i32 lba, i32 total, void* buf)
{
    outb(0x1F6, (lba >> 24) | 0xE0);
    outb(0x1F2, total);
    outb(0x1F3, (uchar)(lba & 0xff));
    outb(0x1F4, (uchar)(lba >> 8));
    outb(0x1F5, (uchar)(lba >> 16));
    outb(0x1F7, 0x20);

    u16* ptr = (u16*) buf;
    for (int b = 0; b < total; b++) {
        // Wait for the buffer to be ready
        char c = insb(0x1F7);
        while(!(c & 0x08))
            c = insb(0x1F7);

        // Copy from hard disk to memory
        for (int i = 0; i < 256; i++) {
            *ptr = insw(0x1F0);
            ptr++;
        }

    }
    return 0;
}


O3 i32 disk_write_sector(i32 lba, i32 total, void* buf)
{
    /* disk_write_sector
    *   @lba: numero intero che identifica un settore del disco
    *   @total: numero di blocchi che mi servono 
    *   @buffer: a partire da dove in ram carichiamo i settori 
    * */ 
    /* ==== outb(0x1F6, (lba >> 24) | 0xE0); ==== 
    * 
    */
    ushort *ptr = (ushort*) buf;

    ata_wait_ready();

    outb(ATA_SECCOUNT, total);
    outb(ATA_LBA_LOW, lba & 0xFF);
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
    outb(ATA_COMMAND, WRITE_SECTOR);
    outb(ATA_DRIVE, (lba >> 24) | 0xE0);

    for (i32 s = 0; s < total; s++) {
        ata_wait_drq();
        for (i32 i = 0; i < 256; i++) 
            outw(ATA_DATA, *ptr++);
    }

    outb(ATA_COMMAND, ATA_FLUSH);
    ata_wait_ready();

    return 0;
}


void disk_search_and_init()
{
    memset(&disk, 0, sizeof(disk));
    disk.id = 0;
    disk.type = ENIGMAOS_DISK_TYPE_REAL;
    disk.sector_size = ENIGMAOS_SECTOR_SIZE;
    disk.filesystem = fs_resolve(&disk);

}


struct disk* disk_get(i32 index)
{
    if (index != 0)
        return 0;
    
    return &disk;
}


i32 disk_read_block(struct disk* idisk, u32 lba, i32 total, void* buf)
{
    if (idisk != &disk)
        return -EIO;

    return disk_read_sector(lba, total, buf);
}

