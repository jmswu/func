#include "flash.h"
#include <xc.h>

static const uint8_t FLASH_DATA[FLASH_BLOCK_SIZE] __at(FLASH_BLOCK_ADDR) = {FLASH_PRESET_VAL};

void Flash_erase(uint16_t addr) {
    /* load address into registers */
    TBLPTRU = 0U;
    TBLPTRH = (uint8_t) (addr >> 8U);
    TBLPTRL = (uint8_t) (addr & 0xFF);

    EECON1bits.WREN = 1U; // enable write
    EECON1bits.FREE = 1U; // enable erase operation
    di(); // disable interrupt
    EECON2 = 0x55; // write 0x55
    EECON2 = 0x0AA; // write 0x0AA
    EECON1bits.WR = 1U; // start erase (CPU stall)
    ei(); // re-enable interrupt
}

void Flash_write(uint16_t addr, uint8_t *data, uint8_t size) {

    /* load address into registers */
    TBLPTRU = 0U;
    TBLPTRH = (uint8_t) (addr >> 8U);
    TBLPTRL = (uint8_t) (addr & 0xFF);

    /* put data in to buffer */
    for (uint8_t i = 0; i < size; i++) {
        TABLAT = *data++;
        asm("TBLWT*+");
    }

    /* re-load address into registers */
    TBLPTRU = 0U;
    TBLPTRH = (uint8_t) (addr >> 8U);
    TBLPTRL = (uint8_t) (addr & 0xFF);

    EECON1bits.WREN = 1U; // enable write to memory
    di(); // disable interrupt
    EECON2 = 0x55; // write 0x55
    EECON2 = 0x0AA; // write 0x0AA
    EECON1bits.WR = 1U; // start program (CPU stall)
    ei(); // re-enable interrupts
    EECON1bits.WREN = 0U; // disable write to memory
}

void Flash_read(uint16_t addr, uint8_t *data, uint8_t size) {

    /* load address into registers */
    TBLPTRU = 0U;
    TBLPTRH = (uint8_t) (addr >> 8U);
    TBLPTRL = (uint8_t) (addr & 0xFF);

    /* read data */
    for (uint8_t i = 0; i < size; i++) {
        asm("TBLRD*+");
        *data++ = TABLAT;
    }
}