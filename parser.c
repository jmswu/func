#include "parser.h"
#include <stdio.h>

void parse_print_param(cmd_paser_params_t *params){
    printf("parser params info\n");
    printf("size    : %d\n", sizeof(cmd_paser_params_t)/sizeof(params->data[0]));
    printf("cmd     : %s\n", params->cmd);
    printf("param1  : %s\n", params->param1);
    printf("param2  : %s\n", params->param2);
}

void parse_init(cmd_paser_params_t *params){
    /*
    params->cmd = NULL;
    params->param1 = NULL;
    params->param2 = NULL;
    params->isParam1Digit = 0;
    params->isParam2Digit = 0;
    */

    unsigned size = sizeof(cmd_paser_params_t)/sizeof(params->data[0]);
    for(unsigned int i = 0; i < size; i++){
        params->data[i] = 0;
    }
}
