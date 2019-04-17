/* 
 * File:   flash.h
 * Author: james
 *
 * Created on 18 April 2019, 8:05 AM
 */

#ifndef FLASH_H
#define	FLASH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

#define FLASH_BLOCK_SIZE    (1024U) // flash minimum erase block size
#define FLASH_WRITE_SIZE    (64U)   // flash minimum write size 
#define FLASH_BLOCK_ADDR    (0x0400)// flash address use for permenent data storage
#define FLASH_PRESET_VAL    "secret_number"  // preset value to indicate there is no data is storage in the flash

    /*
     * erase a block of flash memory
     * @param addr  - address of the block of flash data that need to be erase
     */
    void Flash_erase(uint16_t addr);

    /*
     * write a block of data to the flash memory
     * @param addr  - starting address of the flash data need to be read
     * @param *data - pointer to where the data is from
     * @param size  - number of bytes to be write
     */
    void Flash_write(uint16_t addr, uint8_t *data, uint8_t size);
    
    /*
     * read a block of data from flash memory
     * @param addr  - starting address of the flash data need to be read
     * @param *data - pointer to where the data is stored
     * @param size  - number of bytes to be read
     */
    void Flash_read(uint16_t addr, uint8_t *data, uint8_t size);


#ifdef	__cplusplus
}
#endif

#endif	/* FLASH_H */

