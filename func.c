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

uint8_t isCmd(uint8_t *cmd, const unsigned char *param, uint8_t offset){
    
    // get the size of the command
    uint8_t size;
    size = strlen(param);
    
    // check if they match
    uint8_t i = 0;
    for(i = 0; i < size; i++){
        if (cmd[i + offset] != param[i])
            return 0;
    }
    
    // if the next char is not space or \0, this is likely a longer command
    if ((cmd[i + offset] == 0x20) || (cmd[i + offset] == 0x00)){
        return 1;
    }else{
        return 0;
    }
}

uint8_t* parse(uint8_t* buffer, uint8_t* pattern)
{
    uint8_t p;  // store one char in pattern
    uint8_t b;  // store one char in buffer
    
    // make sure its a valid pointer
    if(buffer == 0)
        return 0;
    
    // skip all space
    while(isspace(*buffer))
        ++buffer;
    
    while(1)
    {
        // get one char from the pattern, then set the pointer to next 
        // char in pattern. 
        p = *pattern++;
        // check if it's end of the pattern, return new buffer pointer 
        // if its the end of pattern
        if(p == 0){
            // check the next char in the buffer is space, or its end of string
            // or, may result in a fake mis-match.
            // eg buffer = "hello", pattern = "he", this will come back as positive
            // also can use isspace() to check for space instead of checking for 0x20
            if ((*buffer == 0x20) || (*buffer == 0))
                return buffer;
        }
        // convert to lower case for comparison, exit loop if the end of
        // the buffer is reached, or the there is a mis-match in the data
        b = tolower(*buffer++);
        if(b == 0 || b != p)
            break;
    }
    return 0;
}
