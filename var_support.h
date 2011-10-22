typedef vector<double> memory_table;
typedef map<string,int> var_cast;
typedef var_cast :: iterator var_cast_it;
typedef vector<bool> memory_init_table;

class variables{
    public:
        var_cast        var_table;
        memory_table    memory;
        memory_init_table memory_init;

        double get_var_pos(string a);
        int add_var(string,double);
        void del_var(string);
        int eval_var(string ind , double val);
        const string cin_get_var_name();
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
void variables :: del_var(string ind){
    var_cast_it pos = var_table.find(ind);
    if (pos==var_table.end())
        throw no_such_var();
    else var_table.erase(pos);
    // note that the actual content in memory is not released
    // so as to save time
}
int variables :: eval_var(string ind , double val){
    var_cast_it pos = var_table.find(ind);
    if (pos==var_table.end())
        throw no_such_var();
    memory.at((*pos).second) = val;
    return (*pos).second;
}
const string variables :: cin_get_var_name(){
    string value ;
    char x = 0;
    if (isalpha(cin.peek())){
        while(cin){
            if (!(cin>>x))throw bad_input();
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
