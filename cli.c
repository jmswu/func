#include "cli.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/*
 * -----------------------------------------
 * public functions
 * -----------------------------------------
 */

/*
 * parse an buffer with pattern, then return a poiter
 * leading space is ignored
 * @param char* buffer        - buffer contain commands, usually user input
 * @param const char* pattern - pattern need to be matched
 */
char* cli_parse(char* buffer, const char* pattern);

/*
 * return true if it's a number
 * @param char c - single char
 */
int cli_isnumber(char c);

/*
 * this stores all the commands info
 */
cli_params_t cli_params_list[CLI_MAX_ENTRY];

void cli_print_param(cli_params_t *params)
{
    printf("\n");
    printf("CLI params info\n");
    printf("size    : %d\n", sizeof(cli_params_t)/sizeof(params->data[0]));
    printf("cmd     : %s\n", params->cmd);
    printf("param1  : %s\n", params->param1);
    printf("param2  : %s\n", params->param2);
    printf("isUsed  : %d\n", params->isUsed);
    printf("cb      : %p\n", params->cb);
}

void cli_print_result(cli_result_t *result){
    printf("\n");
    printf("CLI result info\n");
    printf("size    : %d\n", sizeof(cli_result_t)/sizeof(result->data[0]));
    printf("isCMD   : %s\n", result->isCmdMatch?"YES":"NO ");
    printf("isParam1: %s [%d]\n", result->isParam1Match?"YES":"NO ", result->NumParam1);
    printf("isParam2: %s [%d]\n", result->isParam2Match?"YES":"NO ", result->NumParam2);
    printf("index   : %d\n", result->ParamIndex);
    printf("P1 addr : %p\n", result->p1);
    printf("P2 addr : %p\n", result->p2);
    printf("P3 addr : %p\n", result->p3);
}

void cli_params_init(cli_params_t *params)
{
    unsigned int size = sizeof(cli_params_t)/sizeof(params->data[0]);
    for(unsigned int i = 0; i < size; i++)
    {
        params->data[i] = 0;
    }
}

void cli_result_init(cli_result_t *result){
    unsigned int size = sizeof(cli_result_t)/sizeof(result->data[0]);
    for (unsigned int i = 0; i < size; i++){
        result->data[i] = 0;
    }
}

void cli_init(void)
{
    unsigned int list_size = sizeof(cli_params_list)/sizeof(cli_params_list[0]);
    for(unsigned int i = 0; i < list_size; i++)
    {
        cli_params_list[i].isUsed = 0;  // flag this as not used
    }
}

cli_errno_t cli_add(cli_params_t *params)
{
    unsigned int list_size = sizeof(cli_params_list)/sizeof(cli_params_list[0]); // slot size
    unsigned int params_size = sizeof(cli_params_t)/sizeof(params->data[0]); // params size

    if (params == NULL)
        return CLI_NULL_PTR;

    /*
     * find an empty slot
     */
    for(unsigned int i = 0; i < list_size; i++)
    {
        if (cli_params_list[i].isUsed == 0)
        {
            /*
             * copy params into the list
             */
            for(unsigned int j =0; j < params_size; j++)
            {
                cli_params_list[i].data[j] = params->data[j];
            }
            cli_params_list[i].isUsed = 1;
            return CLI_OK;
        }
    }

    return CLI_FAILED;
}

cli_errno_t cli_run(char *buffer)
{
    // conversion results
    cli_result_t result;


    //cli_print_result(&result);

    // null pointer check
    if (buffer == NULL)
        return CLI_NULL_PTR;

    // loop through all the entries
    for (unsigned int i = 0; i < CLI_MAX_ENTRY; i++){

        // find a valid entry
        if (cli_params_list[i].isUsed == 1){

            // clear the result
            cli_result_init(&result);

            // assign index to result
            result.ParamIndex = i;

            // null check and parse first command
            if (cli_params_list[i].cmd != NULL){
                // parse command
                result.p1 = cli_parse(buffer, cli_params_list[i].cmd);
                // if command is found
                if (result.p1){
                    result.isCmdMatch = 1;
                }
            }else{
                return CLI_NULL_PTR;
            }

            // null check and parse param1
            if (cli_params_list[i].param1 != NULL){
                // if cmd is valid
                if (result.p1){
                    // parse command
                    result.p2 = cli_parse(result.p1, cli_params_list[i].param1);
                    // if a command is found
                    if (result.p2){
                        result.isParam1Match = 1;
                    }
                }
            }

            // null check and parse param2
            if (cli_params_list[i].param2 != NULL){
                // if param1 is valid
                if (result.p2){
                    // parse command
                    result.p3 = cli_parse(result.p2, cli_params_list[i].param2);
                    // if a command is found
                    if (result.p3){
                        result.isParam2Match = 1;
                    }
                }
            }

            // converter parameter 1 to number
            if (result.p1 != NULL){
                // till the end of buffer
                while(*result.p1 != 0){
                    // if it's a number, covert it to number
                    if (cli_isnumber(*result.p1) && !isspace(*result.p1)){
                        result.NumParam1 = strtol(result.p1, &result.p2, 10);
                        break;
                    }
                    result.p1++; // next
                }
            }

            // convert parameter 2 to number
            if (result.p2 != NULL){
                // till the end of buffer
                while(*result.p2 != 0){
                    // if it's a number, convert it number
                    if (cli_isnumber(*result.p2) && !isspace(*result.p2)){
                        result.NumParam2 = strtol(result.p2, NULL, 10);
                        break;
                    }
                    result.p2++;
                }
            }

            // run call back function
            if (cli_params_list[i].cb(&result) == CLI_OK)
                return CLI_OK;

        }// end of valid check
    }// end of loop

    return CLI_FAILED;
}

char* cli_parse(char* buffer, const char* pattern)
{
    char p;  // store one char in pattern
    char b;  // store one char in buffer

    // make sure its a valid pointer
    if(buffer == 0)
        return NULL;

    // skip all space
    while(isspace(*buffer))
        ++buffer;

    while(1)
    {
        // get one char from the pattern, then set the pointer to next
        // char in pattern.
        p = *pattern++;
        // check if it's end of the pattern, return new buffer pointer
        // if its the end of pattern
        if(p == 0)
        {
            // check the next char in the buffer is space, or its end of string
            // or, may result in a fake mis-match.
            // eg buffer = "hello", pattern = "he", this will come back as positive
            // also can use isspace() to check for space instead of checking for 0x20
            if ((*buffer == 0x20) || (*buffer == 0) || (*buffer == 0x0A))
                return buffer;
        }
        // convert to lower case for comparison, exit loop if the end of
        // the buffer is reached, or the there is a mis-match in the data
        b = tolower(*buffer++);
        if(b == 0 || b != p)
            break;
    }
    return 0;
}

int cli_isnumber(char c){
    const char *num = "0123456789";
    while(*num != 0){
        if (*num++ == c) return 1;
    }
    return 0;
}
