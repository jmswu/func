#include "parser.h"
#include <stdio.h>

cmd_paser_params_t params_list[PARSER_CMD_SLOT];

void parser_print_param(cmd_paser_params_t *params)
{
    printf("parser params info\n");
    printf("size    : %d\n", sizeof(cmd_paser_params_t)/sizeof(params->data[0]));
    printf("cmd     : %s\n", params->cmd);
    printf("param1  : %s\n", params->param1);
    printf("param2  : %s\n", params->param2);
}

void parser_params_init(cmd_paser_params_t *params)
{
    /*
    params->cmd = NULL;
    params->param1 = NULL;
    params->param2 = NULL;
    params->isParam1Digit = 0;
    params->isParam2Digit = 0;
    */

    unsigned size = sizeof(cmd_paser_params_t)/sizeof(params->data[0]);
    for(unsigned int i = 0; i < size; i++)
    {
        params->data[i] = 0;
    }
}

void parser_init(void)
{

    unsigned int list_size = PARSER_CMD_SLOT;
    for(unsigned i = 0; i < list_size; i++)
    {
        params_list[i].isUsed = 0;  // flag this as not used
    }
}

void parser_add(cmd_paser_params_t *params)
{

}
