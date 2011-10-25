



class token_stream{
    friend class variables;

	public:
//		token_stream():
//			l2r_pos(0),r2l_pos(0) {}
		token_type get_token();
        void putback(){--l2r_pos;}
		int buffer_size(){return l2r.size();};
		//int r2l_size(){return r2l.size();};
        void l_forward(){++l2r_pos;}
        void l_backward(){--l2r_pos;}
        stream_content_type &data(){return l2r;}

		void init();
        void set_debug(int x){var_data.memory[var_data.get_var_pos("_debug")]=x;}
		void print_l2r();


        variables var_data;
        int l2r_pos ,  r2l_pos ;
	protected:
		stream_content_type l2r ;//, r2l ;

	private:
		int debug(){return var_data.memory[var_data.get_var_pos("_debug")];} ;
        void scan();
		int eol();
		void push_element(token_type);
        //string raw;

};
	int 	token_stream :: eol(){
		if ((unsigned)l2r_pos==l2r.size()-1)return 1;
			else return 0;
	}
	void token_stream :: print_l2r(){
            stream_content_type_iter  it;
            for (it=l2r.begin();it!=l2r.end();++it)
                cerr<<(*it).first<<" "<<(*it).second<<"\n";
            cerr<<endl;
		}
    void token_stream :: push_element(token_type x){
        l2r.push_back(x);
        //++l2r_pos;
    }
	void token_stream :: init(){
        if (debug())cerr<<"token_stream :: init()";
        l2r_pos = 0;
        r2l_pos = 0;
        l2r.clear();
        //cout<<"> "<<flush;
        scan();
	}
    void token_stream :: scan(){
		char x;
        double double_tmp;

		while(!cin_eol()){
            dispose_space();
            x = cin.get();
            if (x==13||x==10)
                break;
            //if (cin>>x){}else throw bad_input();
            if (isdigit(x)){
                cin.putback(x);
                if (!(cin>>double_tmp))
                    throw bad_input();
                push_element(make_pair(_number_type,double_tmp));
            }
            else if (isalpha(x) || x=='_'){
                cin.putback(x);
                string indtf = var_data.cin_get_var_name();
                if (debug())cerr<<"[indentifier: ] "<<indtf<<endl;
                int pos;

                try{
                    pos = var_data.get_var_pos(indtf);
                }catch(no_such_var){
                    pos = var_data.add_var(indtf,0);
                }
                push_element(make_pair(_var_type,pos));
                //to be done here about variables
            }
            else{
                switch(x){
                    case '+':case '-':case '*':case '/':case '%':
                    case '^':case '!':case '>':case '<':case '~':
                    case '@':case '|':case '&':
                    //case shift_opr('>'):case shift_opr('<'):
                        push_element(make_pair(_opr_type,x));break;
                    case '(':case ')':case '[':case ']':
                        push_element(make_pair(_brk_type,x));break;
                    case '#':case '?':
                        push_element(make_pair(_cmd_type,x));break;
                    case ':':
                        push_element(make_pair(_assign_type,x));break;
                    default:
                        throw bad_input();
                }
            }
		}

        r2l_pos = l2r.size()-1;
        /*stream_content_type_iter it = l2r.end();
        for (it--;it>=l2r.begin();--it){
            r2l.push_back(*it);
        }*/
        if (debug())print_l2r();
	}
	token_type token_stream :: get_token(){
        if (l2r_pos<l2r.size())
            return data()[l2r_pos++];
        else return make_pair(-1,NULL);
	}
