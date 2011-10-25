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
static const int _func_asin = 19;
static const int _func_acos = 20;
static const int _func_atan = 21;

typedef map<string,int> function_cast;
typedef function_cast::iterator function_cast_it;

class functions{
    public:
        void    init_system_func();
        function_cast_it    isfunction( string s );
        void    add_function( string s ,int x);
        double  get_result(int opr,double x);
        function_cast_it    end_of_list(){return df.end();}
    protected:
        function_cast df;
        int x;
};

function_cast_it   functions ::    isfunction( string s ){
    return df.find(s) ;
}
void    functions :: add_function(string s,int x){
    df[s] = x;
}
void    functions ::    init_system_func(){
    #define add_func(x)\
        add_function("x",_func_##x);
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
