
#ifndef RTC_OROLOGIO_H
#define RTC_OROLOGIO_H

#include "config.h"

extern void init_hardware_rtc();
extern void do_rtc();

struct tempo_t{
    u8 sec;
    u8 min;
    u8 ore;
    u8 rtc_dirty;
};

extern struct tempo_t t;
extern void set_rtc_dirty(struct tempo_t *t, u8 new_value);
extern void rtc_get_time(struct tempo_t *t);

extern struct tempo_t* get_tempo();
extern volatile u8 rtc_dirty;


#endif
