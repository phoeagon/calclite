/**
    this is the core header

    shift_opr uses the unused bit (first bit) in a char to mark special operators.

*/

#ifndef CALC
/** core header */

#include <utility>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <string>
#include <cerrno>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cmath>
using namespace std;

const string app_name = "CalcLight";

typedef pair<int,double> token_type;

static const double _m_pi = 3.14159265358979323f;
static const double _m_e  = 2.718281828459045f;
static const double _m_phi= 1.618033988749895f;

static const int _var_init_size = 10;

static const int _number_type = 0;
static const int _var_type = 1;
static const int _opr_type = 2;
static const int _func_type = 3;
static const int _brk_type = 4; //bracket
static const int _cmd_type = 5;
static const int _assign_type = 6;

void    init_random(){/** initiate random seed */
	srand(time(NULL));
}

typedef vector<token_type> stream_content_type ;
typedef stream_content_type :: iterator  stream_content_type_iter;

void    empty_cin_buffer(){/** clear the std::cin line */
	cin.clear();
	int x;
	while ( x = cin.get() )
		if ( x == 10 || x == 13 )break;
}

int     cin_eol(){  /** check if std::cin at End of Line*/
    int x = cin.peek();
    return ( x==10 || x==13 );
}
void    find_next_element   ( int value )
{
	int x;
	while ( cin ){
	    if ( !value && cin_eol() )return;
        x = cin.get();
        //if(x==10 || x==13)return;
		if ( isspace( x ) == value ){
			cin.putback( x );
			return ;
		}
	}
}
void    jump_to_space(){    /** go to next space */
    find_next_element( 1 );
}
void    dispose_space(){    /** go until no more space*/
    find_next_element( 0 );
}

/** error classes */
class   exp_undef{};
class   bad_input{};
class    divide_zero{};
class   grammar_error{};
class   no_such_pos{};
class   modulus_error{};
class   no_such_var{};
class   duplicate_def{};
class   var_def_ok{};
class   user_exit{};
class   help_info{};
class   assign_error{};
class   init_error{};
class   fact_error{};
class   bitwise_int{};
class   null_statement{};

/** precision */
static  const double pres = 1e-10;

int     equal ( double a , double b ){
    /** check if two values equal, with tolerance */
    return ( abs( a - b ) < 1e-7 );
}

int     iswhole ( double a ){
    /** check if a value is integral */
    return ( abs( a - round (a) )< 1e-7 );
}
int     isnan ( double a ){
    /** check if #nan is given */
    /** it's provided in math.h but not cmath */
    return a != a;
}

double permutation(int n, int k)/**calculate p(n,k)*/
{   if (n<k)return 0;
	double r = 1, d = n - k;
	/** choose the smaller of k and n - k */
	if (d > k) { k = d; d = n - k; }

	while (n > k)
		r *= n--;
	return r;
}
double binomial(int n, int k)/**calculate c(n,k)*/
{   if (n<k)return 0;
	double r = 1, d = n - k;
	/** choose the smaller of k and n - k */
	if (d > k) { k = d; d = n - k; }

	while (n > k) {
		r *= n--;
		/* divide (n - k)! as soon as we can to delay overflows */
		while (d > 1 ) r /= d--;
	}
	return r;
}

#undef shiftopr(x)
#define shift_opr(x) ((x)^128)
int     force_int( double x ){
    if ( iswhole( x ))
        return (int)x;
    else throw bitwise_int();
}
int gcd(int a,int b){
    if (!b)return a;
    return gcd(b,a%b);
}
double lcm(int a,int b){
    return a/gcd(a,b)*(double)b;
}

/** end of core header */
#endif



#define CALC
