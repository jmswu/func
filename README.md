# func
a collection of functions that I often use


/* convert a string hex array to byte array, return data length
   @char *hex       input data, hex string, must be 2 char in a pair and \0 terminated
   @uint8_t *data   output data, this must size big enought to hold all the data
   @return          len of the *data, return 0 if invalid input data is provided
   
   Example:
   char *inputHex = "BC1D45FF"
   uint8_t buf[20];
   uint8_t len;
   len = HexCharArray2ByteArray(inputHex, buf);

uint8_t HexCharArray2ByteArray(char *hex, uint8_t *data);
