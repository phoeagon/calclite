#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cmath>

typedef struct{
	int _type,value;
} token_type;

static const int _number_type = 0;
static const int _var_type = 1;
static const int _opr_type = 2;

void init_random(){
	srand(time(NULL));
}


