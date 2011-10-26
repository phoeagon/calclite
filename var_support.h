/**
    this header file implements variable support
*/

#ifndef VAR_SUPPORT

typedef vector<double> memory_table;
typedef map<string,int> var_cast;
typedef var_cast :: iterator var_cast_it;
typedef vector<char> memory_init_table;

class   variables{
    public:
        void    init_system_var(int);
        void    reset_var();
        void    reset_system_var();
        /** memory things */
        var_cast           var_table;
        memory_table       memory;
        memory_init_table    memory_init;

        double  get_var_pos(string a);/**get where is variable [a] stored in memory*/
        int     add_var(string,double);/** add a variable */
        int     add_var(string,double,int);
        void    del_var(string);
        double  eval_var(string ind , double val);/**evaluate a variable by name*/


        /** constructor */
        variables(){
            init_system_var(1);
            memory.reserve(_var_init_size);
            memory_init.reserve(_var_init_size);
        };
    private:
        void    reset_all();
};

double  variables ::    get_var_pos(string a){/**get where var [a] is stored in memory*/
    var_cast_it it ;
    it = var_table.find(a);
    if (it!=var_table.end())return (*it).second;
        else throw no_such_var();
}
int    variables ::     add_var(string ind , double val){/** add variable*/
    if (var_table.find(ind)!=var_table.end())
        throw duplicate_def();

    memory.push_back(val);
    memory_init.push_back(0);
    return (var_table[ind] = memory.size()-1);
}
int     variables ::    add_var
        (string ind , double val , int quiet)
{
    try{
        return add_var(ind,val);
    }catch(duplicate_def){
        if (quiet){
            eval_var(ind,val);
            return get_var_pos(ind);
        }
        else throw duplicate_def();
    }
}
void variables :: del_var ( string ind )
{
    var_cast_it pos = var_table.find(ind);
    if ( pos == var_table.end() )
        throw no_such_var();
    else    var_table.erase(pos);
    /** note that the actual content in memory is not released
    * so as to save time
    */
}
double variables :: eval_var(string ind , double val){/**evaluate variable by name*/
    var_cast_it pos = var_table.find(ind);
    if (pos==var_table.end())
        throw no_such_var();
    return memory.at((*pos).second) = val;
}


void variables :: init_system_var   (int quiet = 0){
    try{
        memory_init[add_var("_debug",0,quiet)] = 0;
        memory_init[add_var("_var_strict",1,quiet)] = 0;
        memory_init[add_var("_precision",8,quiet)] = 0;
        memory_init[add_var("_type_strict",1,quiet)] = 0;

        memory_init[add_var("_e",_m_e,quiet)] = 1;
        memory_init[add_var("_pi",_m_pi,quiet)] = 1;
        memory_init[add_var("_phi", _m_phi,quiet)] = 1;
    }catch(duplicate_def){
        throw init_error();
    }
}
void variables ::   reset_all(){
    memory.     clear();
    memory_init.clear();
    var_table.  clear();
}
void variables ::   reset_var(){
    reset_all();
    init_system_var();
}

#endif
#define VAR_SUPPORT
