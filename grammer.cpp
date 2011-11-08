/*
    this file implements methods defined in grammer.h
*/
#include "grammer.h"
#include "var_support.h"
#include "token_stream_class.h"
#include "function_support.h"

double  grammar ::  statement()
{
    /**R*/  /** assignment = */
    if (debug())cerr<<"statement: "<<endl;

    token_type lvalue = tkin.get_token();
    if (lvalue.first != _var_type) /** if next first token is not a variable */
    {
        tkin.putback();
        return boolean_expression();
    }

    token_type data = tkin.get_token();
    if (data.first!=_assign_type) /**  if next operator is not assignment */
    {
        tkin.putback();
        tkin.putback();/** put back the variable and operator */
        return boolean_expression();
    }

    while ( 1 )
    {
        switch( (int)data.second )
        {
        case '=':
        {
            double x = statement();
            tkin.vars().memory_init[lvalue.second] = 1;
            return var_at_pos(lvalue.second) = x;
        }
        //other assignment operators to be added here
        default:
            throw grammar_error();
        }
    }
}
double  grammar ::  run()                   /** main calculation function */
{
    srand(time(NULL));
    tkin.init();

    if ( tkin.data().size() == 1 &&
            tkin.data()[0].first == _cmd_type)  /** if is a command */
    {
        int flag = ( tkin.data()[0].second );
        if ( flag == '#' )
            throw user_exit();
        else if ( flag == '?' )
            throw help_info();
        else
            throw bad_input();
    }
    if (tkin.data().size()==0)throw null_statement();/**if expression is empty*/

    return statement();/** calculates */
}
double  grammar ::  boolean_expression()
{
    /**L*/  /** <bitwise> | &  ^^(xor) */
    //left associativity
#ifdef _DEBUG
    if (debug())    cerr<<"boolean_expression:"<<tkin.l2r_position()<<endl;
#endif

    double left = compare_expression();
    token_type t = tkin.get_token();/** next token */
    while(1)
    {
        switch((int)t.second)
        {
        case '&':
            /** bitwise and requires integer-value */
            left = (int)left & force_int(compare_expression());
            t = tkin.get_token();
            break;
        case '|':
            /** bitwise or requires integer-value */
            left = (int)left & force_int(compare_expression());
            t = tkin.get_token();
            break;
        case shift_opr('^'):
            /** bitwise sor requires integer-value */
            left = (int)left ^ force_int(compare_expression());
            t = tkin.get_token();
            break;
        default:
            tkin.putback();
            return left;
        }
    }
}
double  grammar ::  compare_expression()
{
    /**L*/  /** > < == >= <=*/
    //left associates
#ifdef _DEBUG
    if (debug())    cerr<<"compare_expression:"<<tkin.l2r_position()<<endl;
#endif

    double left = expression();
    token_type t = tkin.get_token();    /** next token*/
    while(1)
    {
        switch((int)t.second)
        {
        case '>':
            left = left>expression();
            t = tkin.get_token();
            break;
        case '<':
            left = left<expression();
            t = tkin.get_token();
            break;
        case shift_opr('>'):
            left = left>=expression() ;
            t = tkin.get_token();
            break;
        case shift_opr('<'):/** <= */
            left = left<=expression();
            t = tkin.get_token();
            break;
        case shift_opr('='):/** >= */
            left = (left==expression());
            t= tkin.get_token();
            break;
        default:
            tkin.putback();
            return left;
        }
    }
}
double   grammar ::     expression()
{
    /**L*/  /** +- */
#ifdef _DEBUG
    if (debug())    cerr<<"expression:"<<tkin.l2r_position()<<endl;
#endif
    double left = term();
    token_type data = tkin.get_token(); /** next token */
    while(1)
    {
        switch((int)data.second)
        {
        case '+':
            left+=term();
            data=tkin.get_token();
            break;
        case '-':
            left-=term();
            data=tkin.get_token();
            break;
        default:
            tkin.putback();
            return left;
        }
    }
}
double  grammar ::  term()
{
    /**L*/ /** % / %  _P_ _C_ _G_ _L_*/
#ifdef _DEBUG
    if (debug())cerr<<"term:"<<tkin.l2r_position()<<endl;
#endif

    double left = unary_plus();
    token_type data = tkin.get_token(); /** next token */
    while(1)
    {
        switch( (int)data.second )
        {
        case '*':            /** multiplies */
        {
            left *= unary_plus();
            data = tkin.get_token();
            break;
        }
        case '/':            /** division */
        {
            double dvsr = unary_plus();
            if (equal(dvsr,0))
            {
                throw divide_zero() ;    /**reject 0 divisor*/
            }
            left /= dvsr;
            data = tkin.get_token();
            break;
        }
        case '%':
        {
            /** modulus */ /** requires integer-value*/
            int val1 = force_int(left);
            int val2 = force_int(unary_plus());
            if (val2==0)throw divide_zero();
            left = val1 % val2;
            data = tkin.get_token();
            break;
        }
        case shift_opr('C'): /** combination - binomial*/
        {
            /** requires integer-value */
            int val1 = force_int(left);
            int val2 = force_int(unary_plus());
            return binomial(val1,val2);
        }
        case shift_opr('P'):
        {
            /** permutation - arrangement*//** int value*/
            int val1 = force_int(left);
            int val2 = force_int(unary_plus());
            return permutation(val1,val2);
        }
        case shift_opr('G'):
        {
            /** gcd *//** int value*/
            int val1 = force_int(left);
            int val2 = force_int(unary_plus());
            return gcd(val1,val2);
        }
        case shift_opr('L'):
        {
            /** lcm *//** int value*/
            int val1 = force_int(left);
            int val2 = force_int(unary_plus());
            return lcm(val1,val2);
        }
        default :
            tkin.putback();
            return left;
        }
    }
}
double  grammar ::   unary_plus()
{
    /**R*/  /** <unary> + - @(bitwise not) ~(logic not)*/
    //right associate
#ifdef _DEBUG
    if (debug())cerr<<"unary_plus()"<<tkin.l2r_position()<<endl;
#endif

    token_type t = tkin.get_token();    /** next token */
    if ( t.first == _opr_type )
    {
        switch( (int)(t.second) )
        {
        case '+':
            return unary_plus();
        case '-':
            return -unary_plus();
        case '@':
            return ~force_int(unary_plus());    /**int value*/
        case '~':
            return !force_int(unary_plus());    /**int value*/
        default :
            ;
        }
    }
    tkin.putback();
    return exp_and_pow();
}
double  grammar ::   exp_and_pow()
{
    /**L*/  /** ^ (power) */
    //right associate
#ifdef _DEBUG
    if (debug())cerr<<"exp_and_pow:"<<tkin.l2r_position()<<endl;
#endif
    double left = factorial();
    token_type t = tkin.get_token();    /** next token */
    switch( (int)t.second )
    {
    case '^':
    {
        double v2 = exp_and_pow();
        left = pow(left,v2);
        if (errno)  errno = 0 , throw exp_undef();/** if pow(x,y) returns error*/
        return left;
    }
    default :
        tkin.putback();
        return left;
    }
}
double  grammar ::   factorial()
{
    /**L*/  /** <unary>! factorial */
    //left associative operations with high priority "!"
    //also, it involves single value
#ifdef _DEBUG
    if (debug())cerr<<"factorial:"<<tkin.l2r_position()<<endl;
#endif
    double left = primary();
    token_type t = tkin.get_token();    /** next token */
    while ( 1 )
    {
        switch( (int)t.second )
        {
        case '!':   /** factorial requires integer-value */
        {
            int x = force_int(left);
            int f = 1;
            while ( x > 0 ) f *= x--;
            left = f;
            t = tkin.get_token();
            break;
        }
        default :
            tkin.putback();
            return left;
        }
    }
}
double  grammar ::  primary()
{
    /**L*/  /** () []-abs */
#ifdef _DEBUG
    if (debug())    cerr<<"primary: "<<tkin.l2r_position()<<endl;
#endif

    token_type t = tkin.get_token();
    switch( (int)t.first )
    {
    case( _var_type ):
    {
        if ( debug() ) /** print variable info */
        {
            cerr<<"memory size:"<<var_count()<<endl;
            cerr<<"at memory: "<<t.second<<endl;
        }
        if ( t.second < var_count() )
        {
            if ( var_at_pos_if_init( (int)t.second ) == 0 )
            {
                /** if variable already defined */
                switch( var_strict_level() )
                {
                case 1:
                    cout<<"Warning: uninitialized variable "
                        "detected! zeroed it by default!"<<endl;
                    break;
                case 2:
                    throw no_such_var();
                default:
                    ;
                }
            }
            return var_at_pos( (int)t.second );
        }
        else
            throw no_such_var();
        break;
    }
    case ( _number_type ):
        return t.second;
    case ( _func_type ):
    {
        int x = t.second;
        double xin = primary();
        return tkin.function().get_result(x,xin);/** to function_support.h */
    }
    case ( _brk_type ):
    {
        double d = statement();
        token_type tail = tkin.get_token();
        if ( tail.first == _brk_type )
        {
            switch( (int)(t.second) )
            {
            case '(':
                if ( (int)(tail.second) != ')' )
                    throw grammar_error();
                else return d;
            case '[':
                if ( (int)(tail.second)!=']' )
                    throw grammar_error();
                else return abs(d);
            default:
                throw grammar_error();
            }
        }
        else throw grammar_error();
    }
    default :
        throw grammar_error();
    }

}


