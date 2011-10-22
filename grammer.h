class grammar{
    public:

        token_stream tkin;
        void set_debug(int x){tkin.var_data.memory[tkin.var_data.get_var_pos("_debug")]=x;}
        void set_warning(int x){tkin.var_data.memory[tkin.var_data.get_var_pos("_warning")]=x;}
        double run();
    private:
		int debug(){return tkin.var_data.memory[tkin.var_data.get_var_pos("_debug")];} ;
        int warning(){return tkin.var_data.memory[tkin.var_data.get_var_pos("_warning")];} ;

        double statement(int l,int r);
        double expression(int l,int r);
        double term(int l,int r);
        double fact(int l,int r);
        double fact2(int l,int r);
        double high_pri_left_assoc(int l,int r);
        double primary(int l,int r);
        int opr_right_pos(int l,int r,char* pattern);
        int opr_left_pos(int l,int r,char* pattern);
};
double grammar :: statement(int l,int r){
    if (debug())cerr<<"statement: "<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();
    token_type dt = tkin.data()[l+1];
    if (dt.first==_assign_type){
        if (tkin.data()[l].first!=_var_type)throw assign_error();
        int pos = tkin.data()[l].second;

        double rvalue = expression(l+2,r);
        tkin.var_data.memory_init[pos]  = 1;
            //must set after calculation is done
            // just in case that error occur but left value is set to be initlized
        return tkin.var_data.memory[pos] = rvalue;
    }
    return expression(l,r);
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
    return statement(0,tkin.data().size()-1);
}
double grammar :: expression(int l,int r){
    if (debug())cerr<<"expression:"<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();
    try{
        int q = opr_right_pos(l+1,r,"+-");
        //note that "+-" has left associativity
        char tmp = tkin.data()[q].second;
        switch(tmp){
            case '+':
                return expression(l,q-1)+term(q+1,r);
            case '-':
                return expression(l,q-1)-term(q+1,r);
            default : throw grammar_error();
        }
    }catch(no_such_pos){
        return term(l,r);
    }
}
double grammar :: term(int l,int r){
    if (debug())cerr<<"term:"<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();

    try{
        int q = opr_right_pos(l+1,r,"*/%");
        //note that "*/%" has left associativity

        char tmp = tkin.data()[q].second;

        if (tmp=='*')return term(l,q-1)*fact(q+1,r);
        else if (tmp=='/'){
            double divisor = fact(q+1,r);
            if (equal(0.0,divisor))throw divide_zero();
            return term(l,q-1)/divisor;
        }
        else if (tmp=='%'){
            double num2 = fact(q+1,r);
            double num1 = term(l,q-1);
            if (equal(num2,0))throw divide_zero();
            if (iswhole(num1) && iswhole(num2))
                return (int)num1%(int)num2;
            else throw modulus_error();
            return 0;
        }
    }catch(no_such_pos){
        return fact(l,r);
    }
}
double grammar :: fact(int l,int r){
    if (debug())cerr<<"fact:"<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();
    try{
        int q = opr_left_pos(l,r-1,"^");

        //note that power right associates
        double base = fact2(l,q-1);
        double tt = fact(q+1,r);
        return pow(base,tt);
    }catch(no_such_pos){
        return fact2(l,r);
    }
}
double grammar :: fact2(int l,int r){
    //this deals with left associative operations with high priority "!"
    if (debug())cerr<<"fact2:"<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();
    try{
        int pos = opr_right_pos(l+1,r,"!");
        if (pos!=r)throw no_such_pos();

        double base = fact2(l,r-1);
        if (!iswhole(base))throw fact_error();
        int ans = 1;
        for (int i=base;i>1;--i)ans*=i;
        return ans;

    }catch(no_such_pos){
        return primary(l,r);
    }

}
double grammar :: primary(int l,int r){
    if (debug())cerr<<"primary:"<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();

    token_type head = tkin.data()[l];
    token_type tail = tkin.data()[r];

    if(head.first==_var_type){
        if (debug()){
            cerr<<"memory size:"<<tkin.var_data.memory.size()<<endl;
            cerr<<"at memory: "<<head.second<<endl;
        }

        if(head.second<tkin.var_data.memory.size()){
            if (warning() && tkin.var_data.memory_init[(int)head.second]==0)
                cout<<"Warning: uninitialized variable detected! zeroed it by default!"<<endl;
            return tkin.var_data.memory.at((int)head.second);
        }
        else throw no_such_var();
    }
    else if (head.first==_number_type){
        if (l!=r)
            throw grammar_error();

        return head.second;
    }
    else if(head.first==_brk_type && tail.first==_brk_type){
        if (r-l-1<=0)throw grammar_error();
        if ((int)(head.second)=='(' && (int)(tail.second)==')')
            return expression(l+1,r-1);
        else if((int)(head.second)=='|' && (int)(tail.second)=='|')
            return abs(expression(l+1,r-1));
        throw grammar_error();
    }
    else if(head.first==_opr_type){
        switch((int)(head.second)){
            case '+':return primary(l+1,r);
            case '-':return -primary(l+1,r);
            default :break;
        }
        throw grammar_error();
    }
    else throw grammar_error();
}




/*
 some functions
*/
int grammar :: opr_left_pos(int l,int r, char* pattern){
    if (l>r)throw no_such_pos();
    int brk_dep = 0;
    int j;
    int ct = strlen(pattern);
    int abs_dep = 0;

    while (r>=l){
            token_type tmp = tkin.data()[l];
            if (tmp.first==_brk_type){
                if (tmp.second==')')++brk_dep;
                else if (tmp.second=='(')
                    --brk_dep;
                else if (tmp.second=='|')
                    abs_dep = 1-abs_dep;
            }

        for (j=0;j<ct;++j){
            if (!brk_dep && !abs_dep && tmp.first==_opr_type &&
                (char)(tmp.second)==pattern[j])
            return l;
        }
        ++l;
    }
    throw no_such_pos();

}
int grammar :: opr_right_pos(int l,int r,char* pattern){
    if (l>r)throw no_such_pos();
    int brk_dep = 0;
    int j;
    int ct = strlen(pattern);
    int abs_dep = 0;

    while (r>=l){
            token_type tmp = tkin.data()[r];
            if (tmp.first==_brk_type){
                if (tmp.second==')')++brk_dep;
                else if (tmp.second=='(')
                    --brk_dep;
                else if (tmp.second=='|')
                    abs_dep = 1-abs_dep;
            }

        for (j=0;j<ct;++j){
            if (!brk_dep && !abs_dep && tmp.first==_opr_type &&
                (char)(tmp.second)==pattern[j])
            return r;
        }
        --r;
    }
    throw no_such_pos();

}
