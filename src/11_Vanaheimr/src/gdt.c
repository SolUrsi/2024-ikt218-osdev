#include "gdt.h"

extern void gdt_flush(uint32_t);

struct gdt_entry gdt_entries[5];
struct gdt_ptr gdt_ptr;

void initGDT(){
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    setGDTGate(0,0,0,0,0);                          // NULL segment
    setGDTGate(1,0,0xFFFFFFFF,0x9A,0xCF);           // Kernel Code segment
    setGDTGate(2,0,0xFFFFFFFF,0x92,0xCF);           // Kernel Data segment
    setGDTGate(3,0,0xFFFFFFFF,0xFA,0xCF);           // User Code segment
    setGDTGate(4,0,0xFFFFFFFF,0xF2,0xCF);           // User Data segment

    gdt_flush((uint32_t)&gdt_ptr);
}

void setGDTGate(uint32_t num, uint32_t base, uint32_t limit, 
uint8_t access, uint8_t gran){
    gdt.entries[num].base_low = (base & 0xFFFF);
    gdt.entries[num].base_middle = (base >> 16) & 0xFF;
    gdt.entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= gran & 0xF0;

    gdt_entries[num].access = access;
}

