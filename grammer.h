class grammar{
    public:
        double expression(int l,int r);
        double term(int l,int r);
        double primary(int l,int r);
        double get_result();
        token_stream tkin;
    private:
        int opr_right_pos(int l,int r,char* pattern);
        int opr_left_pos(int l,int r,char* pattern);
};
double grammar :: get_result(){
    return expression(0,tkin.data().size()-1);
}
double grammar :: expression(int l,int r){
    if (l>r)throw grammar_error();
    try{
        int q = opr_right_pos(l,r,"+-");
        char tmp = tkin.data()[q].second;
        switch(tmp){
            case '+':
                return expression(l,q-1)+term(q+1,r);
            case '-':
                return expression(l,q-1)-term(q+1,r);
            default : throw grammar_error();
        }
    }catch(...){
        return term(l,r);
    }
}
double grammar :: term(int l,int r){
    if (l>r)throw grammar_error();

    try{
        int q = opr_right_pos(l,r,"*/%");

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
    }catch(...){
        return primary(l,r);
    }
}
double grammar :: primary(int l,int r){
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
        return expression(l+1,r+1);
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
    int j;
    int ct = strlen(pattern);

    while (r>=l){
        for (j=0;j<ct;++j)
            if (tkin.data()[l].first==_opr_type &&
                (char)(tkin.data()[l].second)==pattern[j])
            return l;
        ++l;
    }
    throw grammar_error();
}
int grammar :: opr_right_pos(int l,int r,char* pattern){
    int j;
    int ct = strlen(pattern);

    while (r>=l){
        for (j=0;j<ct;++j)
            if (tkin.data()[r].first==_opr_type &&
                (char)(tkin.data()[r].second)==pattern[j])
            return r;
        --r;
    }
    throw grammar_error();

}
