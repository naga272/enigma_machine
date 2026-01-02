
#ifndef RTC_OROLOGIO_H
#define RTC_OROLOGIO_H

#include "config.h"

extern void init_hardware_rtc();
extern void do_rtc();

struct tempo_t{
    u8 sec;     /* registro 0x00 */
    u8 min;     /* registro 0x02 */
    u8 ore;     /* registro 0x04 */
    u8 giorno;  /* registro 0x06 */
    u8 mese;    /* registro 0x08 */
    u8 anno;    /* registro 0x09 */
    u8 rtc_dirty;   // flag per dire se l'orario va aggiornato o meno
};


extern struct tempo_t t;
extern void set_rtc_dirty(struct tempo_t *t, u8 new_value);
extern void rtc_get_time(struct tempo_t *t);

extern struct tempo_t* get_tempo();
extern volatile u8 rtc_dirty;


#endif
