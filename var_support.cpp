#include "var_support.h"

double  variables ::    get_var_pos(string a) /**get where var [a] is stored in memory*/
{
    var_cast_it it ;
    it = var_table.find(a);
    if (it!=var_table.end())return (*it).second;
    else throw no_such_var();
}
int    variables ::     add_var(string ind , double val) /** add variable*/
{
    if (var_table.find(ind)!=var_table.end())
        throw duplicate_def();

    memory.push_back(val);
    memory_init.push_back(0);
    return (var_table[ind] = memory.size()-1);
}
int     variables ::    add_var
(string ind , double val , int quiet)
{
    try
    {
        return add_var(ind,val);
    }
    catch(duplicate_def)
    {
        if (quiet)
        {
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
double variables :: eval_var(string ind , double val) /**evaluate variable by name*/
{
    var_cast_it pos = var_table.find(ind);
    if (pos==var_table.end())
        throw no_such_var();
    return memory.at((*pos).second) = val;
}

void variables :: init_system_var   ()
{
    init_system_var(0);
}
void variables :: init_system_var   (int quiet)
{
    try
    {
        memory_init[add_var("_debug",0,quiet)] = 0;
        memory_init[add_var("_var_strict",1,quiet)] = 0;
        memory_init[add_var("_precision",8,quiet)] = 0;
        memory_init[add_var("_type_strict",1,quiet)] = 0;

        memory_init[add_var("_e",_m_e,quiet)] = 1;
        memory_init[add_var("_pi",_m_pi,quiet)] = 1;
        memory_init[add_var("_phi", _m_phi,quiet)] = 1;
    }
    catch(duplicate_def)
    {
        throw init_error();
    }
}
void variables ::   reset_all()
{
    memory.     clear();
    memory_init.clear();
    var_table.  clear();
}
void variables ::   reset_var()
{
    reset_all();
    init_system_var();
}

