#ifndef GDT_H
#define GDT_H

#include "libc/stdint.h"
/*
    Sources:
    https://www.youtube.com/watch?v=jwulDRMQ53I&t=10s&ab_channel=OliveStem
    https://wiki.osdev.org/Global_Descriptor_Table
    https://wiki.osdev.org/Global_Descriptor_Table#Structure
*/

struct gdt_entry {
    uint16_t limit_low;         // The lower 16 bits of the limit.
    uint16_t base_low;          // The lower 16 bits of the base.
    uint8_t base_middle;        // The next 8 bits of the base.
    uint8_t access;             // Access flags, determine what ring this segment can be used in.
    uint8_t flags;              // Flags. Determines what type of segment this is.
    uint8_t base_high;          // The last 8 bits of the base.
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;             // The upper 16 bits of all selector limits.
    uint32_t base;              // The address of the first gdt_entry struct.
} __attribute__((packed));

void initGDT();
void setGDTGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
extern void gdt_flush(uint32_t);

#endif // GDT_H

