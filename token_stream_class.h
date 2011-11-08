/**
    this header defines a class token_stream
        with variable support from class variables in "var_support.h"
        with function support from class functions in "function_support.h"

    the stream reads in data from ()::strm
        and break them into tokens.
    tokens are stored in a vector and can be retrieved using get_token()
*/

#ifndef TOKEN_STREAM
#define TOKEN_STREAM
/** token stream header */

#include "calc.h"
#include "function_support.h"
#include "var_support.h"
class token_stream
{

public:
    token_type get_token();
    void    putback()
    {
        --l2r_pos;    /** put back the last token*/
    }
    int     stream_size()
    {
        return l2r.size();
    };/** get the number of the tokens*/

    void    l_forward()
    {
        ++l2r_pos;    /** token pointer plus one */
    }
    void    l_backward()
    {
        --l2r_pos;    /** token pointer decrease one*/
    }
    stream_content_type &data()
    {
        return l2r;    /** reference to the vector that store tokens */
    }

    void init();        /** initiate l2r things and call scan() */
    void print_l2r();   /** print the vector of tokens, for debug purposes*/

    int     l2r_position()
    {
        return l2r_pos;    /** get current token pointer*/
    }

    variables   &vars()
    {
        return var_data;    /**reference to variable data*/
    }
    functions &function()
    {
        return func;    /**reference to function data */
    }
    void    empty_strm_buffer();
    istringstream           strm;
protected:
private:
    functions               func;   /** function data*/
    stream_content_type     l2r ;   /** tokens */
    variables               var_data;   /** variable data*/
    int                     l2r_pos ,  r2l_pos ;/**token pointer*/

    int debug()
    {
        return var_data.memory[vars().get_var_pos("_debug")];
    } ;
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


#endif
