#ifndef KPRINTF_H
#define KPRINTF_H

#include "utilities/video/video.h"

#define KMSG "<3>"
#define KINFO "<2>"
#define KWARN "<1>"
#define KERR "<0>"

i32 kprintf(const char* fmt, ...);
extern i32 kprintf(const char* fmt, ...);

i32 kprintd(char* fmt);
extern i32 kprintd(char* fmt);

#endif