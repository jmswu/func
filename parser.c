#include "parser.h"
#include <stdio.h>
#include <ctype.h>

cmd_paser_params_t params_list[PARSER_CMD_SLOT];

void parser_print_param(cmd_paser_params_t *params)
{
    printf("parser params info\n");
    printf("size    : %d\n", sizeof(cmd_paser_params_t)/sizeof(params->data[0]));
    printf("cmd     : %s\n", params->cmd);
    printf("param1  : %s [%s]\n", params->param1, params->isParam1Digit?"Digit":"String");
    printf("param2  : %s [%s]\n", params->param2, params->isParam2Digit?"Digit":"String");
    printf("arg1    : %d\n", params->arg1);
    printf("arg2    : %d\n", params->arg2);
    printf("isUsed  : %d\n", params->isUsed);
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
    for(unsigned int i = 0; i < list_size; i++)
    {
        params_list[i].isUsed = 0;  // flag this as not used
    }
}

int parser_add(cmd_paser_params_t *params)
{
    unsigned int list_size = PARSER_CMD_SLOT; // slot size
    unsigned int params_size = sizeof(cmd_paser_params_t)/sizeof(params->data[0]); // params size

    if (params == NULL)
        return 0;

    /*
     * find an empty slot
     */
    for(unsigned int i = 0; i < list_size; i++)
    {
        if (params_list[i].isUsed == 0)
        {
            /*
             * copy params into the list
             */
            for(unsigned int j =0; j < params_size; j++)
            {
                params_list[i].data[j] = params->data[j];
            }
            params_list[i].isUsed = 1;
            return 1;
        }
    }

    return 0;
}

int parser_execute(char *buffer)
{
    if (buffer == NULL)
        return 0;

    for(unsigned int i = 0; i < PARSER_CMD_SLOT; i++)
    {
        if (params_list[i].isUsed == 1)
        {
            printf("isUsed found\n");
            char *p1, *p2, *p3;
            p1 = parser_parse(buffer, params_list[i].cmd);
            if (p1)
            {
                printf("match-1: %s %p\n", params_list[i].cmd, p1);
                p2 = parser_parse(p1, params_list[i].param1);
                printf("looking for: %s %p\n", params_list[i].param1, p2);
                if (p2)
                {
                    printf("match-2: %s\n", params_list[i].param1);
                    p3 = parser_parse(p2, params_list[i].param2);
                    printf("looking for: %s %p\n", params_list[i].param2, p3);
                    if (p3)
                    {
                        printf("match-3: %s\n", params_list[i].param2);
                        params_list[i].cb(100, 200);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

char* parser_parse(char* buffer, char* pattern)
{
    char p;  // store one char in pattern
    char b;  // store one char in buffer

    // make sure its a valid pointer
    if(buffer == 0)
        return 0;

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
        if(p == 0){
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
