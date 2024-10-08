#ifndef STACK_CTOR_H
#define STACK_CTOR_H

#include <stdio.h>
#include <stdint.h>

#include "Utils.h"
#include "Errors.h"

#define HASH_CALC
#define GOOSES
#define DEBUG


//------------------------------------- DEFINE -------------------------------------
#define Isolated_fprintf(...) {FILE * DEBUG_FILE = fopen ("DEBUG.txt", "a+"); fprintf (DEBUG_FILE, __VA_ARGS__); fclose (DEBUG_FILE); return;}

#define ERROR_FWRITER(ERRORS, LOG_FILE)                                   \
{                                                                           \
    FILE * DEBUG_FILE = fopen (LOG_FILE, "a+");                           \
                                                                            \   
    rewind (DEBUG_FILE);                                                    \
                                                                            \
    for (size_t i = 0; ERRORS_SIZE > i; i++)                                \
    {                                                                       \
        if (ERRORS & (i << 1))                                              \
        {                                                                   \
            fprintf (DEBUG_FILE, "%s", stack_errors_interpretation[i]);     \
        }                                                                   \
    }                                                                       \
    fwrite ("\n", 1, 1, DEBUG_FILE);                                        \
                                                                            \
    fclose (DEBUG_FILE);                                                    \
}                                                                               

#ifdef HASH_CALC

    #define ON_HASH(stk) {stk->HashAddres = HashCalc ((char *) stk, sizeof (Stack_t));                               \
                          stk->BufferHash = HashBufferCalc ((char *) stk->data, stk->capacity);}

#else

    #define ON_HASH(stk);

#endif

#ifdef GOOSES

    #define ADD_ALIGEN(capacity) (8 - capacity % 8) * ((capacity % 8) != 0)

    #define MEM_OF_GOOSES sizeof (gooseType)

    #define PRINT_GOOSES(num)                               \
    {                                                       \
        COLOR_PRINT (GREEN, "%s: ", #num);                  \
        if (num != GOOSE_CONST)                             \
            COLOR_PRINT (RED,  "<%x>\n", num)               \
        else                                                \
            COLOR_PRINT (BLUE, "<%x> (OK)\n", num);         \
    }
#else

    #define ADD_ALIGEN(capacity) 0
    #define MEM_OF_GOOSES 0
    #define PRINT_GOOSES(num, flag);

#endif
//



//
#ifdef DEBUG

    #define VERIFY_STACK(stk)                                   \
    {                                                           \
        int check = Verificator(stk);                           \
        if (check)                                              \
        {                                                       \                    
            StackDump(stk, check, #stk, __FILE__, __LINE__);    \
            exit (1);                                           \
        }                                                       \
    }                                                           \

#else 

    #define VERIFY_STACK(stk);

#endif

//------------------------------------ TYPEDEF -------------------------------------

typedef double   stackElem;
typedef uint64_t gooseType;
typedef uint64_t hashType;   

//-------------------------------------- CONST --------------------------------------

const size_t    DELTA_CAPACITY_SIZE       = sizeof(double);

const stackElem POISON_NUM                = -666;

const unsigned  GOOSE_CONST               = 0xE1DA;
 
const size_t    STANDART_SIZE             = 16;

const int       STANDART_STACK_ELEM       = 0;
      
const int       CALLOC_QUANTITY_OF_STACKS = 5;
      
const int       ERRORS_SIZE               = 8;

//--------------------------------------- ENUM --------------------------------------

enum REALLOC_MODE
{
    INCREASE = 1,
    DECREASE = 0
};

//-------------------------------------- STRUCT --------------------------------------

typedef struct
{
#ifdef GOOSES
    gooseType goose1   = GOOSE_CONST;
#endif

    size_t size        = STANDART_STACK_ELEM;
    size_t capacity    = STANDART_STACK_ELEM;
    stackElem * data   = NULL;

#ifdef GOOSES
    gooseType goose2   = GOOSE_CONST;
#endif

#ifdef HASH_CALC
    int HashAddres     = STANDART_STACK_ELEM;
    int BufferHash     = STANDART_STACK_ELEM;
#endif
} Stack_t;

//-------------------------------------- FUNCT --------------------------------------

void      StackCtor      (Stack_t * stk, size_t capacity);
void      StackDtor      (Stack_t * stk);
void      StackPush      (Stack_t * stk, stackElem top);
stackElem StackPop       (Stack_t * stk);
void      MemNew         (Stack_t * stk, REALLOC_MODE flag);
int       Verificator    (Stack_t * stk);
void      StackDump      (Stack_t * stk, const int ERROR, const char * var_name, const char * file_name, const int line);
int       HashCalc       (const char * data, size_t size);
void      FileWriter     (const char * file_directory, const unsigned * ERRORS);
void      DoubleMemSet   (stackElem  * pointer, const stackElem num, size_t size);
int       HashBufferCalc (const char * data, size_t size);


#endif //