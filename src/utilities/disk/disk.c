
#include "utilities/io/io.h"
#include "utilities/disk/disk.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/video/video.h"

// primary hard disk
struct disk enigmaos_disk;


static inline void ata_wait_ready(void)
{
    u8 s;
    do {
        s = insb(ATA_STATUS);
        if (s & ATA_ERR)
            return;
    } while (s & ATA_BSY);
}


static inline void ata_wait_drq(void)
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


O3 i32 disk_read_sector(i32 lba, i32 total, void* buf)
{
    ushort* ptr = (ushort*) buf;

    for (i32 s = 0; s < total; s++) {
        // Controllo iniziale di stato
        if (insb(ATA_STATUS) & ATA_BSY) {
            // Attendi fino a 30 secondi (timeout)
            for (int timeout = 0; timeout < 30000; timeout++) {
                if (!(insb(ATA_STATUS) & ATA_BSY))
                    break;
                // Piccolo delay
                for (volatile int i = 0; i < 1000; i++);
            }
            if (insb(ATA_STATUS) & ATA_BSY)
                return -1; // Timeout
        }

        // Seleziona drive e LBA
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

        // Attendi dati pronti con timeout
        u8 status;
        int timeout = 1000000; // Timeout più robusto
        do {
            status = insb(ATA_STATUS);
            if (status & ATA_ERR) {
                // Leggi registro errori per debug
                insb(ATA_ERROR);
                return -1;
            }
            timeout--;
            if (timeout <= 0) return -1; // Timeout
        } while ((status & ATA_BSY) || !(status & ATA_DRQ));

        // Leggi 256 word (512 byte)
        for (int i = 0; i < 256; i++) {
            *ptr++ = insw(ATA_DATA);
        }

        lba++;
    }
    return 0;
}


void disk_search_and_init()
{   
    memset(&enigmaos_disk, 0, sizeof(enigmaos_disk));
    enigmaos_disk.type = ENIGMAOS_DISK_TYPE_REAL;
    enigmaos_disk.sector_size = ENIGMAOS_SECTOR_SIZE;
}


struct disk* disk_get(i32 index)
{
    if (index != 0)
        return 0;

    return &enigmaos_disk;
}


i32 disk_read_block(struct disk *idisk, i32 lba, i32 total_blocks, void* buffer)
{
    if (idisk != &enigmaos_disk)
        return -EIO;

    return disk_read_sector(lba, total_blocks, buffer);
}
