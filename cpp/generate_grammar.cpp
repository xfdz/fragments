#include <stdio.h>
#include <vector>
#include "grammarUtil"

using namespace std;

int main()
{
    //generate sentence
    vector<string> sentence = gen_sentence( read_grammar( cin ) );

    // write the first word, if any
    vector<strng>::const_iterator it = sentence.begin();
  
    if(! sentence.emtpy() )
    {
        cout << *it;
        ++it;
    }

    //write the rest of the words, each preceded by a space
    while( it != sentence.end() )
    {
        cout << "  " << *it;
        ++it;
    }

    cout << endl;

    return 0;
}

