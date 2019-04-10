#include "circular_buffer.h"

void cbuff_init(volatile circular_buffer_t *buff, volatile uint8_t *data, uint16_t size){
    // check if buffer is null
    if (buff == 0) return;
    if (data == 0) return;
    
    // disable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    uint8_t saved_ipl;
    SET_AND_SAVE_CPU_IPL(saved_ipl, 7);
    // ---------------------------------------
    
    buff->data = data;
    buff->head = 0U;
    buff->tail = 0U;
    buff->size = size;
    buff->data_count = 0U;
    
    // enable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    RESTORE_CPU_IPL(saved_ipl);
    // ---------------------------------------
    
    return;
}


int cbuff_isEmpty(volatile circular_buffer_t *buff){
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
    
    if (buff->data_count == 0U) {
        result = 1;
    }
    else {
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

int cbuff_isFull(volatile circular_buffer_t *buff){
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
    
    if (buff->data_count == buff->size) {
        result = 1;
    }
    else {
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

void cbuff_put(volatile circular_buffer_t *buff, uint8_t data){
    // make sure buffer is not null
    if (buff == 0) return;
    
    // disable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    uint8_t saved_ipl;
    SET_AND_SAVE_CPU_IPL(saved_ipl, 7);
    // ---------------------------------------
    
    // put one byte into the buffer
    buff->data[buff->head] = data;
    
    // point to next location
    buff->head++;
    
    // check for over flow
    if ((buff->head) >= (buff->size)) {
        buff->head = 0;
    }
    
    // increase data counter
    buff->data_count++;
    
    // enable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    RESTORE_CPU_IPL(saved_ipl);
    // ---------------------------------------
    
    return;
}

uint8_t cbuff_get(volatile circular_buffer_t *buff){
    // make sure buff is valid
    if (buff == 0) return 0;
    
    // disable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    uint8_t saved_ipl;
    SET_AND_SAVE_CPU_IPL(saved_ipl, 7);
    // ---------------------------------------
    
    // get one byte
    uint8_t data;
    data = buff->data[buff->tail];
    
    // point to next location
    buff->tail++;
    
    // check over flow
    if (buff->tail >= buff->size) buff->tail = 0;
    
    // decrease data counter
    buff->data_count--;
    
    // enable interrupt
    // replace this according to your target
    // ---------------------------------------
    #warning "Replace the according to your target"
    RESTORE_CPU_IPL(saved_ipl);
    // ---------------------------------------
    
    return data;
}
