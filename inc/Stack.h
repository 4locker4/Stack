#ifndef STACK_CTOR_H
#define STACK_CTOR_H

#include <stdio.h>
#include <stdint.h>

#include "Utils.h"
#include "Errors.h"

#define HASH_CALC
#define GOOSES
#define DEBUG

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
      
const int       ERRORS_SIZE               = 9;

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

#ifdef HASH_CALC
    int HashAddres     = STANDART_STACK_ELEM;
    int BufferHash     = STANDART_STACK_ELEM;
#endif

#ifdef GOOSES
    gooseType goose2   = GOOSE_CONST;
#endif

} Stack_t;

typedef struct 
{
    Stack_t ** quentity_of_stacks = NULL;
    int        capacity           = 0;
} n_Stacks;

//-------------------------------------- FUNCT --------------------------------------

void        StackCtor             (Stack_t * stk, size_t capacity);
void        StackDtor             (Stack_t * stk);
void        StackPush             (Stack_t * stk, stackElem top);
stackElem   StackPop              (Stack_t * stk);


#endif //