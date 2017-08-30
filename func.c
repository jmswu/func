#include "func.h"

uint8_t HexCharArray2ByteArray(char *hex, uint8_t *data){
    uint8_t strLen;
    uint8_t dataLen;
    uint8_t oneStrHex[3];

    strLen = strlen((const char*)hex);
    dataLen = strLen / 2;

    /* length of string hex must be even number */
    if ((strLen % 2) != 0){
        return 0;
    }

    for(uint8_t i = 0; i < dataLen; i++){
        uint8_t index = i * 2;
        oneStrHex[0] = hex[index];
        oneStrHex[1] = hex[index + 1];
        oneStrHex[2] = '\0';
        data[i] = (uint8_t)strtol(oneStrHex, NULL, 16);
    }

    return dataLen;
}
