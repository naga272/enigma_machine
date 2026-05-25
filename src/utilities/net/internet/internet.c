#include "utilities/net/internet/internet.h"


static u16 ip_checksum16(const void* data, u32 len) {
    const u16* p = (const u16*) data;
    u32 sum = 0;

    while (len > 1) {
        sum += *p++;
        len -= 2;
    }
    if (len) {
        u16 last = 0;
        *(u8*)&last = *(const u8*)p;
        sum += last;
    }
    // fold
    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);
    return (u16) ~sum;
}
