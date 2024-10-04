///@file Errors.h
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MANGETA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define STRANGE "\x1b[1;35;7m"

#define COLOR_PRINT(color, ...)  {printf (color __VA_ARGS__); printf (RESET); }    ///< Colorful print

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
    OUT_OF_CAPACITY      =      0100,
    STACK_UNDERFLO       =     01000,
    GOOSE_ERROR          =    010000, 
    STACK_FLO            =   0100000,
    SOME_ONE_POOPED_HERE =  01000000
};

#endif