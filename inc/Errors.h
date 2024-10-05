///@file Errors.h
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Utils.h"

#define my_assert(expr) if (!(expr))\
                        {\
                            printf ("ERROR: \"" #expr "\", file %s, function %s, line %d\n", \
                                        __FILE__, __func__, __LINE__);\
                            exit (1);\
                        }

#define CHECKED_(expr) if (!(expr))\
                            {\
                            COLOR_PRINT (RED, "ERROR, your error`s number is: <%d>\n",\
                                              "Information:\n",\
                                              "File: <%s>           Line: <%d>\n",\
                                              expr, __FILE__, __LINE__)}

enum ERRORS
{
    OK                   = 0,
    IS_NULL              = 1 << 0,
    BAD_HASH             = 1 << 1,
    OUT_OF_CAPACITY      = 1 << 2,
    STACK_UNDERFLO       = 1 << 3,
    GOOSE_ERROR          = 1 << 4, 
    STACK_FLO            = 1 << 5,
    SOME_ONE_POOPED_HERE = 1 << 6
};

#endif