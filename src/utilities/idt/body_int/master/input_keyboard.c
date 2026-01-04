
// definizione tastiera italiana standard QZERTY
#include "config.h"
#include "utilities/idt/body_int/master/input_keyboard.h"
#include "utilities/idt/body_int/master/keyboard_layer.h"



volatile uchar tmp_char_container;
volatile u8 new_char_written;


void gestisci_scancode_from_controller(u8 scancode)
{
    if (RELEASE_KEY(scancode))
        return;   // ignoro il rilascio tasti

    // keyboard_map_<tipo tastiera> definita in enigma/keyboard.h (e' definito solo QZERTY)
    tmp_char_container = keyboard_map_QZERTY[scancode];

    if (tmp_char_container >= '0' && tmp_char_container <= '4')
        return;  // caso fase di setup

    if (tmp_char_container >= 'a' && tmp_char_container <= 'z')
        tmp_char_container -= 32;

    if (tmp_char_container >= 'A' && tmp_char_container <= 'Z')
        new_char_written = 1;
}
