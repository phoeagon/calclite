/**
    this header file implements variable support
*/

#ifndef VAR_SUPPORT
#define VAR_SUPPORT

#include "calc.h"

typedef vector<double> memory_table;
typedef map<string,int> var_cast;
typedef var_cast :: iterator var_cast_it;
typedef vector<char> memory_init_table;

class   variables
{
public:
    void    init_system_var();
    void    init_system_var(int quiet);
    void    reset_var();
    void    reset_system_var();
    /** memory things */
    var_cast           var_table;
    memory_table       memory;
    memory_init_table    memory_init;

    double  get_var_pos(string a);/**get where is variable [a] stored in memory*/
    int     add_var(string,double);/** add a variable */
    int     add_var(string,double,int);
    void    del_var(string);
    double  eval_var(string ind , double val);/**evaluate a variable by name*/


    /** constructor */
    variables()
    {
        init_system_var(1);
        memory.reserve(_var_init_size);
        memory_init.reserve(_var_init_size);
    };
private:
    void    reset_all();
};


#endif
