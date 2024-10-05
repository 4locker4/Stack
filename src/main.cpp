#include "../inc/StackCtor.h"

int main ()
{
    COLOR_PRINT (STRANGE, "Lets go\n");
    Stack_t stk = {};

    StackCtor (&stk, STANDART_SIZE);


//-----------------------------------------------------------------
    for (int i = 0; i < 128; i++)
    {
        StackPush (&stk, (double) i / 31);
    }

    for (int i = 0; i < 128; i++)
    {
        COLOR_PRINT (BLUE, "<%lg>, size = <%d>\n", stk.data[stk.size - i - 1], stk.size - i);
    }

    printf ("pointer to stack: <%p>\nsize: <%u>\tcapacity: <%u>\n", 
            &stk.data, stk.size, stk.capacity);
    
    char * fall = (char *) &stk.data;
    for (int i = 0; i < 1; i ++)
    {
        *(fall + i) = 1;
    }

    while (stk.size > 0)
    {
        StackPop (NULL);
    }

    StackDtor (&stk);

//-----------------------------------------------------------------

}

// int Test ()
// {
//     stackEl_t test1[30] = { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
//                            11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
//                            21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    

// }