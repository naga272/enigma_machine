
#include "utilities/io/io.h"
#include "utilities/disk/disk.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/memory/heap/malloc.h"
#include "errors_no.h"


struct disk disk;


O3 static inline void ata_wait_ready(void)
{
    u8 s;
    do {
        s = insb(ATA_STATUS);
        if (s & ATA_ERR)
            return;
    } while (s & ATA_BSY);
}


O3 static inline void ata_wait_drq(void)
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


O3 i32 disk_read_sector(i32 lba, i32 total, void* buf)
{
    ushort* ptr = (ushort*) buf;

    for (i32 s = 0; s < total; s++) {
        // check dello stato
        if (insb(ATA_STATUS) & ATA_BSY) {
            // attesa 30 secondi (timeout)
            for (int timeout = 0; timeout < 30000; timeout++) {
                if (!(insb(ATA_STATUS) & ATA_BSY))
                    break;
                // delay
                for (volatile int i = 0; i < 1000; i++);
            }
            if (insb(ATA_STATUS) & ATA_BSY)
                return -1; // timeout
        }

        // select drive e LBA
        outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));

        // 400ns delay
        insb(ATA_STATUS);
        insb(ATA_STATUS);
        insb(ATA_STATUS);
        insb(ATA_STATUS);

        outb(ATA_SECCOUNT, 1);
        outb(ATA_LBA_LOW, lba & 0xFF);
        outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
        outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
        outb(ATA_COMMAND, READ_SECTOR);

        //attesa dei dati pronti
        u8 status;
        int timeout = 1000000; // faccio un piccolo timeout

        do {
            status = insb(ATA_STATUS);
            if (status & ATA_ERR) {
                insb(ATA_ERROR);
                return -1;
            }
            timeout--;

            if (timeout <= 0) 
                return -1;  // Timeout
        } while ((status & ATA_BSY) || !(status & ATA_DRQ));

        // lettura di 2 bytes alla volta
        for (int i = 0; i < 256; i++)
            *ptr++ = insw(ATA_DATA);

        lba++;
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

