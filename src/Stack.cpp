#include "../inc/Stack.h"

#include "../src/Defines.h"
#include "../src/Utils.h"
#include "../src/Errors.h"

static char *   LOG_FILE      = "DEBUG.txt"; 
static n_Stacks inited_stacks = {};

static char * stack_errors_interpretation[ERRORS_SIZE] = 
{
    "There is NULL pointer\n", 
    "Bad hash\n", 
    "Size more than capacity\n",
    "Capacity = 0\n",
    "AAAAA, Gals are here!!! (Our gooses are bad)\n",
    "Stack flo\n", 
    "You pooped into your data\n",
    "You got something repeated\n",
    "There is no inited stack or another problem\n"
};

static void MemNew                 (Stack_t * stk, REALLOC_MODE flag);
static int  Verificator            (Stack_t * stk);
static void StackDump              (Stack_t * stk, const int ERROR, const char * var_name, const char * file_name, const int line);
static int  HashCalc               (const char * data, size_t size);
static void DoubleMemSet           (stackElem  * pointer, const stackElem num, size_t size);
static int  HashBufferCalc         (const char * data, size_t size);
static void FileWriter             (const char * file_directory, const unsigned * ERRORS);
static int  AddToStackChecker      (Stack_t * stk);
static int  RemoveFromStackChecker (Stack_t * stk);
static int  InitStackChecker       (Stack_t * stk);



