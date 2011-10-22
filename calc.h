#include <utility>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <string>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cmath>
using namespace std;


//	int _type,value;
typedef pair<int,double> token_type;

static const int _number_type = 0;
static const int _var_type = 1;
static const int _opr_type = 2;
static const int _func_type = 3;
static const int _brk_type = 4; //bracket
static const int _cmd_type = 5;
static const int _assign_type = 6;

void init_random(){
	srand(time(NULL));
}

typedef vector<token_type> stream_content_type ;
typedef stream_content_type :: iterator  stream_content_type_iter;

void empty_cin_buffer(){
	cin.clear();
	char x;
	while (x=cin.get())
		if (x==10 || x==13)break;
}

int cin_eol(){
    char x = cin.peek();
    return (x==10 || x==13);
}
void find_next_element(int value){
	char x;
	if (cin_eol())return;
	while (cin){
        x=cin.get();
		if (isspace(x)==value){
			cin.putback(x);
			return ;
		}
	}
}
void jump_to_space(){
    find_next_element(1);
}
void dispose_space(){
    find_next_element(0);
}

class bad_input{};
class divide_zero{};
class grammar_error{};
class no_such_pos{};
class modulus_error{};
class no_such_var{};
class duplicate_def{};
class var_def_ok{};
class user_exit{};
class help_info{};
class assign_error{};
class init_error{};

static const double pres = 1e-7;

int equal(double a,double b){
    return (abs(a-b)<1e-7);
}

int iswhole(double a){
    return (abs(a-(int)a)<1e-7);
}
