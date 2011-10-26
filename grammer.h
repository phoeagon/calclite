#ifndef GRAMMER
class grammar{
    public:
        grammar(){srand(time(NULL));}
        /**get DEBUG status*/
		int         debug()
                { return var_at_pos(tkin.vars().get_var_pos( "_debug" ) ); } ;
        int         type_strict_level()
                { return var_at_pos( tkin.vars().get_var_pos( "_type_strict" ) ); } ;
        int         var_strict_level()
                { return var_at_pos( tkin.vars().get_var_pos( "_var_strict" ) ); } ;
        int         precision()
                { return var_at_pos( tkin.vars().get_var_pos( "_precision" ) ); } ;

        /** functions that return a reference to variable-things**/
        variables   &var_data()         {return tkin.vars();}
        double      &var_at_pos(int x)  {return tkin.vars().memory[x];}
        char        &var_at_pos_if_init(int x)
                        {return tkin.vars().memory_init[x];}
        int         var_count()         {return tkin.vars().memory.size();}
        void        init_var()          {tkin.vars().init_system_var();}

        /**debug function**/
        void        set_debug(int x)    {var_at_pos(tkin.vars().get_var_pos("_debug"))=x;}
        void        set_var_strict_level(int x)  {var_at_pos(tkin.vars().get_var_pos("_var_strict"))=x;}
        void        set_type_strict_level(int x)  {var_at_pos(tkin.vars().get_var_pos("_type_strict"))=x;}

        double      run();/**calculate function*/

