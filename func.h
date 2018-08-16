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
   
// look for a sub string in a string, starting from offset location
uint8_t isCmd(uint8_t *cmd, const unsigned char *cmd_to_check, uint8_t offset);
   
// parse a pattern in the buffer
// if a pattern is match, return the pointer after the pattern
// if a pattern is not match, return 0
//
//  Example #1
//     char* cmd = "set param1 1024";
//     puts(parse(parse(cmd, "set"), "param1"));
//
//  Example #2 
//     char* val = 0;
//     char* set = parse(cmd, "set");
//     if(set){
//         if(val = parse(set, "param1")){
//             puts("set param1:");
//             puts(val);
//         }
//         else if(val = parse(set, "param2")){
//             puts("set param2:");
//             puts(val);          
//         }
//     }
uint8_t* parse(uint8_t* buffer, uint8_t* pattern);


#ifdef	__cplusplus
}
#endif

#endif	/* FUNC_H */

