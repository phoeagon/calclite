/**
    this header file is intended for preprocess.
    as the implementation in "grammar" class supports only
    one statement in a row, only operators in a character,
    this part do a substitution to the data read from std::cin
    and processes them before pushing everything back
    to std::cin for grammer part to read.

    namespace preprocessor{
        pre_read()      //  read data from std::cin
        replace_str()   //  find and replace a given pattern in a string into a new one
        pre_push()      //  push processed data back to std::cin
    }

*/

#ifndef PREPROCESSOR
namespace preprocessor{

    string storage; /**buffer string*/

    void pre_read(){/**reads a line from cin into storage*/
        getline(cin,storage);
        storage += '\n';
    }

    int replace_str(string &storage,const char*pattern, const char* new_pattern){
        /**replace a given pattern into new_pattern*/
        int     times = 0;
        size_t  pos;
        while ( (pos = storage.find(pattern))!=string::npos){
            //size_t len = pattern.size();
            size_t  len = strlen(pattern);
            storage.replace(pos,len,new_pattern);
            ++times;
        }
        return times;
    }

    void    pre_push(){
        /**push back storage[] back to cin*/
        int     i = storage.size();
        while (i--)
            cin.putback(storage[i]);//,cerr<<(int)storage[i]<<' ';
            //cerr<<endl;
    }
    int pre_proc(){
        /**get a line from cin*/
        pre_read();

        /** replace ";" into EOL */
        replace_str(storage,";;",";");
        int     x = replace_str(storage,";","\n")+1;//how many sub-lines
        //replace_str(storage," \n","\n");
        replace_str(storage,"\n\n","\n");//fixes mutiple ';' together
        char b[10]={0};
        //-----------------
        /**replacing operators from human-styled to single-chared*/

        #define replace_shift_opr(d,oo)\
        b[0] = shift_opr(d);\
        replace_str(storage,oo,b);

        replace_shift_opr('>',">=");
        replace_shift_opr('<',"<=");
        replace_shift_opr('=',"==");
        replace_shift_opr('^',"^^");
        replace_shift_opr('C',"_C_");
        replace_shift_opr('P',"_P_");
        replace_shift_opr('L',"_L_");
        replace_shift_opr('G',"_G_");
        pre_push();/**push back to cin*/

        //for(int i=0;i<storage.size();++i)cerr<<(int)storage[i]<<' '<<endl;

        return x;/** return the number of sub-lines */
    }

}
#endif
#define PREPROCESSOR
