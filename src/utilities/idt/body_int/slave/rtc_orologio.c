#include "utilities/io/io.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"


O3 static inline void rtc_wait_update_end()
{
    while (1) {
        outb(0x70, 0x0A);
        if (!(insb(0x71) & 0x80))
            break;
    }
}


O3 static inline u8 rtc_read(u8 reg)
{
    outb(0x70, reg);
    return insb(0x71);
}


O3 static inline u8 bcd_to_bin(u8 v)
{
    // converte i dati da binary-coded-decimal in binario
    return (v & 0x0F) + ((v >> 4) * 10);
}


O3 static inline u8 rtc_get_sec_utc()
{
    return bcd_to_bin(rtc_read(0x00));
}


O3 static inline u8 rtc_get_min_utc()
{
    return bcd_to_bin(rtc_read(0x02));
}


O3 static inline u8 rtc_get_ore_utc()
{
    return bcd_to_bin(rtc_read(0x04));
}


O3 void rtc_get_time(struct tempo_t *t)
{
    // alla conversione devo aggiungere il timezone
    t->sec = rtc_get_sec_utc() + 17;

    if (t->sec >= 60)
        t->sec = t->sec % 60;

    t->min = rtc_get_min_utc() + 4;

    /* 
    *   se t->min si trova a 59 e faccio + 4 esce fuori 63,
    *   e quindi finisco per stampare in output HH:63:SS
    * */
    if (t->min >= 60)
        t->min = t->min % 60;

    t->ore = rtc_get_ore_utc() + 1;

    if (t->ore >= 24)
        t->ore = t->ore % 24;
}


O3 void set_rtc_dirty(struct tempo_t *t, u8 new_value)
{
    t->rtc_dirty = new_value;
}


O3 void do_rtc()
{
    rtc_wait_update_end();
}


O3 void init_hardware_rtc()
{
    // per far funzionare l'IRQ8 devo prima abilitare IRQ2 
    outb(0x21, insb(0x21) & ~0x04);

    // poi sblocco irq8
    outb(0xA1, insb(0xA1) & ~0x01);

    // configurazione RTC
    outb(0x70, 0x8B);
    u8 regB = insb(0x71);
    outb(0x70, 0x8B);
    outb(0x71, regB | 0x40);  // Abilita periodic interrupt (bit 6)

    // impostazione della frequenza
    outb(0x70, 0x8A);
    u8 regA = insb(0x71);
    outb(0x70, 0x8A);
    outb(0x71, (regA & 0xF0) | 0x0F);  // 2Hz (valore 15)
    
    // bisogna leggere register C per pulire eventuali interrupt in coda
    outb(0x70, 0x0C);
    insb(0x71);
}
