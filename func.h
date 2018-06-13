/* 
 * File:   func.h
 * Author: james
 *
 * Created on 17 August 2017, 2:50 PM
 */

#ifndef FUNC_H
#define	FUNC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* convert a string hex array to byte array, return data length 
   @param - char *hex, string hex array, must be in one byte pair of "FF"
   @param - uint8_t *data, return data of the converted data
   return - length of the converted data
*/
uint8_t HexCharArray2ByteArray(char *hex, uint8_t *data);
  
/* remove all space in a string 
   @param - char *input, input char array, terminated by \0
   @param - char *output, output char array, terminated by \0
   return - length of trimed char array
*/
uint8_t trimSpace(char *input, char *output);


#ifdef	__cplusplus
}
#endif

#endif	/* FUNC_H */

