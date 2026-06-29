#include "utilities/disk/streamer.h"
#include "utilities/memory/heap/malloc.h"


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("modulo per leggere dati da un disco come se fosse uno stream lineare");


/*
*   Invece di lavorare direttamente con settori e offset manuali,
*   mantiene internamente una posizione corrente nel disco.
*
*   Permette di:
*       - creare uno stream associato a un disco
*       - spostare la posizione corrente
*       - leggere una quantità arbitraria di byte
*       - chiudere e liberare lo stream
*
*   diskstreamer_read() traduce automaticamente la posizione corrente
*   in:
*       - numero del settore
*       - offset interno al settore
*
*   Se la quantità di byte richiesta supera la dimensione di un settore,
*   la funzione continua ricorsivamente la lettura dei settori successivi.
*
*   Questo livello di astrazione è utile per filesystem e parser di
*   strutture disco, evitando di dover gestire manualmente i blocchi.
*/


struct disk_stream* diskstreamer_new(i32 disk_id)
{
    /*
    *  @disk_id: identificatore del disco da cui creare lo stream
    *  Crea e inizializza una nuova struttura disk_stream associata
    *  al disco indicato. La posizione iniziale dello stream viene
    *  impostata a 0.
    */
    struct disk* disk = disk_get(disk_id);

    if (!disk)
        return 0;

    struct disk_stream* streamer = kcalloc(sizeof(struct disk_stream));
    streamer->pos = 0;
    streamer->disk = disk;
    return streamer;
}


i32 diskstreamer_seek(struct disk_stream* stream, i32 pos)
{
    /*
    *  @stream: stream di cui modificare la posizione corrente
    *  @pos: nuova posizione da impostare nello stream
    *  Imposta la posizione corrente dello stream al valore specificato.
    */
    stream->pos = pos;
    return 0;
}


i32 diskstreamer_read(struct disk_stream* stream, void* out, i32 total)
{
    /*
    *  @stream: stream da cui leggere i dati
    *  @out: buffer di destinazione in cui copiare i dati letti
    *  @total: numero totale di byte da leggere
    *
    *  Legge una quantità di byte dal disco partendo dalla posizione
    *  corrente dello stream. La funzione calcola il settore e l'offset
    *  corrispondenti, legge il settore in un buffer temporaneo e copia
    *  i dati nel buffer di output. Se la quantità richiesta supera la
    *  dimensione di un settore, continua la lettura ricorsivamente sui
    *  settori successivi.
    */
    i32 sector = stream->pos / ENIGMAOS_SECTOR_SIZE;
    i32 offset = stream->pos % ENIGMAOS_SECTOR_SIZE;
    i32 total_to_read = total;

    char buf[ENIGMAOS_SECTOR_SIZE];

    i32 overflow = (offset + total_to_read) >= ENIGMAOS_SECTOR_SIZE;
    
    if (overflow)
        total_to_read -= (offset+total_to_read) - ENIGMAOS_SECTOR_SIZE;

    i32 res = disk_read_block(stream->disk, sector, 1, buf);

    if (res < 0) 
        return res;

    for (i32 i = 0; i < total_to_read; i++)
        *(char*) out++ = buf[offset + i];

    stream->pos += total_to_read;

    if (overflow)
        res = diskstreamer_read(stream, out, total-total_to_read);

    return res;
}


void diskstreamer_close(struct disk_stream* stream)
{
    /*
    *  @stream: stream da liberare dalla memoria
    *  Libera la memoria associata alla struttura disk_stream.
    */
    kfree(stream);
}
