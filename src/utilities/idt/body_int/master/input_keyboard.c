
// definizione tastiera italiana standard QZERTY
#include "config.h"
#include "utilities/idt/body_int/master/input_keyboard.h"
#include "utilities/idt/body_int/master/keyboard_layer.h"


uchar keyboard_map_QZERTY[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', 141, '\b', '\t', /* 0x00 - 0x0F */
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 138, '+', '\n', 0,             /* 0x10 - 0x1F */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 149, 133, 151, 0, '\\',             /* 0x20 - 0x2F */
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, '*', 0, ' ', 0, 0, 0, 0, 0, /* 0x30 - 0x3F */
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',               /* 0x40 - 0x4F */
    '2', '3', '0', '.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         /* 0x50 - 0x5F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                 /* 0x60 - 0x6F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0                                  /* 0x70 - 0x7F */
};


volatile uchar tmp_char_container;
volatile u8 new_char_written;

static volatile u8 extended = 0;


KB_FLAGS f_t = { 0 };


static inline u8 gestisci_special_case(u8 scancode)
{
    if (extended && scancode == FRECCIA_SINISTRA) {
        if (f_t.ctrlleft)
            f_t.change_page_shell_left = 1;
        extended = 0;
        return 1;
    }

    if (extended && scancode == FRECCIA_DESTRA) {
        if (f_t.ctrlleft)
            f_t.change_page_shell_right = 1;

        extended = 0;
        return 1;
    }

    if (scancode == CTRL_LEFT_RELEASED) {
        extended = 0;
        f_t.ctrlleft = 0;
        return 1;
    }

    if (RELEASE_KEY(scancode))
        return 1;

    return 0;
}


void gestisci_scancode_from_controller(u8 scancode)
{
    if (scancode == 0xE0) {
        extended = 1;
        return;
    }

    if (gestisci_special_case(scancode))
        return;

    if (scancode == CTRL_LEFT_PRESS && !f_t.ctrlleft) {
        f_t.ctrlleft = 1;
        return;
    }

    // keyboard_map_<tipo tastiera> definita in enigma/keyboard.h (e' definito solo QZERTY)
    tmp_char_container = keyboard_map_QZERTY[scancode];

    if (tmp_char_container >= '0' && tmp_char_container <= '4')
        return;  // caso fase di setup

    if (tmp_char_container >= 'a' && tmp_char_container <= 'z')
        tmp_char_container -= 32;

    if (tmp_char_container >= 'A' && tmp_char_container <= 'Z')
        new_char_written = 1;
}
