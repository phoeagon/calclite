/**
    this file implements system functions
    isfuntion(s)    check if "s" is a function defined
*/
#ifndef FUNCTION_SUPPORT

#define FUNCTION_SUPPORT

#include "calc.h"

typedef map<string,int> function_cast;
typedef function_cast::iterator function_cast_it;

class functions
{
public:
    void    init_system_func();

    int    isfunction( string s );          /**check if is a function defined*/
    void    add_function( string s ,int x);/**add a function named s with label x*/
    double  get_result(int opr,double x);   /** get the result of the given function labeled opr*/

    function_cast_it    end_of_list()
    {
        return fs.end();
    }
    functions()
    {
        init_system_func();
    }

protected:
    function_cast fs;
    int x;
};
/** function labels */
static const int _func_sin = 0;
static const int _func_cos = 1;
static const int _func_tan = 2;
static const int _func_cot = 3;
static const int _func_sec = 4;
static const int _func_csc = 5;
static const int _func_exp = 6;
static const int _func_ln = 7;
static const int _func_log = 7;
static const int _func_log2 = 8;
static const int _func_log10 = 9;
static const int _func_rand = 10;
static const int _func_dtor = 11;
static const int _func_rtod = 12;
static const int _func_sqrt = 13;
static const int _func_floor = 14;
static const int _func_ceil = 15;
static const int _func_sinh = 16;
static const int _func_cosh = 17;
static const int _func_tanh = 18;
static const int _func_asin = 19;
static const int _func_acos = 20;
static const int _func_atan = 21;
static const int _func_sign = 22;
static const int _func_signpow = 23;
static const int _func_invert = 24;
static const int _func_abs = 25;
static const int _func_round = 26;



#endif

