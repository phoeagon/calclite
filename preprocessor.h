namespace preprocessor{
    string storage;

    void pre_read(){
        getline(cin,storage);
        storage += '\n';
    }
    int replace_str(string &storage,const char*pattern, const char* new_pattern){
        int times = 0;
        size_t pos;
        while ( (pos = storage.find(pattern))!=string::npos){
            //size_t len = pattern.size();
            size_t len = strlen(pattern);
            storage.replace(pos,len,new_pattern);
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
        char b[10]={0};

        b[0] = shift_opr('>');
        replace_str(storage,">=",b);
        b[0] = shift_opr('<');
        replace_str(storage,"<=",b);
        b[0] = shift_opr('=');
        replace_str(storage,"==",b);
        b[0] = shift_opr('^');
        replace_str(storage,"^^",b);

        pre_push();
        //for(int i=0;i<storage.size();++i)cerr<<(int)storage[i]<<' '<<endl;
        return x;
    }

}
