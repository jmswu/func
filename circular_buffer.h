/* 
 * File:   circular_buffer.h
 * Author: james
 *
 * Created on 16 June 2018, 4:41 PM
 */

#ifndef CIRCULAR_BUFFER_H
#define	CIRCULAR_BUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <xc.h>
    
    typedef struct{
        uint8_t *data;
        uint8_t head;
        uint8_t tail;
        uint8_t size;
        uint8_t data_counter;
    }circular_buffer_t;
    
    void CBuff_Initial(volatile circular_buffer_t *buff, uint8_t *data, uint8_t size);
    uint8_t CBuff_isEmpty(volatile circular_buffer_t *buff);
    uint8_t CBuff_isFull(volatile circular_buffer_t *buff);
    void CBuff_put(volatile circular_buffer_t *buff, uint8_t data);
    uint8_t CBuff_get(volatile circular_buffer_t *buff);



#ifdef	__cplusplus
}
#endif

#endif	/* CIRCULAR_BUFFER_H */

