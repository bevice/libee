cmake_minimum_required(VERSION 3.8 FATAL_ERROR)


set(LIBEEPROM_HEADERS
        libee.h
        )

set(LIBEEPROM_SRC
        libee.c
        )

add_library(ee
        ${LIBEEPROM_HEADERS}
        ${LIBEEPROM_SRC}
        )

target_include_directories(ee
        PUBLIC .
        )

## TODO: а нужен ли хал? Неа, хватит и CMSIS, но у меня нет отдельного тагета =(
target_link_libraries(ee stm32f1xx_hal)
