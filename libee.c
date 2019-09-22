
#include <stm32f1xx.h>
#include <stdint.h>
#include <stddef.h>
#include "libee.h"

static void ee_memcpy(const void *dst, const void *src, size_t size);

extern char __eeprom_start__;
extern char __eeprom_end__;
extern char __eepram_start__;
extern char __eepram_end__;

extern void *__FLASH_PAGE_SIZE__; // addr contents size


void eemem_load() {

    size_t size = &__eeprom_end__ - &__eeprom_start__;
    char *src_ptr = (char *) &__eeprom_start__;
    char *dst_ptr = (char *) &__eepram_start__;
    while (size--)
        *dst_ptr++ = *src_ptr++;
    asm("nop");

}

void eemem_save() {
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
    if (!(FLASH->CR & FLASH_CR_LOCK)) {
        // Сотрем все нахер
        char *ptr = &__eeprom_start__;

        while (ptr < &__eeprom_end__) {
            FLASH->CR |= FLASH_CR_PER;
            FLASH->AR = (uint32_t) (ptr);
            FLASH->CR |= FLASH_CR_STRT;
            while (FLASH->SR & FLASH_SR_BSY);
            ptr += (uint32_t) (&__FLASH_PAGE_SIZE__);
        }
        FLASH->CR &= ~FLASH_CR_PER;
        ee_memcpy(&__eeprom_start__, &__eepram_start__, &__eepram_end__ - &__eepram_start__);
        FLASH->CR |= FLASH_CR_LOCK; // заперли
    }
}


void ee_memcpy(const void *dst, const void *src, size_t size) {
    size >>= 1;  // как два байта переслать
    uint16_t *s = (uint16_t *) src;
    uint16_t *d = (uint16_t *) dst;
    FLASH->CR |= FLASH_CR_PG;
    while (size--) {
        while (FLASH->SR & FLASH_SR_BSY);
        *d++ = *s++;
    }
}