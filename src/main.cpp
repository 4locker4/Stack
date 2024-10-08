#include "../inc/Stack.h"

int main ()
{
    COLOR_PRINT (STRANGE, "Lets go\n");
    Stack_t stk = {};
    Stack_t stk9 = {};

    StackCtor (&stk, STANDART_SIZE);
    StackCtor (&stk9, STANDART_SIZE);

    for (int i = 0; i < 128; i++)
    {
        StackPush (&stk, (double) i);
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
        COLOR_PRINT (GREEN, "%lg\n", StackPop (&stk));
    }

    for (int i = 0; i < stk.size + 10; i++)
    {

        COLOR_PRINT (BLUE, "<%lg>, size = <%d>\n", stk.data[i], stk.size - i);
    }


    StackDtor (&stk);


//-----------------------------------------------------------------

}