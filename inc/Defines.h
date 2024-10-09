#ifndef USERS_H
#define USERS_H

//------------------------------------- DEFINE -------------------------------------

#define Isolated_fprintf(returned_elem, ...)        \
{                                                   \
    FILE * DEBUG_FILE = fopen ("DEBUG.txt", "a+");  \
    fprintf (DEBUG_FILE, __VA_ARGS__);              \
    fclose (DEBUG_FILE);                            \
}

#define ERROR_FWRITER(ERRORS, LOG_FILE)                                     \
{                                                                           \
    FILE * DEBUG_FILE = fopen (LOG_FILE, "a+");                             \
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
    if (!fclose (DEBUG_FILE))                                               \
        COLOR_PRINT("File didn`t close\n");                                 \
}

#ifdef HASH_CALC

    #define ON_HASH(stk) {stk->HashAddres = HashCalc ((char *) stk, sizeof (Stack_t));          \
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

    
    #define CHEKING_FOR_STACK_AVAILABILITY(stk, flag)                           \
    {                                                                           \
        for (size_t i = 0; i < inited_stacks.capacity; i++)                     \
        {                                                                       \
            if (inited_stacks.quentity_of_stacks[i] == stk)                     \
                flag = true;                                                    \
        }                                                                       \
    }

#else 

    #define VERIFY_STACK(stk);

#endif

#endif