
#include "utilities/video/video.h"


i32 do_write(u32 fd, void* buf, size_t count)
{
    /* 
    *   Per il momento count e fd non mi servono,
    *   non ho ancora creato un VFS e non gestisco fd
    * **/
    char* tmp_buf = (char*) buf;

    while (*tmp_buf) {
        terminal_writechar(*tmp_buf, actual_color_terminal);
        tmp_buf++;
    }

    // (indirizzo finale - indirizzo iniziale) = len messaggio stampato
    return (i32) ((void*) tmp_buf - buf);
}
