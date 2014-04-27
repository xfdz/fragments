#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "grammar.h"

using std::map;
using std::vector;
using std::string;
using std::getline;
using std::domain_error;
using std::logic_error;
using std::istream;


vector<string> 
gen_sentence( const Grammar& g )
{
    vector<string> ret;

    string sentence = "<sentence";

    gen_aux( g, sentence, ret );
   
    return ret;
}



bool
bracketed( const string& s )
{
    return s.size() > 1 && s[0] == '<' && s[ s.size() - 1 ] == '>';
}

Grammar 
read_grammar(istream& in)
{
    Grammar ret;
    string line;

    //read the input
    while( getline( in, line ) )
    {
         //split the input into words
         vector<string> entry = split( line );
   
         if(! entry.empty() )
         {
             //use the category to store the associated rule
             ret[ entry[0] ].push_back( Rule( entry.begin() + 1, entry.end() ) );
         }
    } 

    return ret;
}

void
gen_aux( const Grammar& g, const string& word, vector<string>& ret)
{
    if(! bracketed( word ) )
    {
         ret.push_back( word );
    } 
    else
    {
        //locate the rule that corresponds to word
        Grammar::const_iterator it = g.find( word );

        if( it == g.end() )
        {
            throw logic_error("emtpy rule");
        }

        //fetch the set of possible rules
        const Rule_collection& c = it->second;

        // from which we select one at random
        const Rule& r = c[ nrand( c.size() ) ];

        // recursively expand the selected rule
        for( Rule::const_iterator i = r.begin(); i != r.end(); ++i)
        {
            gen_aux( g, *i, ret );
        }        
    }
}


int
nrand( int n )
{
    if( n <= 0 || n > RAND_MAX )
    {
        throw domain_error("Argument to nrand is out of range");
    }

    const int bucket_size = RAND_MAX / n;

    int r;

    do
    { 
        r = rand() / bucket_size;
    }
    while( r >= n );

    return r;
}

//true if the argument is whitespace, false otherwise
bool 
space( char c )
{
    return isspace( c );

}

//false if the argument is whitespace, true otherwise
bool 
not_space( char c )
{
    return !isspace( c );
}

vector<string>
split( const string& str )
{
    typedef string::const_iterator iter;

    vector<string> ret;

    iter i = str.begin();

    while( i != str.end() )
    {
        //ignore leading blanks
        i = find_if( i, str.end(), not_space );

        //find end of next word
        iter j = find_if( i, str.end(), space );
  
        //copy the characters in [i,j)
        if( i != str.end() )
        {
            ret.push_back( string(i, j ) );
        } 
       
        i = j; 
    }

    return ret;
}

