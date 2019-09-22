# STM32 EEPROM emulation 

##First: define sections in Linker file
```
# RAM Region

	.eeprom-flash : {
		. = ALIGN(1024);
		__eeprom_start__ = .;
        . += (__eepram_end__ - __eepram_start__);
		__eeprom_end__ = .;
		. = ALIGN(1024);
		__eeprom_aligned_end__ = .;

	} > ROM

# AND ROM

    .eeprom : AT (__eeprom_start__) {
            __eepram_start__ = .;
            KEEP(*(.eeprom))
    		KEEP(*(.eeprom*))
    		__eepram_end__ = . ;
    } > RAM


```
##Second: Define EEMEM data
```
#include <ee.h>
EEMEM uint32_t eeprom_variable = 0x55abcdef;
```

##Third: Load and save data
* ```eemem_load();``` loads data from __rom__ section to __ram__
* ```eemem_save();``` saves data from __ram__ section to __rom__
