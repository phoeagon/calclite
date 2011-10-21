#include <iostream>
using namespace std;

#include "calc.h"
#include "token_stream_class.h"


#include "grammer.h"

int main(){
    //tkin = new token_stream();
    grammar instance;
    instance.debug = 0;
    instance.tkin.debug = 0;
    try{
            cout << instance.run()<<endl;
    }
    catch(divide_zero){
        cout<<"divided by zero!"<<endl;
    }
    catch(...){
        cout<<"input error!"<<endl;
    }
}

