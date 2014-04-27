#include <iostream>
#include <cstdlib>
#include <map>

using std::map;
using std::cout;
using std::endl;
using std::cerr;
using std::string;

#define MAXROMAN 7 

typedef map<char,int> roman_mapvals;
typedef roman_mapvals::const_iterator roman_mapiter;

int   RTABLE_VALUES[]={  1,  5, 10, 50, 100, 500, 1000 };
char  RTABLE_CHARS[] ={ 'I','V','X','L','C','D','M' };

int usage(const char *name){
    cout << "usage: "<< name << " <roman number> " << endl; 
    exit(EXIT_SUCCESS);
}

int roman_to_decimal(const string &input, 
                     const roman_mapvals &romanreftable) { 

     if( input.size() == 1 ){

        roman_mapiter itr_roman_num =  romanreftable.find(input[0]); 
        if( itr_roman_num == romanreftable.end()) 
             return EXIT_FAILURE;

        return itr_roman_num->second;
     }

     int sum=0, prefix=0, suffix =0, previous=0;
     string::const_iterator itr_input = input.begin();
     for(int i=0,j=1; i != input.size() && j != input.size(); ++i,++j){

         roman_mapiter 
         itr_firstroman_num = romanreftable.find(itr_input[i]); 
         roman_mapiter 
         itr_secondroman_num = romanreftable.find(itr_input[j]); 

         if( itr_firstroman_num == romanreftable.end() 
             || itr_secondroman_num == romanreftable.end() ) 
         // only valid roman characters in RTABLE_CHARS
             return EXIT_FAILURE;
           
         prefix = itr_firstroman_num->second; 
         suffix =  itr_secondroman_num->second; 

         if( prefix < suffix )
             sum = ( sum - prefix ) + ( suffix - prefix ); 
         else{
             if( i != 0 )
             // not first time around
                     sum += suffix; 
             else
             // first time around 
                 sum = prefix + suffix;
         }
         
         previous = prefix;
     }

     return sum;
}

int main( int argc, char *argv[])
{
    if( argc < 2 ) usage(argv[0]);
   std::string roman_number(argv[1]); roman_mapvals reference_table;
    for(int i=0; i != MAXROMAN; ++i)
    // build lookup table 
        reference_table[ RTABLE_CHARS[i] ] = RTABLE_VALUES[i]; 

    int result = roman_to_decimal(roman_number, reference_table);    

    if( result == EXIT_FAILURE ){
        cerr << "FAILED: input contains non-Roman character "<< endl; 
        exit(EXIT_FAILURE);
    }

    cout << "Arabic number " << result << endl;

    return EXIT_SUCCESS;
}
