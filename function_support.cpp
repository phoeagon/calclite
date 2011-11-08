/*
    this file implements methods defined in function_support.h
*/
#include "function_support.h"

int   functions ::    isfunction( string s )
{
    /**check if "s" is function defined*/
    function_cast_it data = fs.find(s) ;
    if (data==fs.end())
        return -1;
    else return data->second;
}
void    functions :: add_function(string s,int x)
{
    /**add a function named s with label x*/
    fs[s] = x;
}
void    functions ::    init_system_func()
{
#define add_func(x)\
        add_function(#x,_func_##x);
    add_func(sin);
    add_func(cos);
    add_func(tan);
    add_func(cot);
    add_func(sec);
    add_func(csc);
    add_func(asin);
    add_func(acos);
    add_func(atan);
    add_func(ln);
    add_func(log);
    add_func(log2);
    add_func(log10);
    add_func(exp);
    add_func(rand);
    add_func(log2);
    add_func(sinh);
    add_func(cosh);
    add_func(tanh);
    add_func(rtod);
    add_func(dtor);
    add_func(floor);
    add_func(ceil);
    add_func(sign);
    add_func(signpow);
    add_func(invert);
    add_func(abs);
    add_func(round);
}

double  functions :: get_result(int opr,double x)
{
    /** get the result of the given function labeled opr*/
    switch(opr)
    {
    case _func_sin :
        return  sin(x);
    case _func_cos :
        return  cos(x);
    case _func_tan :
        return  tan(x);
    case _func_cot :
        return  1/tan(x);
    case _func_sec :
        return  1/cos(x);
    case _func_csc :
        return  1/sin(x);
    case _func_exp :
        return  exp(x);
    case _func_ln :
        return  log(x);
    case _func_log2 :
        return  log(x)/log(2);
    case _func_log10 :
        return  log(x)/log(10);
    case _func_rand :
        return  rand()%((int)x);
    case _func_dtor :
        return  x*_m_pi/180;
    case _func_rtod :
        return  x*180/_m_pi;
    case _func_sqrt :
        return  sqrt(x);
    case _func_floor :
        return  floor(x);
    case _func_ceil :
        return  ceil(x);
    case _func_sinh :
        return  sinh(x);
    case _func_cosh :
        return  cosh(x);
    case _func_tanh :
        return  tanh(x);
    case _func_sign :
        return  equal(x,0) ? 0 : ( (x>0) - (x<0) );
    case _func_signpow:
        return  pow(-1,x);
    case _func_invert:
        return  (1/x);
    case _func_abs:
        return  abs(x);
    case _func_round:
        return  round(x);
    default:
        break;
    }
}
