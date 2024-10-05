#include "../inc/Stack.h"

const char * is_null              = "There is NULL pointer\n";
const char * bad_hash             = "Your hash is bad bad boy\n";
const char * out_of_capacity      = "Relly? Size is too big, stupid student\n";
const char * stack_underflo       = "Bul bul bul there is no elements in my\n";
const char * goose_error          = "AAAAA, Gals are here!!!\n";
const char * stack_flo            = "Its too big for me, i cant (stack_flo)\n";
const char * some_one_pooped_here = "Bro, you pooped in ypur data. Did your mum teach you not to poop near your food?\n";

int StackCtor (Stack_t * stk, size_t capacity)
{                                                                                                                                                                                                                               //popa
    if (stk == NULL)
    {
        COLOR_PRINT (RED, "163 stack on my neck. Bad pointer to stack, we cant create a stack, kek.\n");
        return IS_NULL;
    }

    if (stk->data != NULL)
        {
            COLOR_PRINT (RED, "You made a repeated stack\n");
            return REPEATED_VAL;
        }

    stk->capacity = capacity;
    stk->size     = 0;
    
    stk->data = (stackElem *) calloc (stk->capacity * sizeof (stackElem) + 
                                      ADD_ALIGEN (stk->capacity) + 2 * MEM_OF_GOOSES, sizeof (char));

    DoubleMemSet (stk->data, POISON_NUM, stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity) + 2 * MEM_OF_GOOSES);

#ifdef GOOSES
    *(gooseType *) stk->data = stk->goose1;
    
    stk->data = (stackElem *) ((char *) stk->data + MEM_OF_GOOSES);

    *(gooseType *) ((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)) = stk->goose2;
#endif

#ifdef ON_HASH
    ON_HASH (stk)
#endif

    VERIFY_STACK (stk);

    return 0;
}

int StackDtor (Stack_t * stk)
{
    if (stk->data == NULL)
    {
        COLOR_PRINT (RED, "You called StackDtor again\n");
        return REPEATED_VAL;
    }

    VERIFY_STACK (stk)

    free(stk->data);
    stk->data = NULL;

#ifdef GOOSES
    stk->goose1   = GOOSE_CONST;
#endif

    stk->size     = STANDART_STACK_ELEM;
    stk->capacity = STANDART_STACK_ELEM;

#ifdef GOOSES
    stk->goose2   = GOOSE_CONST;
#endif

    return OK;
}

int StackPush (Stack_t * stk, stackElem top)
{    
    VERIFY_STACK (stk)

    if (stk->size == stk->capacity)
    {
        MemNew (stk, INCREASE);
    }
    
    stk->data[stk->size++] = top;

    ON_HASH (stk)
    
    VERIFY_STACK (stk)

    return OK;
}

int StackPop (Stack_t * stk)
{
    VERIFY_STACK (stk)

    if (stk->size <= (stk->capacity - DELTA_CAPACITY_SIZE) / 2)
        MemNew (stk, DECREASE);

    stackElem poped = stk->data[stk->size];

    stk->data[--stk->size] = POISON_NUM;

    ON_HASH (stk)

    VERIFY_STACK (stk)

    return poped;
}

int MemNew (Stack_t * stk, REALLOC_MODE flag)
{
    VERIFY_STACK (stk)

    /* decrease or increase capacity */
    if (flag)
        stk->capacity *= 2;
    else
        stk->capacity /= 2;

    /* allocating memory */
    stk->data = (stackElem *) ((char *) realloc((char *) stk->data - MEM_OF_GOOSES, stk->capacity * sizeof (stackElem) + 
                                                ADD_ALIGEN (stk->capacity) + 2 * MEM_OF_GOOSES) + MEM_OF_GOOSES);

    /* fill poisons num all bites */
    DoubleMemSet ((stackElem *) stk->data + stk->size, POISON_NUM, stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity) + 
                  MEM_OF_GOOSES - stk->size * sizeof (stackElem));

#ifdef GOOSES
    /* add canary at the beggining */
    *(gooseType *) ((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)) = stk->goose2;
#endif

    ON_HASH (stk)

    VERIFY_STACK (stk)

    return OK;
}

int Verificator (Stack_t * stk)
{ 
    unsigned ERRORS = 0;

    if (stk <= NULL)
    {
        ERRORS |= IS_NULL;
        return 1;
    }
printf ("%p\n", &stk->data);
    if (stk->data <= NULL)
        ERRORS |= IS_NULL;

    if (stk->size > stk->capacity)  
        ERRORS |= OUT_OF_CAPACITY;

    if (stk->capacity > 0xDAFAC)
        ERRORS |= STACK_FLO;
    
#ifdef GOOSES

    CHECK_GOOSES (stk->goose1);

    CHECK_GOOSES (stk->goose2);

    if ((char *) stk->data - MEM_OF_GOOSES >= 0)
    {
        if (* (gooseType *) ((((char *) stk->data) - MEM_OF_GOOSES)) != GOOSE_CONST ||
            * (gooseType *) (((char *) stk->data) + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)) != GOOSE_CONST)
            ERRORS |= SOME_ONE_POOPED_HERE;        
    }
#endif

#ifdef HASH_CALC
    if (HashCalc ((char *) stk, sizeof (Stack_t)) != stk->HashAddres)
        ERRORS |= BAD_HASH;
    if (HashBufferCalc ((char *) stk->data, stk->capacity) != stk->BufferHash)
        ERRORS |= BAD_HASH;

