
#include "circular_buffer_obj.h"
#include <string.h>

void cbuff_obj_init(volatile circular_buffer_obj_t *buff, volatile void *obj, uint16_t obj_max, uint16_t obj_size) {
    // check if buffer is null
    if (buff == 0) return;
    if (obj == 0) return;

    // disable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    uint8_t saved_ipl;
    SET_AND_SAVE_CPU_IPL(saved_ipl, 7);
    // ---------------------------------------  
    
    buff->obj = obj;
    buff->head = 0U;
    buff->tail = 0U;
    buff->obj_max = obj_max;
    buff->obj_count = 0U;
    buff->obj_size = obj_size;
    
    // enable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    RESTORE_CPU_IPL(saved_ipl);
    // --------------------------------------- 

    return;
}

int cbuff_obj_isEmpty(volatile circular_buffer_obj_t *buff) {
    // check if buffer is null
    if (buff == 0) return 1;

    int result;

    // disable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    uint8_t saved_ipl;
    SET_AND_SAVE_CPU_IPL(saved_ipl, 7);
    // ---------------------------------------  

    if (buff->obj_count == 0U) {
        result = 1;
    } else {
        result = 0;
    }

    // enable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    RESTORE_CPU_IPL(saved_ipl);
    // --------------------------------------- 

    return result;
}

int cbuff_obj_isFull(volatile circular_buffer_obj_t *buff) {
    // check if buff is null
    if (buff == 0) return 0;

    int result;

    // disable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    uint8_t saved_ipl;
    SET_AND_SAVE_CPU_IPL(saved_ipl, 7);
    // ---------------------------------------

    if (buff->obj_count == buff->obj_max) {
        result = 1;
    } else {
        result = 0;
    }

    // enable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    RESTORE_CPU_IPL(saved_ipl);
    // ---------------------------------------

    return result;
}

void cbuff_obj_put(volatile circular_buffer_obj_t *buff, volatile void *obj) {
    // make sure buffer is not null
    if (buff == 0) return;
    if (obj == 0) return;

    // disable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    uint8_t saved_ipl;
    SET_AND_SAVE_CPU_IPL(saved_ipl, 7);
    // ---------------------------------------

    // put one byte into the buffer
    uint16_t offset = 0;
    uint8_t *pBuff = 0;
    uint8_t *pObj = 0;
    offset = buff->head * buff->obj_size;
    pBuff = (uint8_t *) buff->obj;
    pObj = (uint8_t *) obj;
    memcpy(pBuff + offset, pObj, buff->obj_size);

    // point to next location
    buff->head++;

    // check for over flow
    if ((buff->head) >= (buff->obj_max)) {
        buff->head = 0;
    }
    
    // increase object counter
    buff->obj_count++;

    // enable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    RESTORE_CPU_IPL(saved_ipl);
    // ---------------------------------------

    return;
}

void cbuff_obj_get(volatile circular_buffer_obj_t *buff, volatile void *obj){
    // make sure buff is valid
    if (buff == 0) return;
    if (obj == 0) return;
    
    // disable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    uint8_t saved_ipl;
    SET_AND_SAVE_CPU_IPL(saved_ipl, 7);
    // --------------------------------------- 
    
    // get one byte
    uint16_t offset = 0;
    uint8_t *pObj = 0;
    uint8_t *pBuff = 0;
    pObj = (uint8_t *)obj;
    pBuff = (uint8_t *)buff->obj;
    offset = buff->obj_size * buff->tail;
    memcpy(pObj, pBuff + offset, buff->obj_size);
    
    // point to next location
    buff->tail++;
    
    // check over flow
    if ((buff->tail) >= (buff->obj_max)) buff->tail = 0;
    
    // decrease data counter
    buff->obj_count--;
    
    // enable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    RESTORE_CPU_IPL(saved_ipl);
    // ---------------------------------------
    
    return;
}
