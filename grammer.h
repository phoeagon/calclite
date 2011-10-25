class grammar{
    public:

        token_stream tkin;
        void set_debug(int x){tkin.var_data.memory[tkin.var_data.get_var_pos("_debug")]=x;}
        void set_warning(int x){tkin.var_data.memory[tkin.var_data.get_var_pos("_warning")]=x;}
        double run();
    private:
		int debug(){return tkin.var_data.memory[tkin.var_data.get_var_pos("_debug")];} ;
        int warning(){return tkin.var_data.memory[tkin.var_data.get_var_pos("_warning")];} ;

        double statement();
        double boolean_expression();
        double compare_expression();
        double expression();
        double term();
        double unary_plus();
        double exp_and_pow();
        double factorial();
        double primary();
};
double grammar :: statement(){
    if (debug())cerr<<"statement: "<<endl;

    token_type lvalue = tkin.get_token();
    if (lvalue.first != _var_type){tkin.putback();return boolean_expression();}

    token_type data = tkin.get_token();
    if (data.first!=_assign_type){tkin.putback();tkin.putback();return boolean_expression();}

    while(1){
        switch((int)data.second){
            case '=':{
                    double x = statement();
                    tkin.var_data.memory_init[lvalue.second] = 1;
                    return tkin.var_data.memory[lvalue.second] = x;
            }
            default:throw grammar_error();
        }
    }
}
double grammar :: run(){
    tkin.init();


    if (tkin.data().size()==1 &&
        tkin.data()[0].first==_cmd_type){
            int flag = (tkin.data()[0].second);
            if (flag=='#')
                throw user_exit();
            else if (flag=='?')
                throw help_info();
            else throw bad_input();
        }
    if (tkin.data().size()==0)throw null_statement();

    return statement();
}
double grammar :: boolean_expression(){
    //left associativity
    if (debug())cerr<<"boolean_expression:"<<tkin.l2r_pos<<endl;

    double left = compare_expression();
    token_type t = tkin.get_token();
    while(1){
        switch((int)t.second){
            case '&':
                left = (int)left & force_int(compare_expression());
                t = tkin.get_token();break;
            case '|':
                left = (int)left &force_int(compare_expression());
                t = tkin.get_token();break;
            case shift_opr('^'):
                left = (int)left ^ force_int(compare_expression());
                t = tkin.get_token();break;
            default:tkin.putback();return left;
        }
    }
}
double grammar :: compare_expression(){//left associates
    if (debug())cerr<<"compare_expression:"<<tkin.l2r_pos<<endl;
    double left = expression();
    token_type t = tkin.get_token();
    while(1){
        switch((int)t.second){
            case '>':   left = left>expression();t = tkin.get_token();break;
            case '<':   left = left<expression();t = tkin.get_token();break;
            case shift_opr('>'):   left = left>=expression();t = tkin.get_token();break;
            case shift_opr('<'):   left = left<=expression();t = tkin.get_token();break;
            case shift_opr('='):   left = (left==expression());t= tkin.get_token();break;
            default:    tkin.putback();return left;
        }
    }
}
double grammar :: expression(){
    if (debug())cerr<<"expression:"<<tkin.l2r_pos<<endl;
    double left = term();
    token_type data = tkin.get_token();
    while(1){
        switch((int)data.second){
            case '+':
                left+=term();data=tkin.get_token();break;
            case '-':
                left-=term();data=tkin.get_token();break;
            default:
                tkin.putback(); return left;
        }
    }
}
double grammar :: term(){
    if (debug())cerr<<"term:"<<tkin.l2r_pos<<endl;
    double left = unary_plus();
    token_type data = tkin.get_token();
    while(1){
        switch((int)data.second){
            case '*':left *= unary_plus();data = tkin.get_token();break;
            case '/':
            {
                double dvsr = unary_plus();
                if (equal(dvsr,0)){throw divide_zero();}
                left /= unary_plus();
                data = tkin.get_token();
                break;
            }
            case '%':{
                int val1 = force_int(left);
                int val2 = force_int(unary_plus());
                if (val2==0)throw divide_zero();
                left = val1 % val2;
                data = tkin.get_token();
                break;
            }
            default :tkin.putback();
                return left;
        }
    }
}
double grammar :: unary_plus(){
    //right associate
    if (debug())cerr<<"unary_plus()"<<tkin.l2r_pos<<endl;
    token_type t = tkin.get_token();
    if (t.first==_opr_type){
        switch((int)(t.second)){
            case '+':return unary_plus();
            case '-':return -unary_plus();
            case '@':return ~force_int(unary_plus());
            case '~':return !force_int(unary_plus());
            default :;
        }
    }
    tkin.putback();
    return exp_and_pow();
}
double grammar :: exp_and_pow(){
    //right associate
    if (debug())cerr<<"exp_and_pow:"<<tkin.l2r_pos<<endl;

    double left = factorial();
    token_type t = tkin.get_token();
    switch((int)t.second){
        case '^':
            {double v2 = exp_and_pow();
            left = pow(left,v2);
            if (errno)errno = 0 , throw exp_undef();
            return left;
            }
        default : tkin.putback();return left;
    }
}
double grammar :: factorial(){
    //left associative operations with high priority "!"
    //also, it involves single value
    if (debug())cerr<<"factorial:"<<tkin.l2r_pos<<endl;
    double left = primary();
    token_type t = tkin.get_token();
    while (1){
        switch((int)t.second){
            case '!':{
                int x =force_int(left);
                int f = 1;
                while (x>0)f*=x--;
                left = f;
                t = tkin.get_token();
                    break;
            }
            default : tkin.putback();return left;
        }
    }
}
double grammar :: primary(){
    if (debug())cerr<<"primary "<<tkin.l2r_pos<<endl;
    token_type t = tkin.get_token();
    switch((int)t.first){
        case(_var_type):
            if (debug()){
                cerr<<"memory size:"<<tkin.var_data.memory.size()<<endl;
                cerr<<"at memory: "<<t.second<<endl;
            }
            if(t.second<tkin.var_data.memory.size()){
            if (warning() && tkin.var_data.memory_init[(int)t.second]==0)
                    cout<<"Warning: uninitialized variable detected! zeroed it by default!"<<endl;
                return tkin.var_data.memory.at((int)t.second);
            }
            else throw no_such_var();
            break;
        case (_number_type):return t.second;
        case (_brk_type):{
            double d = statement();
            token_type tail = tkin.get_token();
            if (tail.first==_brk_type){
                switch((int)(t.second)){
                    case '(':if ((int)(tail.second)!=')')throw grammar_error();else return d;
                    case '[':if ((int)(tail.second)!=']')throw grammar_error();else return abs(d);
                    default: throw grammar_error();
                }
            }
            else throw grammar_error();
        }

    }

}




/*
 some functions
*/

