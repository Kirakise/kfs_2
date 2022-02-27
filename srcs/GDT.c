#include "GDT.h"
extern void loadgdt(void);
struct GDT_struct gdt[5];
struct GDTR_struct gdtr;

static void setgdt(uint8 i, uint16 base, uint8 mid, uint8 high, uint16 limit, uint8 access, uint8 gran)
{
  gdt[i].highbase = high;
  gdt[i].acess = access;
  gdt[i].base = base;
  gdt[i].limit = limit;
  gdt[i].midbase = mid;
  gdt[i].granularity = gran;
}

void make_gdt(void){
  setgdt(0, GET_LOW(GDT_BASE), GET_MID(GDT_BASE), GET_HIGH(GDT_BASE),
      0x0, 0x0, 0x0);
  setgdt(1, GET_LOW(GDT_BASE), GET_MID(GDT_BASE), GET_HIGH(GDT_BASE), 
      0xffff, 0b10011010, 0xCF); //kern code
  setgdt(2, GET_LOW(GDT_BASE), GET_MID(GDT_BASE), GET_HIGH(GDT_BASE),
      0xffff, 0b10010010, 0xCF); //kern data
  //setgdt(3, GET_LOW(GDT_BASE), GET_MID(GDT_BASE), GET_HIGH(GDT_BASE), 
    //  0xffff, 0b10010010, 0xCF); //kern stack
  setgdt(3, GET_LOW(GDT_BASE), GET_MID(GDT_BASE), GET_HIGH(GDT_BASE), 
      0xffff, 0b11111110, 0xCF); //user code
  setgdt(4, GET_LOW(GDT_BASE), GET_MID(GDT_BASE), GET_HIGH(GDT_BASE), 
      0xffff, 0b11110110, 0xCF); //user data 
  //setgdt(6, GET_LOW(GDT_BASE), GET_MID(GDT_BASE), GET_HIGH(GDT_BASE), 
    //  0xffff, 0b11110110, 0xCF); //user stack
  
  gdtr.base = (uint32)&gdt;
  gdtr.limit = (sizeof(struct GDT_struct) * 5) - 1;

  loadgdt();
}

