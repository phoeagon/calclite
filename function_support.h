static const int _func_sin = 0;
static const int _func_cos = 1;
static const int _func_tan = 2;
static const int _func_cot = 3;
static const int _func_sec = 4;
static const int _func_csc = 5;
static const int _func_exp = 6;
static const int _func_ln = 7;
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

typedef map<string,int> function_cast;
typedef function_cast::iterator function_cast_it;

class functions{
    public:
        void    init_system_func();
        function_cast_it    isfunction( string s );
        void    add_function( string s );
        double  get_result(int opr,double x);
    protected:
        function_cast df;
        int x;
};

function_cast_it   functions ::    isfunction( string s ){
    return df.find(s) ;
}
void    functions :: add_function(string s){
    df[s] = 1;
}
void    functions ::    init_system_func(){
    add_function("sin");
    add_function("cos");
    add_function("tan");
    add_function("cot");
    add_function("sec");
    add_function("csc");
    add_function("asin");
    add_function("acos");
    add_function("atan");
    add_function("ln");
    add_function("exp");
    add_function("rand");
    add_function("log2");
    add_function("srand");
    add_function("sinh");
    add_function("cosh");
    add_function("tanh");
    add_function("rtod");
    add_function("dtor");
    add_function("floor");
    add_function("ceil");
}
//std::transform(ttt.begin(),ttt.end(),x);

const double _pi = 3.14159265358979;
double  functions :: get_result(int opr,double x){
    switch(opr){
        case _func_sin :	return  sin(x);
        case _func_cos :	return  cos(x);
        case _func_tan :	return  tan(x);
        case _func_cot :	return  1/tan(x);
        case _func_sec :	return  1/cos(x);
        case _func_csc :	return  1/sin(x);
        case _func_exp :	return  exp(x);
        case _func_ln :	    return  log(x);
        case _func_log2 :	return  log(x)/log(2);
        case _func_log10 :	return  log(x)/log(10);
        case _func_rand :	return  rand()%((int)x);
        case _func_dtor :	return  x*_pi/180;
        case _func_rtod :	return  x*180/_pi;
        case _func_sqrt :	return  sqrt(x);
        case _func_floor :	return  floor(x);
        case _func_ceil :	return  ceil(x);
        case _func_sinh :	return  sinh(x);
        case _func_cosh :	return  cosh(x);
        case _func_tanh :	return  tanh(x);
        default:break;
    }
}
