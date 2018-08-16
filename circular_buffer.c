
#include "circular_buffer.h"

void CBuff_Initial(volatile circular_buffer_t *buff, uint8_t *data, uint8_t size){

    if (!buff) return;
    (*buff).data = data;
    (*buff).head = 0;
    (*buff).tail = 0;
    (*buff).size = size;
    (*buff).data_counter = 0;
}

uint8_t CBuff_isEmpty(volatile circular_buffer_t *buff){
    
    if (!buff) return 1;
    
    uint8_t result;
    // disable interrupt
    INTCONbits.PEIE = 0;
    
    if ((*buff).data_counter == 0) result = 1;
    else result = 0;
    
    // enable interrupt
    INTCONbits.PEIE = 1;
    return result;
}

uint8_t CBuff_isFull(volatile circular_buffer_t *buff){
    
    if (!buff) return 1;
    
    uint8_t result;
    
    // disable interrupt
    INTCONbits.PEIE = 0;
    
    if ((*buff).data_counter == (*buff).size) result = 1;
    else result = 0;
    
    // enable interrupt
    INTCONbits.PEIE = 1;
    
    return result;
}

void CBuff_put(volatile circular_buffer_t *buff, uint8_t data){
    
    if (!buff) return;
    
    // put one data in the buffer
    (*buff).data[(*buff).head] = data;
    // point to next location
    (*buff).head++;
    // check of over flow
    if ((*buff).head >= (*buff).size)
        (*buff).head = 0;
    
    // disable interrupt
    INTCONbits.PEIE = 0;
    // increase data counter
    (*buff).data_counter++;
    // enable interrupt
    INTCONbits.PEIE = 1;
}


uint8_t CBuff_get(volatile circular_buffer_t *buff){
    
    if (!buff) return 0;
    
    uint8_t data;
    data = (*buff).data[(*buff).tail];
    (*buff).tail++;
    if ((*buff).tail >= (*buff).size)
        (*buff).tail = 0;
    
    // disable interrupt
    INTCONbits.PEIE = 0;
    // increase data counter
    (*buff).data_counter--;
    // enable interrupt
    INTCONbits.PEIE = 1;
    
    return data;
}