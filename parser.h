#include <stdint-gcc.h>

/*
 * define the maximum length of each command
 */

#define PARSER_CMD_SLOT     (10)

/*
 * parser call back function
 */
typedef int(*cmd_parser_func_cb_t)(unsigned int, unsigned int);

typedef union
{
    struct
    {
        char *cmd; // pointer to command
        char *param1; // pointer to parameter 1
        char *param2; // pointer to parameter 2
        uint8_t isParam1Digit   : 1; // indicate param1 is a digit
        uint8_t isParam2Digit   : 1; // indicate param2 is a digit
        uint8_t isUsed          : 1; // indicate this parameter is used
        cmd_parser_func_cb_t cb;
        unsigned int arg1;
        unsigned int arg2;
    };
    uint8_t data[0];
} cmd_paser_params_t;


/*
 * call this before using parser
 */
void parser_init(void);

/*
 * initialize the parser parameter to default values
 */
void parser_params_init(cmd_paser_params_t *params);


/*
 * print parameter values for debug
 */
void parser_print_param(cmd_paser_params_t *params);

/*
 * add an command object to the list
 */
 void parser_add(cmd_paser_params_t *params);
