
string storage;

void pre_read(){
    getline(cin,storage);
    storage += '\n';
}
int replace_str(string &storage,const string pattern, const string new_pattern){
    int times = 0;
    size_t pos;
    while ( (pos = storage.find(pattern))!=string::npos){
        storage.replace(pos,pattern.size(),new_pattern.c_str());
        ++times;
    }
    return times;
}
void pre_push(){
    int i = storage.size();
    while (i--)
        cin.putback(storage[i]);//,cerr<<(int)storage[i]<<' ';
        //cerr<<endl;
}
int pre_proc(){
    pre_read();
    //char ll = 13;
    //replace_str(storage," ","");
    replace_str(storage,";;",";");
    //replace_str(storage,";\n","\n");
    int x = replace_str(storage,";","\n\n")+1;
    replace_str(storage,"\n\n\n","\n\n");//fixes ';' at EOL
    replace_str(storage,">=",""+shift_opr('>'));
    replace_str(storage,"<=",""+shift_opr('<'));
    pre_push();
    //cerr<<storage<<endl;
    return x;
}

