



class token_stream{
	public:
//		token_stream():
//			l2r_pos(0),r2l_pos(0) {}
		token_type get_token();
		void init();
		int eol();
	protected:
		stream_content_type l2r , r2l ;
		int l2r_pos ,  r2l_pos ;
	private:
		
};
	int 	token_stream :: eol(){
		if (l2r_pos==l2r.size()-1)return 1;
			else return 0;
	}
	
	void token_stream :: init(){
		
	}
	token_type token_stream :: get_token(){

	}
