double expression(int l,int r);
double term(int l,int r);
double primary(int l,int r);

double expression(int l,int r){

}
double term(int l,int r){
    if (l>r)throw grammar_error();

    int q = r;
    int tmp ;
    while (q>=0){
        tmp = (int)(tkin.data()[q].second);
        if (tmp=='*' || tmp=='/')break;
    }
    if (q<0)throw grammar_error();

    if (tmp=='*')return term(l,q-1)*primary(q+1,r);
    else if (tmp=='/'){
        double divisor = primary(q+1,r);
        if (equal(0.0,divisor))throw divide_zero();
        return term(l,q-1)/divisor;
    }
    else if (tmp=='%'){
        //to do here
    }
    return primary(l,r);

}
double primary(int l,int r){
    if (l>r)throw grammar_error();

    token_type head = tkin.data()[l];
    token_type tail = tkin.data()[r];

    if (head.first==_number_type){
        if (l!=r)
            throw grammar_error();

        return head.second;
    }
    else if(tmp.first==_brk_type){
        if (r-l-1<=0)throw grammar_error();
        if ((int)(head.second)!='('||(int)(tail.second)!=')')
            throw grammar_error();
        return expression(l+1,r+1);
    }
    else if(tmp.first==_opr_type){
        switch((int)(tmp.second)){
            case '+':return primary(l+1,r);
            case '-':return -primary(l+1,r);
            default :throw grammar_error();
        }
    }
    else throw grammar_error();
}