void StackCtor (Stack_t * stk, size_t capacity)
{                                                                                                                                                                                          //popa       
    if (stk == NULL)
    {
        Isolated_fprintf(;, "163 stack on my neck. Bad pointer to stack, we cant create a stack, kek.\n")
        return;
    }

#ifdef DEBUG
    bool flag = false;

    CHEKING_FOR_STACK_AVAILABILITY(stk, flag)

    if (flag)
    {
        Isolated_fprintf(;,"You made a repeated stack\n")
        return;
    }

    if (inited_stacks.capacity == 0)
        InitStackChecker (stk);
    else
        AddToStackChecker (stk);

#endif

    stk->capacity = capacity;
    stk->size     = 0;
    
    stk->data = (stackElem *) calloc (stk->capacity * sizeof (stackElem) + 
                                      ADD_ALIGEN(stk->capacity) + 2 * MEM_OF_GOOSES, sizeof (char));

    DoubleMemSet (stk->data, POISON_NUM, stk->capacity * sizeof (stackElem) + ADD_ALIGEN(stk->capacity) + 2 * MEM_OF_GOOSES);

#ifdef GOOSES
    *(gooseType *) stk->data = stk->goose1;
    
    stk->data = (stackElem *) ((char *) stk->data + MEM_OF_GOOSES);

    *(gooseType *) ((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN(stk->capacity)) = stk->goose2;
#endif

#ifdef ON_HASH
    ON_HASH(stk)
#endif

    return;
}

void StackDtor (Stack_t * stk)
{
    VERIFY_STACK(stk)

    RemoveFromStackChecker (stk);

    free((char *) stk->data - sizeof (gooseType));
    stk->data = NULL;

#ifdef GOOSES
    stk->goose1   = GOOSE_CONST;
#endif

    stk->size     = STANDART_STACK_ELEM;
    stk->capacity = STANDART_STACK_ELEM;

#ifdef GOOSES
    stk->goose2   = GOOSE_CONST;
#endif

#ifdef HASH_CALC
    stk->BufferHash = 0;
    stk->HashAddres = 0;
#endif

    return;
}

void StackPush (Stack_t * stk, stackElem top)
{
    VERIFY_STACK(stk)

    if (stk->size == stk->capacity)
    {
        MemNew (stk, INCREASE);
    }

    stk->data[stk->size++] = top;

    ON_HASH(stk)

    VERIFY_STACK(stk)

    return;
}

stackElem StackPop (Stack_t * stk)
{
    VERIFY_STACK(stk)
    if (stk->size == 0)
    {
        COLOR_PRINT (RED, "Can`t pop, there is no elements\n");
        return IS_NULL;
    }

    if (stk->size <= (stk->capacity - DELTA_CAPACITY_SIZE) / 2)
        MemNew (stk, DECREASE);

    stackElem poped = stk->data[--stk->size];

    stk->data[stk->size] = POISON_NUM;

    ON_HASH(stk)

    return poped;
}

static void MemNew (Stack_t * stk, REALLOC_MODE flag)
{
    VERIFY_STACK(stk)

    /* decrease or increase capacity */
    if (flag)
        stk->capacity *= 2;
    else
        stk->capacity /= 2;

    /* allocating memory */
    stk->data = (stackElem *) ((char *) realloc((char *) stk->data - MEM_OF_GOOSES, stk->capacity * sizeof (stackElem) + 
                                                ADD_ALIGEN(stk->capacity) + 2 * MEM_OF_GOOSES) + MEM_OF_GOOSES);

    /* fill poisons num all bites */
    DoubleMemSet ((stackElem *) stk->data + stk->size, POISON_NUM, stk->capacity * sizeof (stackElem) + ADD_ALIGEN(stk->capacity) + 
                  MEM_OF_GOOSES - stk->size * sizeof (stackElem));

#ifdef GOOSES
    /* add canary at the beggining */
    *(gooseType *) ((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN(stk->capacity)) = stk->goose2;
#endif

    ON_HASH(stk)

    VERIFY_STACK(stk)
}


#define CHECK_GOOSES(num) if (num != GOOSE_CONST) ERRORS |= GOOSE_ERROR;

static int Verificator (Stack_t * stk)
{ 
    unsigned ERRORS = 0;
    bool flag = false;

    if (stk == NULL)
    {
        ERRORS |= IS_NULL;
        return ERRORS;
    }

    CHEKING_FOR_STACK_AVAILABILITY(stk, flag)

    if (!flag)
    {
        Isolated_fprintf (0, "There is no inited stacks or where is a problem somewhere\n")
        ERRORS |= NO_INITED_STACKS;
        return ERRORS;
    }
    if (stk->capacity <= 0)
        ERRORS |= STACK_UNDERFLO;

    if (stk->size > stk->capacity)  
        ERRORS |= OUT_OF_CAPACITY;

    if (stk->capacity > 0xDAFAC)
        ERRORS |= STACK_FLO;

    if (stk->data == NULL)
    {
        ERRORS |= IS_NULL;
        return ERRORS;
    }
    
#ifdef GOOSES

    CHECK_GOOSES(stk->goose1);

    CHECK_GOOSES(stk->goose2);

    if ((char *) stk->data - MEM_OF_GOOSES >= 0)
    {
        if (* (gooseType *) ((((char *) stk->data) - MEM_OF_GOOSES)) != GOOSE_CONST ||
            * (gooseType *) (((char *) stk->data) + stk->capacity * sizeof (stackElem) + ADD_ALIGEN(stk->capacity)) != GOOSE_CONST)
            ERRORS |= SOME_ONE_POOPED_HERE;        
    }

#endif

#ifdef HASH_CALC

    if (HashCalc ((char *) stk, sizeof (Stack_t)) != stk->HashAddres)
        ERRORS |= BAD_HASH;
    if (HashBufferCalc ((char *) stk->data, stk->size) != stk->BufferHash)
        ERRORS |= BAD_HASH;

#endif

    if (ERRORS)
        FileWriter(LOG_FILE, &ERRORS);
    return ERRORS;
}

#undef CHECK_GOOSES

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

#define Dump_to_file(...) fprintf(DEBUG_FILE, __VA_ARGS__);

static void StackDump (Stack_t * stk, const int ERROR, const char * var_name, const char * file_name, const int line)
{
    FILE * DEBUG_FILE = fopen ("DEBUG.txt", "a+");

    if (DEBUG_FILE == NULL)
    {
        COLOR_PRINT(RED, "Can`t open file. We can`t print for u(\n")
        return;
    }
    if (ERROR & NO_INITED_STACKS)
        return;

    Dump_to_file("Strack_t <%p> ", stk);
    Dump_to_file("born at %s: %d, ", file_name, line);
    Dump_to_file("name: \"%s\"\n", var_name);

    if (stk == NULL)
    {
        Dump_to_file("pointer to Stack_t str = NULL\n");
        return;
    }

    if (stk->data == NULL)
    {
        Dump_to_file("Data is NULL\n");
        return;
    }

    Dump_to_file("ALLIGEN: <%d>,\tGOOSE_SIZE: <%d>\n", ADD_ALIGEN (stk->capacity), MEM_OF_GOOSES)

    Dump_to_file("size = <%d>",         stk->size);
    Dump_to_file("\tcapasity = <%d>\n", stk->capacity);

    PRINT_GOOSES(stk->goose1);

    PRINT_GOOSES(stk->goose2);

    if (ERROR & SOME_ONE_POOPED_HERE)
        Dump_to_file("Sorry, your buffer is broke\n")
    else
    {
        PRINT_GOOSES(*((char *) stk->data - MEM_OF_GOOSES));

        PRINT_GOOSES(*((char *) stk->data + stk->capacity * sizeof (stackElem) + ADD_ALIGEN (stk->capacity)));
    }

#ifdef HASH_CALC
    Dump_to_file("Hash: %d\n",        stk->HashAddres);
    Dump_to_file("Buffer hash: %d\n", stk->BufferHash);
#endif


    if (!(OUT_OF_CAPACITY & ERROR || STACK_FLO & ERROR || STACK_UNDERFLO & ERROR))
    {
        size_t counter = 0;
        while (counter < stk->capacity)
        {   
            Dump_to_file("[%d] = ", counter);
            if (DoubleComparison (stk->data[counter], POISON_NUM))
            {
                Dump_to_file("%x (POISON)\n", stk->data[counter]);
                counter++;
            }
            else
            {
                Dump_to_file("%lg\n",   stk->data[counter]);
                counter++;
            }
        }
    }
    else
        Dump_to_file("Sorry, our capacity is bad, we can`t print stack\n");

    Dump_to_file("Dump ends.\n");
    
    if (!fclose (DEBUG_FILE))
        COLOR_PRINT(RED, "File didn`t close\n")
}
#undef Dump_to_file

static int HashCalc (const char * data, size_t size)
{
    int Hash = 0; // rename
    //size is bad
    size -= (sizeof (hashType) * 2 + sizeof (gooseType));

    for (size_t counter = 0; size > counter; counter++)
    {
        Hash = ((Hash << 5) + Hash) ^ data[counter];
    }

    return Hash;
}

static int HashBufferCalc (const char * data, size_t size)
{
    int Hash = 0;

    for (size_t counter = 0; size > counter; counter++)
    {
        Hash = ((Hash << 5) + Hash) ^ data[counter];
    }

    return Hash;
}

static void FileWriter (const char * file_directory, const unsigned * ERRORS)
{
    FILE * DEBUG_FILE = fopen (file_directory, "a+");

    if (!DEBUG_FILE)
    {
        COLOR_PRINT (RED, "ERROR: can`t create a file\n");
        return;
    }

    rewind (DEBUG_FILE);

    for (size_t i = 0; ERRORS_SIZE > i; i++)
    {
        if (*ERRORS & (i << 1))
        {
            fprintf (DEBUG_FILE, "%s", stack_errors_interpretation[i]);
        }
    }
    fwrite ("\n", 1, 1, DEBUG_FILE);

    if (!fclose (DEBUG_FILE))
        COLOR_PRINT(MANGETA, "File didn`t close\n"); 
}

static void DoubleMemSet (stackElem * pointer, const stackElem num, size_t size)
{
    size /= sizeof (stackElem);

    for (size_t index = 0; index < size; index++)
    {
        pointer[index] = num;
    }
    return;
}

int RemoveFromStackChecker (Stack_t * stk)
{   
    for (int i = 0; i < inited_stacks.capacity; i++)
        if (inited_stacks.quentity_of_stacks[i] == stk)
            inited_stacks.quentity_of_stacks[i]  = NULL;

    for (int i = 0; i < inited_stacks.capacity - 1; i++)
    {
        if (inited_stacks.quentity_of_stacks[i] == NULL)
        {
            inited_stacks.quentity_of_stacks[i]     = inited_stacks.quentity_of_stacks [i + 1];
            inited_stacks.quentity_of_stacks[i + 1] = NULL;
        }
    }

    inited_stacks.capacity--;

    inited_stacks.quentity_of_stacks = (Stack_t **) realloc (inited_stacks.quentity_of_stacks, inited_stacks.capacity * sizeof (Stack_t *));
}

int AddToStackChecker (Stack_t * stk)
{
    inited_stacks.quentity_of_stacks = (Stack_t **) realloc (inited_stacks.quentity_of_stacks, inited_stacks.capacity + 1);

    inited_stacks.quentity_of_stacks[inited_stacks.capacity + 1] = NULL;

    inited_stacks.quentity_of_stacks[inited_stacks.capacity++]   = stk;
}

int InitStackChecker (Stack_t * stk)
{
    inited_stacks.quentity_of_stacks = (Stack_t **) calloc (2, sizeof (Stack_t *));

    inited_stacks.quentity_of_stacks[inited_stacks.capacity + 1] = NULL;

    inited_stacks.quentity_of_stacks[inited_stacks.capacity++]   = stk;
}