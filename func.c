#include "func.h"

uint8_t HexCharArray2ByteArray(char *hex, uint8_t *data){
    uint8_t strLen;
    uint8_t dataLen;
    uint8_t oneStrHex[3];

    strLen = strlen((const char*)hex);
    dataLen = strLen / 2U;

    /* length of string hex must be even number */
    if ((strLen % 2U) != 0){
        return 0;
    }

    for(uint8_t i = 0; i < dataLen; i++){
        uint8_t index = i * 2U;
        oneStrHex[0] = hex[index];
        oneStrHex[1] = hex[index + 1];
        oneStrHex[2] = '\0';
        data[i] = (uint8_t)strtol(oneStrHex, NULL, 16);
    }

    return dataLen;
}

uint8_t trimSpace(char *input, char *output){
    uint8_t len = 0;
    
    // loop until the end of the char array
    // in case of loop forever, watch dog timer should reset the board.
    while(*input != 0){
        // if it's not space, assign the char to the output array
        if (*input != 0x20){
            *output = *input;
            // point to the next output char
            output++;
            // count the length of output char
            len++;
        }
        // point to next input char
        input++;
    }
    
    // add termination char
    *output = 0;
    // return lenght of the output char array.
    return len;
}