#endif

    if (ERRORS)
        FileWriter ("DEBUG.txt", &ERRORS);
    return ERRORS;
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

int StackDump (Stack_t * stk, const int ERROR, const char * var_name, const char * file_name, const int line)
{
    FILE * DEBUG_FILE = fopen ("DEBUG.txt", "a+");

    Dump_to_file ("Strack_t");
    Dump_to_file ("<%p> ", stk);
    Dump_to_file ("born at ");
    Dump_to_file ("%s: %d, ", file_name, line);
    Dump_to_file ("name: ")
    Dump_to_file ("\"%s\"\n", var_name);

    if (stk == NULL)
    {
        Dump_to_file ("pointer to Stack_t str = NULL\n");
        return IS_NULL;
    }

    if (stk->data == NULL)
    {
        Dump_to_file ("Data is NULL\n");
        return IS_NULL;
    }

    Dump_to_file ("ALLIGEN: <%d>,\tGOOSE_SIZE: <%d>\n", ADD_ALIGEN (stk->capacity), MEM_OF_GOOSES)

    Dump_to_file ("size = ");
    Dump_to_file ("<%d>",   stk->size);
    Dump_to_file ("\tcapasity = ");
    Dump_to_file ("<%d>\n", stk->capacity);

    PRINT_GOOSES (stk->goose1);

    PRINT_GOOSES (stk->goose2);

    if (ERROR & SOME_ONE_POOPED_HERE)
        Dump_to_file ("Sorry, your buffer is broke\n")
    else
    {
        PRINT_GOOSES (*((char *) stk->data - MEM_OF_GOOSES));

        PRINT_GOOSES (*((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)));
    }

#ifdef HASH_CALC
    Dump_to_file ("Hash: %d\n", stk->HashAddres);
    Dump_to_file ("Buffer hash: %d\n", stk->BufferHash);
#endif

    if (stk->data == NULL) 
    {
        Dump_to_file ("\tstk->data == NULL\n\n");
        Dump_to_file ("Dump ends.\n");
        return IS_NULL;
    }

    if (!(OUT_OF_CAPACITY & ERROR || STACK_FLO & ERROR || STACK_UNDERFLO & ERROR))
    {
        size_t counter = 0;
        while (counter < stk->capacity)
        {   
            Dump_to_file ("[%d] = ", counter);
            if (DoubleComparison (stk->data[counter], POISON_NUM))
            {
                Dump_to_file ("%x (POISON)\n", stk->data[counter]);
                counter++;
            }
            else
            {
                Dump_to_file ("%lg\n",   stk->data[counter]);
                counter++;
            }
        }
    }
    else
        Dump_to_file ("Sorry, our capacity is bad, we can`t print stack\n");

    Dump_to_file ("Dump ends.\n");
    
    fclose (DEBUG_FILE);
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

int HashBufferCalc (const char * data, size_t size)
{
    int HashAddres = 0;
    size -= sizeof (hashType);

    for (int i = 0; i < size; i++)
    {
        HashAddres = (HashAddres * size);
        HashAddres = HashAddres << 8;
        size *= 33 * 31 * 29;   

        while (true)
        {
            HashAddres = size >> 10;

            if (HashAddres & 33 * 31 == 0)
                continue;
            else if (size >> 8 == 17)
            {
                HashAddres = 31 * (size << 10);
                HashAddres = HashAddres << 9;
                break;
            }
            else
            size *= 1777;
                break;
        }

        break;
    }

    return size;
}

int FileWriter (const char * file_directory, const unsigned * ERRORS)
{
    FILE * DEBUG_FILE = fopen (file_directory, "a+");

    rewind (DEBUG_FILE);

    if (*ERRORS & IS_NULL)              fwrite (is_null,              sizeof (char), strlen (is_null)              * sizeof (char), DEBUG_FILE);
    if (*ERRORS & BAD_HASH)             fwrite (bad_hash,             sizeof (char), strlen (bad_hash)             * sizeof (char), DEBUG_FILE);
    if (*ERRORS & OUT_OF_CAPACITY)      fwrite (out_of_capacity,      sizeof (char), strlen (out_of_capacity)      * sizeof (char), DEBUG_FILE);
    if (*ERRORS & STACK_UNDERFLO)       fwrite (stack_underflo,       sizeof (char), strlen (stack_underflo)       * sizeof (char), DEBUG_FILE);
    if (*ERRORS & STACK_FLO)            fwrite (stack_flo,            sizeof (char), strlen (stack_flo)            * sizeof (char), DEBUG_FILE);
    if (*ERRORS & GOOSE_ERROR)          fwrite (goose_error,          sizeof (char), strlen (goose_error)          * sizeof (char), DEBUG_FILE);
    if (*ERRORS & SOME_ONE_POOPED_HERE) fwrite (some_one_pooped_here, sizeof (char), strlen (some_one_pooped_here) * sizeof (char), DEBUG_FILE);
    
    fwrite ("\n", 1, 1, DEBUG_FILE);

    fclose (DEBUG_FILE);

    return 0;
}

int DoubleMemSet (stackElem * pointer, const stackElem num, size_t size)
{
    size /= sizeof (stackElem);

    for (size_t index = 0; index < size; index++)
    {
        pointer[index] = num;
    }

    return -1;
}