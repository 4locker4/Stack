/// @file Utils.h

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "Errors.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const double EPSILON = 1e-10;                                                       ///< Error constant double

bool   IsZero             (const double val);                                         ///< Double error check
bool   DoubleComparison   (const double firstNum, const double secondNum);            ///< Checking equality double
void   BufferCleaner      ();                                                         ///< Buffer cleaner
bool   SkipSpaces         ();                                                         ///< Skip spaces and tabs after User`s text, returns first char
int    StrCounter         (char * fileFirstElement);                                  ///< Count quantity of tests
void   TestArrayReturner  (int fileSize, char * fileFirstElement);                    ///< Put values into array of struct (test data array)
char * FileToStr          (const char * file_directory);                              ///< Return string with all file`s text
size_t ReadFileSize       (const char * file_directory);                              ///< Return fili size



#endif ///not UTILS_H
