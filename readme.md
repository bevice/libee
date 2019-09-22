# STM32 EEPROM emulation 

## First: define sections in a linker file
_Check ```__FLASH_PAGE_SIZE__``` value_

```
# RAM Region
__FLASH_PAGE_SIZE__ = 1024;

    .eeprom : AT (__eeprom_start__) {
            __eepram_start__ = .;
            KEEP(*(.eeprom))
    		KEEP(*(.eeprom*))
    		__eepram_end__ = . ;
    } > RAM


# AND ROM

	.eeprom-flash : {
		. = ALIGN(__FLASH_PAGE_SIZE__);
		__eeprom_start__ = .;
        . += (__eepram_end__ - __eepram_start__);
		__eeprom_end__ = .;
		. = ALIGN(__FLASH_PAGE_SIZE__);
		__eeprom_aligned_end__ = .;

	} > ROM

```
## Second: Define EEMEM data
```
#include <ee.h>
EEMEM uint32_t eeprom_variable = 0x55abcdef;
```

## Third: Load and save data
* ```eemem_load();``` loads data from __rom__ section to __ram__
* ```eemem_save();``` saves data from __ram__ section to __rom__
