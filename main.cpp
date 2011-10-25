#include <iostream>
using namespace std;

#include "calc.h"
#include "interact.h"
#include "preprocessor.h"
#include "var_support.h"

#include "token_stream_class.h"

#include "grammer.h"

int main(){
    //cout<<">"<<endl;
    //pre_proc();
    //tkin = new token_stream();
    print_welcome();

    grammar instance;
    instance.tkin.var_data.init_system_var();

    instance.set_debug(0);
    instance.set_warning(1);
    //instance.tkin.set_debug(1);
    while (1){
        cout<<"> "<<flush;int x = pre_proc();//cerr<<x<<endl;
        //char t;
        //while (cin){t = cin.get();cerr<<(int)t<<' ';}
    while (x--){
        try{
                int x = instance.tkin.var_data.get_var_pos("_precision");
                x = instance.tkin.var_data.memory[x];
                //cout<<"> "<<flush;
                cout << setprecision(x);
                double ans = instance.run();

                if (instance.tkin.l2r_pos!=instance.tkin.data().size())throw grammar_error();

                cout<<ans<<endl;
        }
        catch(init_error){
            cout<<"system initialization error!"<<endl;
            cout<<"some parts may not work, use '#' to exit."<<endl;
        }
        catch(assign_error){
            cout<<"assignment statement must have a variable as left value"<<endl;
        }
        catch(null_statement){}
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
        catch(bitwise_int){
            cout<<" some operators (modulus, bitwise, etc) support integer values only!"<<endl;
        }
        catch(...){
            cout<<"input error!"<<endl;
        }
            empty_cin_buffer();
    }
    }
}

