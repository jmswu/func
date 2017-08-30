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

/* convert a string hex array to byte array, return data length */
uint8_t HexCharArray2ByteArray(char *hex, uint8_t *data);


#ifdef	__cplusplus
}
#endif

#endif	/* FUNC_H */

