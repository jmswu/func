#ifndef CLI_H_INCLUDED
#define CLI_H_INCLUDED

#include <stdint-gcc.h>

/*
 * define the maximum number of commands that can support
 */
#define CLI_MAX_ENTRY     (10)


/*
  example:

    #include "cli.h"

    // call back functions
    cli_errno_t cli_cb1(cli_result_t * result);
    cli_errno_t cli_cb2(cli_result_t * result);

    main(){

          // this need to be called before any cli functions call
          cli_init();

          // declare a parameter
          cli_params_t params;

          // setup an example command 1
          cli_params_init(&params);
          params.cmd = "test1";
          params.param1 = "param_1";
          params.param2 = "param_2";
          params.cb = cli_cb1; // assign function call back
          //cli_print_param(&params); // optional, print the parameter values
          cli_add(&params); // add the command

          // setup an example command 2
          cli_params_init(&params);
          params.cmd = "test2";
          params.param1 = "param_1";
          params.param2 = "param_2";
          params.cb = cli_cb2; // assign function call back
          //cli_print_param(&params); // optional, print the parameter values
          cli_add(&params); // add the command

          while(1)
          {
                printf("cmd>");
                buffer[0] = 0;
                fgets(buffer, buffer_size, stdin);

                printf("\n");
                printf("user input: %s", buffer);

                if (cli_run(buffer) != CLI_OK)
                {
                    printf("[bad command]\n");
                }
           }

    }

    cli_errno_t cli_cb1(cli_result_t *result)
    {
        if ((result->isCmdMatch) && (result->isParam1Match) && (result->isParam2Match))
        {
            // to-do: user code
            return CLI_OK;
        }
        else
            return CLI_FAILED;
    }

    cli_errno_t cli_cb2(cli_result_t *result)
    {
        if ((result->isCmdMatch) && (result->isParam1Match) && (result->isParam2Match))
        {
            // to-do: user code
            return CLI_OK;
        }
        else
            return CLI_FAILED;
    }


 */

typedef enum
{
    CLI_OK,
    CLI_FAILED,
    CLI_NULL_PTR
} cli_errno_t;

typedef union
{
    struct
    {
        uint8_t isCmdMatch      : 1; // indicate cmd is found
        uint8_t isParam1Match   : 1; // indicate param1 is found
        uint8_t isParam2Match   : 1; // indicate param2 is found
        uint8_t RFU             : 5;
        uint16_t NumParam1; // converted param1 in unsigned int
        uint16_t NumParam2; // converted param2 in unsigned int
        uint16_t ParamIndex; // the index pointing to the parameter list
        char *p1;
        char *p2;
        char *p3;
    };
    uint8_t data[0];
} cli_result_t;

/*
 * cli call back function, this is the function to call when a cli is matched
 */
typedef cli_errno_t (*cli_cb_t)(cli_result_t *);

typedef union
{
    struct
    {
        const char *cmd; // pointer to command
        const char *param1; // pointer to parameter 1
        const char *param2; // pointer to parameter 2
        uint8_t isUsed  : 1; // indicate this parameter is used
        uint8_t RFU     : 7;
        cli_cb_t cb; // call back function
    };
    uint8_t data[0];
} cli_params_t;

extern cli_params_t cli_params_list[CLI_MAX_ENTRY];


/*
 * -----------------------------------------
 * public functions
 * -----------------------------------------
 */

/*
 * call this before using cli library
 */
void cli_init(void);

/*
 * initialize the cli parameter to default values. Call this
 * before assigning values to the parameters
 */
void cli_params_init(cli_params_t *params);

/*
 * initialize the cli result to default values. Call this
 * before assigning values to the result
 */
void cli_result_init(cli_result_t *result);

/*
 * add an command object to the list
 */
cli_errno_t cli_add(cli_params_t *params);

/*
 * match the buffer with any one of the commands in the list
 * if a match is found, the function assigned to the command
 * is executed.
 */
cli_errno_t cli_run(char *buffer);


/*
 * -----------------------------------------
 * debug functions, not needed for normal
 * operation.
 * -----------------------------------------
 */

/*
* print parameter values for debug
*/
void cli_print_param(cli_params_t *params);

/*
 * print result values for debug
 */
void cli_print_result(cli_result_t *result);

#endif



