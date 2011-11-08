/**
    this header file is intended for preprocess.
    as the implementation in "grammar" class supports only
    one statement in a row, only operators in a character,
    this part do a substitution to the data read from std::cin
    and processes them before pushing everything back
    to grammer.strm for grammer part to read.

    namespace preprocessor{
        pre_read()      //  read data from std::cin
        replace_str()   //  find and replace a given pattern in a string into a new one
        pre_push()      //  push processed data back to std::cin
    }

*/

#ifndef PREPROCESSOR
#define PREPROCESSOR

#include "calc.h"

namespace preprocessor
{

extern string storage; /**buffer string*/ //in preprocessor.cpp
extern int storage_len;                 // in preprocessor.cpp

void pre_read();/**reads a line from cin into storage*/


int replace_str(string &storage,const char*pattern, const char* new_pattern);
/**replace a given pattern into new_pattern*/


void    pre_push();
/**push back storage[] back to cin*/

int pre_proc();
/**get a line from cin*/


}
#endif
