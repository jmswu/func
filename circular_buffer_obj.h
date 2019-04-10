/* 
 * File:   circular_buffer_obj.h
 * Author: james
 *
 * Created on 4 April 2019, 11:01 AM
 */

#ifndef CIRCULAR_BUFFER_OBJ_H
#define	CIRCULAR_BUFFER_OBJ_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

    // circular buffer object
    typedef struct {
        volatile void *obj; // pointer to object buffer
        volatile uint16_t head; // head position of object in the buffer
        volatile uint16_t tail; // tail position of object in the buffer
        volatile uint16_t obj_max; // maximum number of objects that can stored in the buffer
        volatile uint16_t obj_count; // number of objects stored in the buffer
        volatile uint16_t obj_size; // size of one object in bytes
    } circular_buffer_obj_t;

    // set up circular buffer memory, all buffer need to be setup first
    // a user need to declar a circular buffer structure, then reserve 
    // some memory for the actuall buffer, this function will combine those
    // two and create a circular buffer.
    // 
    // @param *buff     - pointer to circular buffer
    // @param *obj      - pointer to object array use in this circular buffer
    // @param obj_max   - maximum number of objects that can stored in the buffer
    // @param obj_size  - size of one object in bytes
    void cbuff_obj_init(volatile circular_buffer_obj_t *buff, volatile void *obj, uint16_t obj_max, uint16_t obj_size);

    // check if a circular buffer is empty
    // @param *buff - pointer to a circular buffer
    int cbuff_obj_isEmpty(volatile circular_buffer_obj_t *buff);

    // check if a circular buffer is full
    // @param *buff - pointer to a circular buffer
    int cbuff_obj_isFull(volatile circular_buffer_obj_t *buff);


    // add one byte into a circular buffer
    // @param *buff     - pointer to a circular buffer
    // @param *obj      - pointer to the object to be added to the buffer
    void cbuff_obj_put(volatile circular_buffer_obj_t *buff, volatile void *obj);

    // get one byte from a circular buffer
    // @param *buff     - pointer to a circular buffer
    // @param *obj      - pointer to the object to be returned to the buffer
    void cbuff_obj_get(volatile circular_buffer_obj_t *buff, volatile void *obj);

#ifdef	__cplusplus
}
#endif

#endif	/* CIRCULAR_BUFFER_OBJ_H */

