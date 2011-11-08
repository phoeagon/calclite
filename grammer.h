/**
    this header file implements how this app handle statements and expressions.

    grammar class gets token support from its member, tkin (defined in token_stream_class.h)
    tkin has variable support in it.

    grammar class supports only single-char operators, so multi-char
        operators need to be replaced by preprocessor defined in "preprocessor.h".

    shift_opr(char) uses an un-used bit (the first bit) in a char to support
        additional operators and keep them from be mixed up with original ones.

    Grammar:
            <low priority>
              statement();
              boolean_expression();
              compare_expression();
              expression();
              term();
              unary_plus();
              exp_and_pow();
              factorial();
              primary();
            <high priority>

*/
#ifndef GRAMMER

#define GRAMMER

#include "calc.h"
#include "var_support.h"
#include "token_stream_class.h"
#include "function_support.h"

class grammar
{
public:
    grammar()
    {
        srand(time(NULL));
    }
    /**get DEBUG status*/
    int         debug()
    {
        return var_at_pos(tkin.vars().get_var_pos( "_debug" ) );
    } ;
    int         type_strict_level()
    {
        return var_at_pos( tkin.vars().get_var_pos( "_type_strict" ) );
    } ;
    int         var_strict_level()
    {
        return var_at_pos( tkin.vars().get_var_pos( "_var_strict" ) );
    } ;
    int         precision()
    {
        return var_at_pos( tkin.vars().get_var_pos( "_precision" ) );
    } ;

    /** functions that return a reference to variable-things**/
    variables   &var_data()
    {
        return tkin.vars();
    }
    double      &var_at_pos(int x)
    {
        return tkin.vars().memory[x];
    }
    char        &var_at_pos_if_init(int x)
    {
        return tkin.vars().memory_init[x];
    }
    int         var_count()
    {
        return tkin.vars().memory.size();
    }
    void        init_var()
    {
        tkin.vars().init_system_var();
    }

    /**debug function**/
    void        set_debug(int x)
    {
        var_at_pos(tkin.vars().get_var_pos("_debug"))=x;
    }
    void        set_var_strict_level(int x)
    {
        var_at_pos(tkin.vars().get_var_pos("_var_strict"))=x;
    }
    void        set_type_strict_level(int x)
    {
        var_at_pos(tkin.vars().get_var_pos("_type_strict"))=x;
    }

    double      run();/**calculate function*/

    /** references to stream-things */
    int         stream_position()
    {
        return tkin.l2r_position();
    }
    int         stream_size()
    {
        return tkin.stream_size();
    }
    void        empty_strm_buffer()
    {
        tkin.empty_strm_buffer();
    }
    istringstream &strm()
    {
        return tkin.strm;
    }
protected:
    token_stream tkin;/** token_stream data*/
private:
    int force_int(double x)
    {
        if ( !iswhole( x ) && type_strict_level() )throw bitwise_int();
        return ( int ) x ;
    }
    double      statement();            /**R*/  /** assignment = */
    double      boolean_expression();   /**L*/  /** <bitwise> | &  ^^(xor) */
    double      compare_expression();   /**L*/  /** > < == >= <=*/
    double      expression();           /**L*/  /** +- */
    double      term();                 /**L*/  /** * % / */
    double      unary_plus();           /**R*/  /** <unary> + - @(bitwise not) ~(logic not)*/
    double      exp_and_pow();          /**L*/  /** ^ (power) */
    double      factorial();            /**L*/  /** <unary> factorial */
    double      primary();              /**L*/  /** () []-abs */
};


#endif
