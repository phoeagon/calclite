#include <iostream>
using namespace std;

#include "calc.h"
#include "token_stream_class.h"


#include "grammer.h"
#include "var_support.h"

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
    catch(modulus_error){
        cout<<"modulus operations works on integers only!";
    }
    catch(...){
        cout<<"input error!"<<endl;
    }
}

