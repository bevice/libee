#ifndef __LIBEE__
#define __LIBEE__

#define EEMEM volatile __attribute__((used, section(".eeprom")))
#ifndef FLASH_PAGE_SIZE
#define FLASH_PAGE_SIZE 1024U
#endif

void eemem_load();
void eemem_save();


#endif