#include "../inc/StackCtor.h"
const char * file_directory = "DEBUG.txt";

const char * is_null              = "There is NULL pointer\n";
const char * bad_hash             = "Your hash is bad bad boy\n";
const char * out_of_capacity      = "Relly? Size is too big, stupid student\n";
const char * stack_underflo       = "Bul bul bul there is no elements in my\n";
const char * goose_error          = "AAAAA, Gals are here!!!\n";
const char * stack_flo            = "Its too big for me, i cant\n";
const char * some_one_pooped_here = "Bro, you ppoped in ypur data. Did your mum teach you not to poop near your food?\n";

unsigned ERRORS = 0;

int StackCtor (Stack_t * stk, size_t capacity)
{                                                                                                                                                                                                                               //popa
    if (stk == NULL)
    {
        COLOR_PRINT (RED, "Bad pointer to stack, we cant create a stack.\n");
        return IS_NULL;
    }

    stk->capacity = capacity;
    stk->size     = 0;
    
    stk->data = (stackElem *) calloc (stk->capacity * sizeof (stackElem) + 
                                                ADD_ALIGEN (stk->capacity) + 2 * MEM_OF_GOOSES, 
                                                sizeof (char));
                                            
    stk->data = (stackElem *) ((char *) stk->data + MEM_OF_GOOSES);

    memset (stk->data, POISON_NUM, stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity));

    for (int i = 0; i < capacity; i++)
    {
        printf("%lg\n", stk->data[i]);
    }

/*#ifdef GOOSES
    *(gooseType *) ((char *) stk->data - MEM_OF_GOOSES) = stk->goose1;
    *(gooseType *) ((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)) = stk->goose2;
#endif

#ifdef ON_HASH
    ON_HASH (stk)
#endif

    VERIFY_STACK (stk);*/

    return 0;
}

int StackDtor (Stack_t * stk)
{
    VERIFY_STACK (stk);

    free(stk->data);

#ifdef GOOSES
    stk->goose1 = 0;
#endif

    stk->data = NULL;
    stk->size = 0;
    stk->capacity = 0;

#ifdef GOOSES
    stk->goose2 = 0;
#endif

    return OK;
}

int StackPush (Stack_t * stk, stackElem top)
{    
    VERIFY_STACK (stk);

    if (stk->size == stk->capacity)
    {
        MemNew (stk, INCREASE);
    }
    
    stk->data[stk->size++] = top;

    ON_HASH (stk)
    
    VERIFY_STACK (stk);

    return OK;
}

int StackPop (Stack_t * stk)
{
    VERIFY_STACK (stk);

    if (stk->size >= (stk->capacity - DELTA_CAPACITY_SIZE) / 2)
    {
        stk->data[--stk->size] = POISON_NUM;

        ON_HASH (stk)

        VERIFY_STACK (stk);
        return OK;
    }
    else
    {
        MemNew (stk, DECREASE);
        stk->data[--stk->size] = POISON_NUM;
        ON_HASH (stk)

        VERIFY_STACK (stk);
        return OK;
    }

    VERIFY_STACK (stk);

    return -1;
}

int MemNew (Stack_t * stk, bool flag)
{
    VERIFY_STACK (stk);

    /* decrease or increase capacity */
    if (flag)
        stk->capacity *= 2;
    else
        stk->capacity /= 2;

    //void * pointer_to_last_data = &stk->data;                         ----- очистку памяти

    /* allocating memory */
    stk->data = (stackElem *) ((char *) realloc((char *) stk->data - MEM_OF_GOOSES, stk->capacity * sizeof (stackElem) + 
                                                ADD_ALIGEN (stk->capacity) + 2 * MEM_OF_GOOSES) + MEM_OF_GOOSES);

    /* fill poisons num all bites */
    memset ((stackElem *) stk->data + stk->size, POISON_NUM, stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity) + MEM_OF_GOOSES - stk->size * sizeof (stackElem));

#ifdef GOOSES
    /* add canary at the beggining */
    *(gooseType *) ((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)) = stk->goose2;
#endif

    ON_HASH (stk)

    VERIFY_STACK (stk);

    return OK;
}

int Verificator (Stack_t * stk)
{ 
    if (stk == NULL)
    {
        ERRORS |= IS_NULL;
        return 1;
    }

    if (stk->data == NULL)
        ERRORS |= IS_NULL;

    if (stk->size > stk->capacity)  
        ERRORS |= OUT_OF_CAPACITY;

    if (stk->capacity > 0xDAFAC)
        ERRORS |= STACK_FLO;
    
    CHECK_GOOSES (stk->goose1);

    CHECK_GOOSES (stk->goose2);

    printf ("<%p>\n", (char *) stk->data - MEM_OF_GOOSES);
/* ПАДАЕТ */
    if (* (gooseType *) ((((char *) stk->data) - MEM_OF_GOOSES)) != GOOSE_CONST ||
        * (gooseType *) (((char *) stk->data) + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)) != GOOSE_CONST)
        ERRORS |= SOME_ONE_POOPED_HERE;
        
