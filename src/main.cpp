#include "../inc/Stack.h"
#include "../src/Defines.h"
#include "../src/Utils.h"
#include "../src/Errors.h"
int main ()
{

    COLOR_PRINT (STRANGE, "Lets go\n");
    Stack_t stk = {};

    StackCtor (&stk, STANDART_SIZE);
    

    for (int i = 0; i < 5; i++)
    {
        StackPush (&stk, i);
    }
    for (int i = 0; i < 11; i++)
    {
        COLOR_PRINT (BLUE, "<%lg>, size = <%d>\n", stk.data[stk.size - i - 1], stk.size - i);
    }
    
    printf ("pointer to stack: <%p>\nsize: <%d>\tcapacity: <%d>\n", 
            &stk.data, stk.size, stk.capacity);
    
    // char * fall = (char *) &stk.data;
    // for (int i = 0; i < 1; i ++)
    // {
    //     *(fall + i) = 1;
    // }

    while (stk.size > 0)
    {
        COLOR_PRINT (GREEN, "%lg - poped from stack\n", StackPop (&stk));
    }

    for (int i = 0; i < stk.size + 10; i++)
    {
        COLOR_PRINT (BLUE, "<%lg>, size = <%d>\n", stk.data[i], stk.size - i);
    }


    StackDtor (&stk);


//-----------------------------------------------------------------

}