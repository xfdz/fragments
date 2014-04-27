#ifndef GUARD_Grammar
#define GUARD_Grammar

#include <map>
#include <string>
#include <vector>
#include <iostream>


typedef std::vector<std::string> Rule;
typedef std::vector<Rule> Rule_collection;
typedef std::map<std::string, Rule_collection> Grammar; 


std::vector<std::string> 
gen_sentence( const Grammar &g );

bool 
bracketed( const std::string &s );

Grammar 
read_grammar( std::istream &in);

void 
gen_aux( const Grammar &g, const std::string &word, std::vector<std::string> &ret);

int 
nrand( int n );

bool 
space( char c );

bool 
not_space( char c );

std::vector<std::string> 
split( const std::string &str ); 


#endif 
