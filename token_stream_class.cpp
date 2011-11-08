/*
    this file implements methods defined in token_stream_class.h
*/

#include "token_stream_class.h"

void   token_stream:: empty_strm_buffer() /** clear the std::strm line */
{
    strm.clear();
    int x;
    while ( x = strm.get() )
        if ( x == 10 || x == 13 || x<0)break;
}

int    token_stream:: strm_eol()   /** check if std::strm at End of Line*/
{
    int x = strm.peek();
    return ( x==10 || x==13 ||x<0);
}
void   token_stream::find_next_element   ( int value )
{
    int x;
    while ( strm )
    {
        if ( !value && strm_eol() )return;
        x = strm.get();
        //if(x==10 || x==13)return;
        if ( isspace( x ) == value )
        {
            strm.putback( x );
            return ;
        }
    }
}
void  token_stream::  jump_to_space()     /** go to next space */
{
    find_next_element( 1 );
}
void   token_stream:: dispose_space()     /** go until no more space*/
{
    find_next_element( 0 );
    //char u = strm.peek();
    //if (u==10 || u==13){ char x = strm.get();}
}
int 	token_stream :: eol()
{
    if ( (unsigned)l2r_pos == l2r.size()-1 )return 1;
    else return 0;
}
void token_stream :: print_l2r()
{
    stream_content_type_iter  it;
    for ( it=l2r.begin(); it!=l2r.end(); ++it)
        cerr<<(*it).first<<" "<<(*it).second<<"\n";
    cerr<<endl;
}
void token_stream :: push_element( token_type x )
{
    l2r.push_back( x );
    //++l2r_pos;
}
void token_stream :: init()
{
    /** initiate l2r things and call scan() */
    if (debug())cerr<<"token_stream :: init()";
    l2r_pos = 0;
    r2l_pos = 0;
    l2r.clear();
    scan();
}
void token_stream :: scan()
{
    /** scan ()::strm and break data into tokens*/
    int x;
    double double_tmp;

    while( !strm_eol() )
    {
        dispose_space();
        x = strm.get();
        if ( x == 13 || x == 10 || x<0 )/**End of Line*/
            break;
        //if (strm>>x){}else throw bad_input();
        if ( isdigit( x ) || x=='.') /** numbers */
        {
            strm.putback( x );
            if ( !( strm >> double_tmp ) )
                throw bad_input();
            push_element( make_pair( _number_type , double_tmp ) );
        }
        else if ( isalpha( x ) || x=='_')   /**variables and functions*/
        {
            strm.putback( x );
            string indtf = strm_get_var_name();
            // to add functions here
            int sig= func.isfunction(indtf);
            if (sig!=-1)
            {
                if (debug())cerr<<"[function: ]"<<indtf<<endl;
                push_element(make_pair(_func_type,sig));
            }
            else // just a variable
            {
                if ( debug() )cerr<<"[indentifier: ] "<<indtf<<endl;
                int pos;

                try
                {
                    pos = var_data.get_var_pos(indtf);
                }
                catch(no_such_var)
                {
                    pos = var_data.add_var(indtf,0);
                }
                push_element(make_pair(_var_type,pos));
            }
        }
        else
        {
            switch(x)   /** manipulating operators*/
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
            case '!':
            case '>':
            case '<':
            case '~':
            case '@':
            case '|':
            case '&':
            case shift_opr('>'):
            case shift_opr('<'):
            case shift_opr('='):
            case shift_opr('^'):
            case shift_opr('C'):
            case shift_opr('P'):
            case shift_opr('G'):
            case shift_opr('L'):
                push_element(make_pair(_opr_type,x));
                break;
            case '(':
            case ')':
            case '[':
            case ']':
                push_element(make_pair(_brk_type,x));
                break;
            case '#':
            case '?':
                push_element(make_pair(_cmd_type,x));
                break;
            case '=':
                push_element(make_pair(_assign_type,x));
                break;
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
token_type token_stream :: get_token()
{
    if (l2r_pos<l2r.size())
        return data()[ l2r_pos++ ];
    else return l2r_pos++ , make_pair(-1,NULL);
}
const string token_stream :: strm_get_var_name() /**read variable name from std::strm*/
{
    string value ;
    char x = strm.peek();
    if ( isalpha(x) || x=='_' )
    {
        dispose_space();
        while( strm )
        {
            x=strm.get();
            if (isdigit(x) || isalpha(x) || x=='_')
                value += x;
            else
            {
                strm.putback(x);
                break;
            }
        }
    }
    if ( value.size() )
        return value;
    else throw bad_input();
}



