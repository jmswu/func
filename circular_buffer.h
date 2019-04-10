/* 
 * File:   circular_buffer.h
 * Author: james
 *
 * Created on 12 December 2018, 9:34 AM
 */

#ifndef CIRCULAR_BUFFER_H
#define	CIRCULAR_BUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
    
    // circular buffer structure
    typedef struct{
        volatile uint8_t *data;          // pointer to buffer
        volatile uint16_t head;          // head position of data in the buffer
        volatile uint16_t tail;          // tail position of data in the buffer
        volatile uint16_t size;          // size of the buffer
        volatile uint16_t data_count;    // number of data stored in the buffer
    }circular_buffer_t;
    
    // set up circular buffer memory, all buffer need to be setup first
    // a user need to declar a circular buffer structure, then reserve 
    // some memory for the actuall buffer, this function will combine those
    // two and create a circular buffer.
    // 
    // @param *buff     - pointer to circular buffer
    // @param *data     - pointer to data array use in this circular buffer
    // @param size      - size the the *data
    void cbuff_init(volatile circular_buffer_t *buff, volatile uint8_t *data, uint16_t size);
    
    // check if a circular buffer is empty
    // @param *buff - pointer to a circular buffer
    int cbuff_isEmpty(volatile circular_buffer_t *buff);
    
    // check if a circular buffer is full
    // @param *buff - pointer to a circular buffer
    int cbuff_isFull(volatile circular_buffer_t *buff);
    
    // add one byte into a circular buffer
    // @param *buff     - pointer to a circular buffer
    // @param data      _ data to be added to the buffer
    void cbuff_put(volatile circular_buffer_t *buff, uint8_t data);
    
    // get one byte from a circular buffer
    // @param *buff     - pointer to a circular buffer
    uint8_t cbuff_get(volatile circular_buffer_t *buff);


#ifdef	__cplusplus
}
#endif

#endif	/* CIRCULAR_BUFFER_H */

