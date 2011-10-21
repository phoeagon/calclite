



class token_stream{
	public:
//		token_stream():
//			l2r_pos(0),r2l_pos(0) {}
		token_type get_token();

		int buffer_size(){return l2r.size();};
		//int r2l_size(){return r2l.size();};
        void l_forward(){++l2r_pos;}
        void l_backward(){--l2r_pos;}
        const stream_content_type &data(){return l2r;}

		void init();
		int eol();
		void push_element(token_type);
	protected:
		stream_content_type l2r ;//, r2l ;
		int l2r_pos ,  r2l_pos ;
	private:

};
	int 	token_stream :: eol(){
		if ((unsigned)l2r_pos==l2r.size()-1)return 1;
			else return 0;
	}
    void token_stream :: push_element(token_type x){
        l2r.push_back(x);
        //++l2r_pos;
    }
	void token_stream :: init(){
		char x;
        double double_tmp;

		while(!cin_eol()){
            x = cin.get();
            if (isdigit(x)){
                cin.putback(x);
                if (!(cin>>double_tmp))
                    throw bad_input();
                push_element(make_pair(_number_type,x));
            }
            else if (isalpha(x)){
                cin.putback(x);
                //to be done here about variables
            }
            else{
                switch(x){
                    case '+':case '-':case '*':case '/':
                        push_element(make_pair(_opr_type,x));break;
                    case '(':case ')':
                        push_element(make_pair(_brk_type,x));break;
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

	}
	token_type token_stream :: get_token(){
        return l2r[l2r_pos++];
	}
