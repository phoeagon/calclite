
string storage;

void pre_read(){
    getline(cin,storage);
    storage += '\n';
}
void replace_str(string &storage,const string pattern, const string new_pattern){
    size_t pos;
    while ( (pos = storage.find(pattern))!=string::npos){
        storage.replace(pos,pattern.size(),new_pattern.c_str());
    }
}
void pre_push(){
    int i = storage.size();
    while (i--)
        cin.putback(storage[i]);//,cerr<<(int)storage[i]<<' ';
        //cerr<<endl;
}
void pre_proc(){
    pre_read();
    replace_str(storage,";","\n");
    replace_str(storage,">=",""+shift_opr('>'));
    replace_str(storage,"<=",""+shift_opr('<'));
    pre_push();
    cerr<<storage<<endl;
}

