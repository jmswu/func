#include <stdint-gcc.h>

/*
 * define the maximum length of each command
 */
#define PARSER_CMD_LENGTH   (10)

#define PARSER_CMD_SLOT     (10)

/*
 * parser call back function
 */
typedef int(*func_cb_t)(unsigned int, unsigned int);

typedef union
{
    struct
    {
        char *cmd; // pointer to command
        char *param1; // pointer to parameter 1
        char *param2; // pointer to parameter 2
        uint8_t isParam1Digit   : 1; // indicate param1 is a digit
        uint8_t isParam2Digit   : 1; // indicate param2 is a digit
        uint8_t not_used        : 6;
        func_cb_t cb;
        unsigned int arg1;
        unsigned int arg2;
    };
    uint8_t data[0];
} cmd_paser_params_t;

typedef union{

    struct{
        char cmd[PARSER_CMD_LENGTH];
        char param1[PARSER_CMD_LENGTH];
        char param2[PARSER_CMD_LENGTH];
    };
    uint8_t data[0];
}cmd_parser_section_t;


/*
 * initialize the parser parameter to default values
 */
void parse_init(cmd_paser_params_t *params);


/*
 * print parameter values for debug
 */
void parse_print_param(cmd_paser_params_t *params);