#ifdef HASH_CALC
    if (HashCalc ((char *) stk, sizeof (Stack_t)) != stk->HashAddres)
        ERRORS |= BAD_HASH;
#endif

    COLOR_PRINT (RED, "<%d> - ERROR\n", ERRORS);

    if (ERRORS != 0)
        return 1;

    return 0;
}

/*
govno zalupa penis her davalka hui blyadina
golovka shluha jopa chlen eblan petuh mudila
rukoblud sanina ochko blyadun vagina 
suka eblanishe vlagalishe perdun drochila 
pidr pizda tuz malafya gomic mudila pilotka manda
anus vagina putana pedrila shalava huila moshonka elda
ROUND!!!!!!!!!!
egor pidoras(he like ebatsa in jopa)
ROUND!!!!!!!!!!
*/

int StackDump (Stack_t * stk, const char * var_name, const char * file_name, const int line)
{
    COLOR_PRINT (GREEN, "Strack_t");
    COLOR_PRINT (RED,   "<%p> ", stk);
    COLOR_PRINT (GREEN, "born at ");
    COLOR_PRINT (RED,   "%s: %d, ", file_name, line);
    COLOR_PRINT (GREEN, "name: ")
    COLOR_PRINT (RED,   "\"%s\"\n", var_name);

    if (stk == NULL)
    {
        COLOR_PRINT (MANGETA, "pointer to Stack_t str = NULL\n");
        return IS_NULL;
    }

    if (stk->data == NULL) COLOR_PRINT (MANGETA, "Data is NULL\n");

    PRINT_GOOSES (stk->goose1, GOOSE_CONST);

    PRINT_GOOSES (stk->goose2, GOOSE_CONST);

/*ПАДАЕТ*/
    PRINT_GOOSES (*((char *) stk->data - MEM_OF_GOOSES), GOOSE_CONST);

    PRINT_GOOSES (*((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)), GOOSE_CONST);

#ifdef HASH_CALC
    COLOR_PRINT (GREEN, "Hash: %d\n", stk->HashAddres);
#endif

    COLOR_PRINT (CYAN, "ALLIGEN: <%d>,\tGOOSE_SIZE: <%d>\n", ADD_ALIGEN (stk->capacity), MEM_OF_GOOSES)

    COLOR_PRINT (GREEN,    "size = ");
    COLOR_PRINT (MANGETA,  "<%d>",   stk->size);
    COLOR_PRINT (GREEN,    "\tcapasity = ");
    COLOR_PRINT (MANGETA,  "<%d>\n", stk->capacity);

    if (stk->data == NULL) 
    {
        COLOR_PRINT (RED,  "\tstk->data == NULL\n\n");
        COLOR_PRINT (CYAN, "Dump ends.\n");
        return IS_NULL;
    }

    size_t counter = 0;
    while (counter < stk->capacity)
    {   
        COLOR_PRINT (GREEN,   "[%d] = ", counter);
        if (DoubleComparison (stk->data[counter], POISON_NUM))
        {
            COLOR_PRINT (YELLOW, "%x (POISON)\n", stk->data[counter]);
            counter++;
        }
        else
        {
            COLOR_PRINT (MANGETA, "%lg\n",   stk->data[counter]);
            counter++;
        }
    }

    COLOR_PRINT (GREEN, "Dump ends.\n");

    FileWriter (file_directory);
    
    exit (1);
    return -1;
}

int HashCalc (const char * data, size_t size)
{
    int HashAddres = 0;
    size -= sizeof (hashType);

    for (size_t counter = 0; size > counter; counter++)
    {
        HashAddres = ((HashAddres << 5) + HashAddres) ^ data[counter];
    }

    return HashAddres;
}

int FileWriter (const char * file_directory)
{
    FILE * result = fopen (file_directory, "w");

    if (ERRORS & IS_NULL)              fwrite (is_null,              sizeof (char), strlen (is_null)              * sizeof (char), result);
    if (ERRORS & BAD_HASH)             fwrite (bad_hash,             sizeof (char), strlen (bad_hash)             * sizeof (char), result);
    if (ERRORS & OUT_OF_CAPACITY)      fwrite (out_of_capacity,      sizeof (char), strlen (out_of_capacity)      * sizeof (char), result);
    if (ERRORS & STACK_UNDERFLO)       fwrite (stack_underflo,       sizeof (char), strlen (stack_underflo)       * sizeof (char), result);
    if (ERRORS & STACK_FLO)            fwrite (stack_flo,            sizeof (char), strlen (stack_flo)            * sizeof (char), result);
    if (ERRORS & GOOSE_ERROR)          fwrite (goose_error,          sizeof (char), strlen (goose_error)          * sizeof (char), result);
    if (ERRORS & SOME_ONE_POOPED_HERE) fwrite (some_one_pooped_here, sizeof (char), strlen (some_one_pooped_here) * sizeof (char), result);

    fclose (result);

    return 0;
}
