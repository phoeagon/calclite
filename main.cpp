#include <iostream>
using namespace std;

#include "calc.h"

#include "var_support.h"

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
    catch(var_def_ok){
        //everything's fine but we print promt that a new different message
    }
    catch(divide_zero){
        cout<<"divided by zero!"<<endl;
    }
    catch(modulus_error){
        cout<<"modulus operations works on integers only!"<<endl;
    }
    catch(no_such_var){
        cout<<"no defined var found!"<<endl;
    }
    catch(...){
        cout<<"input error!"<<endl;
    }
}

