#include "multipress.h"
#include "systick.h"
#include <stdio.h>

void Multipress_init(multipress_params_t *params, uint8_t press_num, uint32_t ticks){
    Multipress_reset(params);
    params->number_pressToDetect = press_num;
    params->tick_rangeToDetect = ticks;
}

void Multipress_reset(multipress_params_t *params){
    /* reset everything */
    params->isStarted = 0U;
    params->number_pressDone = 0U;
    params->tick_firstPress = 0U;
}

void Multipress_press(multipress_params_t *params){
    if (params->isStarted == 0){
        params->isStarted = 1U;
        params->tick_firstPress = Systick_get();
    }
    params->number_pressDone++;
}

uint8_t Multipress_detect(multipress_params_t *params){
    if (params->isStarted){
        
        /* if number of presses is more than required, and it's withing the time range */
        if ((params->number_pressDone >= params->number_pressToDetect) &&
                ((Systick_get() - params->tick_firstPress) <= params->tick_rangeToDetect)){
            Multipress_reset(params);
            return 1U;
        }
        
        /* if timer is expired */
        if ((Systick_get() - params->tick_firstPress) > params->tick_rangeToDetect){
            Multipress_reset(params);
            return 0U;
        }
    }
    
    return 0U;
}
