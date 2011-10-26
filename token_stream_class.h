/**
    this header defines a class token_stream
        with variable support from class variables in "var_support.h"
        with function support from class functions in "function_support.h"

    the stream reads in data from ()::strm
        and break them into tokens.
    tokens are stored in a vector and can be retrieved using get_token()
*/

#ifndef TOKEN_STREAM
/** token stream header */


class token_stream{

	public:
		token_type get_token();
        void    putback()   { --l2r_pos; }      /** put back the last token*/
		int     stream_size() { return l2r.size(); };/** get the number of the tokens*/

        void    l_forward()    {++l2r_pos;}/** token pointer plus one */
        void    l_backward()    {--l2r_pos;}/** token pointer decrease one*/
        stream_content_type &data() {return l2r;}/** reference to the vector that store tokens */

		void init();        /** initiate l2r things and call scan() */
		void print_l2r();   /** print the vector of tokens, for debug purposes*/

        int     l2r_position()  {return l2r_pos;}   /** get current token pointer*/

        variables   &vars()     {return var_data;}  /**reference to variable data*/
        functions &function(){return func;}         /**reference to function data */
        void    empty_strm_buffer();
        istringstream           strm;
    protected:
	private:
        functions               func;   /** function data*/
		stream_content_type     l2r ;   /** tokens */
        variables               var_data;   /** variable data*/
        int                     l2r_pos ,  r2l_pos ;/**token pointer*/

		int debug()
            { return var_data.memory[vars().get_var_pos("_debug")]; } ;
            /**get if debug mode*/
        void scan();    /** scan ()::strm and break data into tokens*/
		int eol();      /** return if at the end of token_stream */
		void push_element(token_type);/** add a token to stream */


		int     strm_eol();
        void   find_next_element   ( int value );
        void    jump_to_space();
        void    dispose_space();
        const string strm_get_var_name();
};

void   token_stream:: empty_strm_buffer(){/** clear the std::strm line */
	strm.clear();
	int x;
	while ( x = strm.get() )
		if ( x == 10 || x == 13 || x<0)break;
}

int    token_stream:: strm_eol(){  /** check if std::strm at End of Line*/
    int x = strm.peek();
    return ( x==10 || x==13 ||x<0);
}
void   token_stream::find_next_element   ( int value )
{
	int x;
	while ( strm ){
	    if ( !value && strm_eol() )return;
        x = strm.get();
        //if(x==10 || x==13)return;
		if ( isspace( x ) == value ){
			strm.putback( x );
			return ;
		}
	}
}
void  token_stream::  jump_to_space(){    /** go to next space */
    find_next_element( 1 );
}
void   token_stream:: dispose_space(){    /** go until no more space*/
    find_next_element( 0 );
    //char u = strm.peek();
    //if (u==10 || u==13){ char x = strm.get();}
}
	int 	token_stream :: eol(){
		if ( (unsigned)l2r_pos == l2r.size()-1 )return 1;
			else return 0;
	}
	void token_stream :: print_l2r(){
            stream_content_type_iter  it;
            for ( it=l2r.begin(); it!=l2r.end(); ++it)
                cerr<<(*it).first<<" "<<(*it).second<<"\n";
            cerr<<endl;
		}
    void token_stream :: push_element( token_type x ){
        l2r.push_back( x );
        //++l2r_pos;
    }
	void token_stream :: init(){
    /** initiate l2r things and call scan() */
        if (debug())cerr<<"token_stream :: init()";
        l2r_pos = 0;
        r2l_pos = 0;
        l2r.clear();
        scan();
	}
    void token_stream :: scan(){
    /** scan ()::strm and break data into tokens*/
		int x;
        double double_tmp;

		while( !strm_eol() ){
            dispose_space();
            x = strm.get();
            if ( x == 13 || x == 10 || x<0 )/**End of Line*/
                break;
            //if (strm>>x){}else throw bad_input();
            if ( isdigit( x ) || x=='.'){/** numbers */
                strm.putback( x );
                if ( !( strm >> double_tmp ) )
                    throw bad_input();
                push_element( make_pair( _number_type , double_tmp ) );
            }
            else if ( isalpha( x ) || x=='_'){  /**variables and functions*/
                strm.putback( x );
                string indtf = strm_get_var_name();
                // to add functions here
                int sig= func.isfunction(indtf);
                if (sig!=-1){
                    if (debug())cerr<<"[function: ]"<<indtf<<endl;
                    push_element(make_pair(_func_type,sig));
                }
                else{// just a variable
                    if ( debug() )cerr<<"[indentifier: ] "<<indtf<<endl;
                    int pos;

                    try{
                        pos = var_data.get_var_pos(indtf);
                    }catch(no_such_var){
                        pos = var_data.add_var(indtf,0);
                    }
                    push_element(make_pair(_var_type,pos));
                }
            }
            else{
                switch(x){  /** manipulating operators*/
                    case '+':case '-':case '*':case '/':case '%':
                    case '^':case '!':case '>':case '<':case '~':
                    case '@':case '|':case '&':
                    case shift_opr('>'):case shift_opr('<'):
                    case shift_opr('='):case shift_opr('^'):
                    case shift_opr('C'):case shift_opr('P'):
                    case shift_opr('G'):case shift_opr('L'):
                        push_element(make_pair(_opr_type,x));break;
                    case '(':case ')':case '[':case ']':
                        push_element(make_pair(_brk_type,x));break;
                    case '#':case '?':
                        push_element(make_pair(_cmd_type,x));break;
                    case '=':
                        push_element(make_pair(_assign_type,x));break;
                    default:
                        throw bad_input();
                }
            }
		}
        dispose_space();
        r2l_pos = l2r.size()-1;
        #ifdef _DEBUG
            if ( debug() )print_l2r();
        #endif
	}
	token_type token_stream :: get_token(){
        if (l2r_pos<l2r.size())
            return data()[ l2r_pos++ ];
        else return l2r_pos++ , make_pair(-1,NULL);
	}
const string token_stream :: strm_get_var_name(){/**read variable name from std::strm*/
    string value ;
    char x = strm.peek();
    if ( isalpha(x) || x=='_' ){
        dispose_space();
        while( strm ){
            x=strm.get();
            if (isdigit(x) || isalpha(x) || x=='_')
                value += x;
            else {
                strm.putback(x);
                break;
            }
        }
    }
    if ( value.size() )
        return value;
    else throw bad_input();
}


#endif
#define TOKEN_STREAM
