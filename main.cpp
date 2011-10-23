#include <iostream>
using namespace std;

#include "calc.h"
#include "interact.h"

#include "var_support.h"

#include "token_stream_class.h"

#include "grammer.h"

int main(){
    //tkin = new token_stream();
    print_welcome();

    grammar instance;
    instance.tkin.var_data.init_system_var();

    instance.set_debug(0);
    instance.set_warning(1);
    instance.tkin.set_debug(0);

    while (1){
        try{
                cout << instance.run()<<endl;
        }
        catch(init_error){
            cout<<"system initialization error!"<<endl;
            cout<<"some parts may not work, use '#' to exit."<<endl;
        }
        catch(assign_error){
            cout<<"assignment statement must have a variable as left value"<<endl;
        }
        catch(exp_undef){
            cout<<"exponential or power in given calculation undefined"<<endl;
        }
        catch(help_info){
            print_help();
        }
        catch(user_exit){
            //terminated by user
            return 0;
        }
        catch(var_def_ok){
            //everything's fine but we print promt that a new different message
        }
        catch(divide_zero){
            cout<<"divided/mod by zero!"<<endl;
        }
        catch(modulus_error){
            cout<<"modulus operations works on integers only!"<<endl;
        }
        catch(no_such_var){
            cout<<"no defined var found!"<<endl;
        }
        catch(fact_error){
            cout<<"n! requires n to be positive integer"<<endl;
        }
        catch(...){
            cout<<"input error!"<<endl;
        }
            empty_cin_buffer();
    }
}

