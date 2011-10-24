typedef vector<double> memory_table;
typedef map<string,int> var_cast;
typedef var_cast :: iterator var_cast_it;
typedef vector<bool> memory_init_table;

class variables{
    friend class token_stream;
    public:
        var_cast        var_table;
        memory_table    memory;
        memory_init_table memory_init;

        double get_var_pos(string a);
        int add_var(string,double);
        int add_var(string,double,int);
        void del_var(string);
        double eval_var(string ind , double val);
        const string cin_get_var_name();
        void init_system_var(int);
        void reset_var();
        void reset_system_var();
    private:
             void reset_all();
};

double variables::get_var_pos(string a){
    var_cast_it it ;
    it = var_table.find(a);
    if (it!=var_table.end())return (*it).second;
        else throw no_such_var();
}
int variables :: add_var(string ind , double val){
    if (var_table.find(ind)!=var_table.end())
        throw duplicate_def();

    memory.push_back(val);
    memory_init.push_back(0);
    return var_table[ind] = memory.size()-1;
}
int variables :: add_var(string ind , double val , int quiet){
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
void variables :: del_var(string ind){
    var_cast_it pos = var_table.find(ind);
    if (pos==var_table.end())
        throw no_such_var();
    else var_table.erase(pos);
    // note that the actual content in memory is not released
    // so as to save time
}
double variables :: eval_var(string ind , double val){
    var_cast_it pos = var_table.find(ind);
    if (pos==var_table.end())
        throw no_such_var();
    return memory.at((*pos).second) = val;
}
const string variables :: cin_get_var_name(){
    string value ;
    char x = cin.peek();
    if (isalpha(x) || x=='_' ){
        while(cin){
            dispose_space();
            x=cin.get();
            if (isdigit(x) || isalpha(x) || x=='_')
                value += x;
            else {
                cin.putback(x);
                break;
            }
        }
    }
    if (value.size())
        return value;
    else throw bad_input();
}

void variables :: init_system_var(int quiet = 0){
    try{
        memory_init[add_var("_debug",0,quiet)]=0;
        memory_init[add_var("_warning",1,quiet)]=0;
        memory_init[add_var("_precision",0,quiet)]=0;

        memory_init[add_var("_e",2.718281828459045f,quiet)]=1;
        memory_init[add_var("_pi",3.14159265358979323f,quiet)]=1;
        memory_init[add_var("_phi", 1.618033988749895f,quiet)]=1;
    }catch(duplicate_def){
        throw init_error();
    }
}
void variables :: reset_all(){
    memory.clear();
    memory_init.clear();
    var_table.clear();
}
void variables :: reset_var(){
    reset_all();
    init_system_var();
}

