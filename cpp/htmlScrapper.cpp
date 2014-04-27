#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <list>
#include <regex.h>

using std::list;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

void usage(const char *program_name){
    cout << "usage: " << program_name << " filename" << endl; 
    exit(0);
}

string delimiter1 = "class=\"copy\">\<color=\"purple\><b\>";
string delimiter2 = "color=\"purple\"><b>";

int main(int argc, char* argv[])
{
    if( argc < 2 ) usage(argv[0]);

    ifstream infile(argv[1]);
    string inputstring, htmlstring;
    while( getline(infile, inputstring ) )
        htmlstring.append(inputstring);  

    string:: current, next;
    string::size_type position, currentlength = htmlstring.size();
    while((position = htmlstring.find(delimiter1))!= string::npos){

        position += delimiter1.size();
        if( currentlength <= position ) break;

        htmlstring = htmlstring.substr(position, htmlstring.size());
        currentlength = htmlstring.size();

        int i;
        while((position = htmlstring.find(delimiter2))!= string::npos){
            position += delimiter2.size();
            if( currentlength <= position ) break;

            for(i=0; i != htmlstring.size(); ++i ){
                if( htmlstring[i] == '<' ){
                //  ending character found 
                    if( htmlstring[i+1] == "b" && htmlstring[i+2] == "r") 
                    else
                    // forward past <br>
                }
                cout << htmlstring[i];
            }

            htmlstring = htmlstring.substr(position, htmlstring.size());
            currentlength = htmlstring.size();
        }

        while((position = htmlstring.find(delimiter3))!= string::npos){
            position += delimiter3.size();
            if( currentlength <= position ) break;

            for(i=0; i != htmlstring.size(); ++i ){
                if(htmlstring[i] == '<' )  break;
                cout << htmlstring[i];
            }

            htmlstring = htmlstring.substr(position, htmlstring.size());
            currentlength = htmlstring.size();
        }
    }

    infile.close();

    return EXIT_SUCCESS;
}
