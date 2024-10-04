/// @file Utils.cpp

#include "..\inc\Utils.h"

/**
 * @brief Checks double error.
 * \param [in]  val    Value of the input double variable
 * \param [out] return Return is this doouble == 0
 */

bool IsZero (const double val)                                                            // Checking double for errors
{
    my_assert (isfinite (val));

    if (EPSILON >= fabs (val))
    {
        return true;
    }
    return false;
}

/**
 * @brief Compearing two double nums
 * \param [in]  firstNum   First double num
 * \param [in]  secondNum  Second double num
 * \param [out] true/false Is this true or false
 */

bool DoubleComparison (const double firstNum, const double secondNum)               // Compare two double
{
    my_assert (isfinite (firstNum));
    my_assert (isfinite (secondNum));

    return IsZero (firstNum - secondNum);
}

/**
 * @brief Clean buffer
 */

void BufferCleaner ()                                                               // Clean Buffer
{ 
    int ch = 0;

    while ((ch = getchar ()) != '\n' && ch != EOF) {}
}

/**
 * @brief Function, which skips spaces after User`s text and returns first not-space char
 * \param [out] lastChar Returns false (not \\n or EOF) or True (if \\n or EOF)
 */

bool SkipSpaces ()
{
    int isSpace = 0;

    while ((isSpace = getchar ()) == ' ' || isSpace == '\t') {}
    
    if (isSpace == '\n' || isSpace == EOF)
    {
        return true;
    }
    return false;
}

/**
 * @brief Counts the number of tests in the file
 * \param [in] fileFirstElement Addres of file first element
 */

int StrCounter (char * fileFirstElement)                                             // Count quantity of tests
{
    int counterStr = 0;

    while (*fileFirstElement != '\0')
    {
        if (*fileFirstElement == '\n')
        {
            counterStr++;
            fileFirstElement++;
            while (*fileFirstElement == '\n')
            {
                fileFirstElement++;
                continue;
            }
        }
        else
            fileFirstElement++;
    }
    return counterStr + 1;
}

char * FileToStr (const char * file_directory)                          
{
    my_assert (file_directory != NULL);

    size_t file_size = ReadFileSize (file_directory);

    FILE* file_with_onejka = fopen (file_directory, "rb");
    my_assert (file_with_onejka != 0);

    char * pointer_to_text = (char *) calloc (file_size + 1, sizeof (char));
    my_assert (file_size != 0);

    size_t check_size = (int) fread (pointer_to_text, sizeof (char), file_size, file_with_onejka);
    my_assert (check_size == file_size);

    pointer_to_text[file_size] = '\0';

    return pointer_to_text;
}

size_t ReadFileSize (const char * file_directory)
{
    my_assert (file_directory != NULL);

    struct stat to_take_file_size = {};
    stat (file_directory, &to_take_file_size);                                      
    my_assert (to_take_file_size.st_size);

    return to_take_file_size.st_size;
}
