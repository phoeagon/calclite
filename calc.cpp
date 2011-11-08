#include "calc.h"

void    init_random() /** initiate random seed */
{
    srand(time(NULL));
}
void    empty_cin_buffer() /** clear the std::cin line */
{
    cin.clear();
    int x;
    while ( x = cin.get() )
        if ( x == 10 || x == 13 )break;
}
int     cin_eol()   /** check if std::cin at End of Line*/
{
    int x = cin.peek();
    return ( x==10 || x==13 );
}
void   find_next_element   ( int value )
{
    int x;
    while ( cin )
    {
        if ( !value && cin_eol() )return;
        x = cin.get();
        //if(x==10 || x==13)return;
        if ( isspace( x ) == value )
        {
            cin.putback( x );
            return ;
        }
    }
}
void    jump_to_space()     /** go to next space */
{
    find_next_element( 1 );
}
void    dispose_space()     /** go until no more space*/
{
    //int v =
    find_next_element( 0 );
    //if (v==10 || v==13)cin.putback(v);
}
int     equal ( double a , double b )
{
    /** check if two values equal, with tolerance */
    return ( abs( a - b ) < 1e-7 );
}
int     iswhole ( double a )
{
    /** check if a value is integral */
    return ( abs( a - round (a) )< 1e-7 );
}
int     isnan ( double a )
{
    /** check if #nan is given */
    /** it's provided in math.h but not cmath */
    return a != a;
}
double permutation(int n, int k)/**calculate p(n,k)*/
{
    if (n<k)return 0;
    double r = 1, d = n - k;
    /** choose the smaller of k and n - k */
    if (d > k)
    {
        k = d;
        d = n - k;
    }

    while (n > k)
        r *= n--;
    return r;
}
double binomial(int n, int k)/**calculate c(n,k)*/
{
    if (n<k)return 0;
    double r = 1, d = n - k;
    /** choose the smaller of k and n - k */
    if (d > k)
    {
        k = d;
        d = n - k;
    }

    while (n > k)
    {
        r *= n--;
        /* divide (n - k)! as soon as we can to delay overflows */
        while (d > 1 ) r /= d--;
    }
    return r;
}

int     force_int( double x )
{
    if ( iswhole( x ))
        return (int)x;
    else throw bitwise_int();
}
int gcd(int a,int b)
{
    if (!b)return a;
    return gcd(b,a%b);
}
double lcm(int a,int b)
{
    return a/gcd(a,b)*(double)b;
}

