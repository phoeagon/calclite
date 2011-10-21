class grammar{
    public:
        double expression(int l,int r);
        double term(int l,int r);
        double primary(int l,int r);
        double run();
        token_stream tkin;
        int debug;
    private:
        int opr_right_pos(int l,int r,char* pattern);
        int opr_left_pos(int l,int r,char* pattern);
};
double grammar :: run(){
    tkin.init();
    return expression(0,tkin.data().size()-1);
}
double grammar :: expression(int l,int r){
    if (debug)cout<<"expression:"<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();
    try{
        int q = opr_right_pos(l+1,r,"+-");
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
    if (debug)cout<<"term:"<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();

    try{
        int q = opr_right_pos(l+1,r,"*/%");

        char tmp = tkin.data()[q].second;

        if (tmp=='*')return term(l,q-1)*primary(q+1,r);
        else if (tmp=='/'){
            double divisor = primary(q+1,r);
            if (equal(0.0,divisor))throw divide_zero();
            return term(l,q-1)/divisor;
        }
        else if (tmp=='%'){
            //to do here
            return 0;
        }
    }catch(no_such_pos){
        return primary(l,r);
    }
}
double grammar :: primary(int l,int r){
    if (debug)cout<<"primary:"<<l<<" "<<r<<endl;
    if (l>r)throw grammar_error();

    token_type head = tkin.data()[l];
    token_type tail = tkin.data()[r];

    if (head.first==_number_type){
        if (l!=r)
            throw grammar_error();

        return head.second;
    }
    else if(head.first==_brk_type && tail.first==_brk_type){
        if (r-l-1<=0)throw grammar_error();
        if ((int)(head.second)!='('||(int)(tail.second)!=')')
            throw grammar_error();
        return expression(l+1,r-1);
    }
    else if(head.first==_opr_type){
        switch((int)(head.second)){
            case '+':return primary(l+1,r);
            case '-':return -primary(l+1,r);
            default :throw grammar_error();
        }
    }
    else throw grammar_error();
}




/*
 some functions
*/
int grammar :: opr_left_pos(int l,int r, char* pattern){
   /* int j;
    int ct = strlen(pattern);

    while (r>=l){
        for (j=0;j<ct;++j)
            if (tkin.data()[l].first==_opr_type &&
                (char)(tkin.data()[l].second)==pattern[j])
            return l;
        ++l;
    }
    throw grammar_error();*/
}
int grammar :: opr_right_pos(int l,int r,char* pattern){
    if (l>r)throw no_such_pos();
    int brk_dep = 0;
    int j;
    int ct = strlen(pattern);

    while (r>=l){
        for (j=0;j<ct;++j){
            token_type tmp = tkin.data()[r];
            if (tmp.first==_brk_type){
                if (tmp.second==')')++brk_dep;
                else //if (tmp.second=='(')
                    --brk_dep;
            }
            if (!brk_dep && tmp.first==_opr_type &&
                (char)(tmp.second)==pattern[j])
            return r;
        }
        --r;
    }
    throw no_such_pos();

}
