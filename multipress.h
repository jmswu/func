/* 
 * File:   multipress.h
 * Author: james
 *
 * Created on 26 April 2019, 7:51 AM
 */

#ifndef MULTIPRESS_H
#define	MULTIPRESS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>

    typedef struct{
        uint32_t tick_firstPress;       // ticks at first press
        uint32_t tick_rangeToDetect;    // multiple press need to be within this range
        uint8_t number_pressDone;       // number of presses have already done
        uint8_t number_pressToDetect;   // number of presses to be detected
        uint8_t isStarted;              // is this detection started
    }multipress_params_t;
    
    /* setup multi press detection */
    void Multipress_init(multipress_params_t *params, uint8_t press_num, uint32_t time);
    
    /* reset object */
    void Multipress_reset(multipress_params_t *params);
    
    /* call when a press is activated */
    void Multipress_press(multipress_params_t *params);
    
    /* return 1 if a multi press condition is met */
    uint8_t Multipress_detect(multipress_params_t *params);


#ifdef	__cplusplus
}
#endif

#endif	/* MULTIPRESS_H */