        /** references to stream-things */
        int         stream_position()   {   return tkin.l2r_position(); }
        int         stream_size()       {   return tkin.stream_size();  }
    protected:
        token_stream tkin;/** token_stream data*/
    private:
        int force_int(double x){
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
double  grammar ::  statement() {           /**R*/  /** assignment = */
    if (debug())cerr<<"statement: "<<endl;

    token_type lvalue = tkin.get_token();
    if (lvalue.first != _var_type){
            tkin.putback();
            return boolean_expression();
        }

    token_type data = tkin.get_token();
    if (data.first!=_assign_type){
            tkin.putback();     tkin.putback();
            return boolean_expression();
        }

    while ( 1 ) {
        switch( (int)data.second ) {
            case '=':
            {
                    double x = statement();
                    tkin.vars().memory_init[lvalue.second] = 1;
                    return var_at_pos(lvalue.second) = x;
            }
            default:    throw grammar_error();
        }
    }
}
double  grammar ::  run(){                  /** main calculation function */
    srand(time(NULL));
    tkin.init();

    if ( tkin.data().size() == 1 &&
        tkin.data()[0].first == _cmd_type){
            int flag = ( tkin.data()[0].second );
            if ( flag == '#' )
                throw user_exit();
            else if ( flag == '?' )
                throw help_info();
            else
                throw bad_input();
        }
    if (tkin.data().size()==0)throw null_statement();/**if expression is empty*/

    return statement();
}
double  grammar ::  boolean_expression(){   /**L*/  /** <bitwise> | &  ^^(xor) */
    //left associativity
    #ifdef _DEBUG
        if (debug())    cerr<<"boolean_expression:"<<tkin.l2r_position()<<endl;
    #endif

    double left = compare_expression();
    token_type t = tkin.get_token();
    while(1){
        switch((int)t.second){
            case '&':
                left = (int)left & force_int(compare_expression());
                t = tkin.get_token();break;
            case '|':
                left = (int)left & force_int(compare_expression());
                t = tkin.get_token();break;
            case shift_opr('^'):
                left = (int)left ^ force_int(compare_expression());
                t = tkin.get_token();break;
            default:tkin.putback();return left;
        }
    }
}
double  grammar ::  compare_expression(){   /**L*/  /** > < == >= <=*/
    //left associates
    #ifdef _DEBUG
        if (debug())    cerr<<"compare_expression:"<<tkin.l2r_position()<<endl;
    #endif

    double left = expression();
    token_type t = tkin.get_token();
    while(1){
        switch((int)t.second){
            case '>':   left = left>expression();   t = tkin.get_token();   break;
            case '<':   left = left<expression();   t = tkin.get_token();   break;
            case shift_opr('>'):
                left = left>=expression() ; t = tkin.get_token();   break;
            case shift_opr('<'):
                left = left<=expression();  t = tkin.get_token();   break;
            case shift_opr('='):
                left = (left==expression());    t= tkin.get_token();break;
            default:
                tkin.putback();return left;
        }
    }
}
double   grammar ::     expression(){       /**L*/  /** +- */
    #ifdef _DEBUG
        if (debug())    cerr<<"expression:"<<tkin.l2r_position()<<endl;
    #endif
    double left = term();
    token_type data = tkin.get_token();
    while(1){
        switch((int)data.second){
            case '+':
                left+=term();   data=tkin.get_token();  break;
            case '-':
                left-=term();   data=tkin.get_token(); break;
            default:
                tkin.putback(); return left;
        }
    }
}
double  grammar ::  term(){                 /**L*/ /** % / %  _P_ _C_ _G_ _L_*/
    #ifdef _DEBUG
        if (debug())cerr<<"term:"<<tkin.l2r_position()<<endl;
    #endif

    double left = unary_plus();
    token_type data = tkin.get_token();
    while(1){
        switch( (int)data.second ){
            case '*':{           /** multiplies */
                left *= unary_plus();
                data = tkin.get_token();
                break;}
            case '/':{           /** division */
                double dvsr = unary_plus();
                if (equal(dvsr,0)){throw divide_zero();}
                left /= dvsr;
                data = tkin.get_token();
                break;
            }
            case '%':{           /** modulus */
                int val1 = force_int(left);
                int val2 = force_int(unary_plus());
                if (val2==0)throw divide_zero();
                left = val1 % val2;
                data = tkin.get_token();
                break;
            }
            case shift_opr('C'):{/** combination - binomial*/
                int val1 = force_int(left);
                int val2 = force_int(unary_plus());
                return binomial(val1,val2);
            }
            case shift_opr('P'):{/** permutation - arrangement*/
                int val1 = force_int(left);
                int val2 = force_int(unary_plus());
                return permutation(val1,val2);
            }
            case shift_opr('G'):{/** gcd */
                int val1 = force_int(left);
                int val2 = force_int(unary_plus());
                return gcd(val1,val2);
            }
            case shift_opr('L'):{/** lcm */
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
double  grammar ::   unary_plus(){          /**R*/  /** <unary> + - @(bitwise not) ~(logic not)*/
    //right associate
    #ifdef _DEBUG
        if (debug())cerr<<"unary_plus()"<<tkin.l2r_position()<<endl;
    #endif

    token_type t = tkin.get_token();
    if ( t.first == _opr_type ){
        switch( (int)(t.second) ){
            case '+':   return unary_plus();
            case '-':   return -unary_plus();
            case '@':   return ~force_int(unary_plus());
            case '~':   return !force_int(unary_plus());
            default :   ;
        }
    }
    tkin.putback();
    return exp_and_pow();
}
double  grammar ::   exp_and_pow(){         /**L*/  /** ^ (power) */
    //right associate
    #ifdef _DEBUG
        if (debug())cerr<<"exp_and_pow:"<<tkin.l2r_position()<<endl;
    #endif
    double left = factorial();
    token_type t = tkin.get_token();
    switch( (int)t.second ){
        case '^':
            {
            double v2 = exp_and_pow();
            left = pow(left,v2);
            if (errno)  errno = 0 , throw exp_undef();
            return left;
            }
        default : tkin.putback();return left;
    }
}
double  grammar ::   factorial(){           /**L*/  /** <unary>! factorial */
    //left associative operations with high priority "!"
    //also, it involves single value
    #ifdef _DEBUG
        if (debug())cerr<<"factorial:"<<tkin.l2r_position()<<endl;
    #endif
    double left = primary();
    token_type t = tkin.get_token();
    while ( 1 ){
        switch( (int)t.second ){
            case '!':{
                int x = force_int(left);
                int f = 1;
                while ( x > 0 ) f *= x--;
                left = f;
                t = tkin.get_token();
                    break;
            }
            default : tkin.putback();return left;
        }
    }
}
double  grammar ::  primary(){              /**L*/  /** () []-abs */
    #ifdef _DEBUG
        if (debug())    cerr<<"primary "<<tkin.l2r_position()<<endl;
    #endif

    token_type t = tkin.get_token();
    switch( (int)t.first ){
        case( _var_type ):
        {
            if ( debug() ){
                cerr<<"memory size:"<<var_count()<<endl;
                cerr<<"at memory: "<<t.second<<endl;
            }
            if ( t.second < var_count() ){
            if ( var_at_pos_if_init( (int)t.second ) == 0 ){
                 switch( var_strict_level() ){
                        case 1:
                            cout<<"Warning: uninitialized variable "
                            "detected! zeroed it by default!"<<endl;
                            break;
                        case 2:
                            throw no_such_var();
                        default:;
                }
            }
            return var_at_pos( (int)t.second );
            }
            else
                    throw no_such_var();
            break;
        }
        case ( _number_type ):return t.second;
        case ( _func_type ):
        {
            int x = t.second;
            double xin = primary();
            return tkin.function().get_result(x,xin);
        }
        case ( _brk_type ):
        {
            double d = statement();
            token_type tail = tkin.get_token();
            if ( tail.first == _brk_type ){
                switch( (int)(t.second) ){
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
        default : throw grammar_error();
    }

}


#endif
#define GRAMMER
