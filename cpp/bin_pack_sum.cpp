/*
 --Entry Level Cloud Software Engineer at Celigo--
 A shop sells an item in packets of 6, 9, and 17. A customer can buy any 
 number of packets, but a packet cannot be broken up. Provide an efficient 
 algorithm to solve the question "Can I buy N items?". For example, is it 
 possible to buy 29 items? What about 19? Your algorithm simply needs to 
 return true or false. 
*/

#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::cout;
using std::endl;

void add(int &toAdd, int amount, int goal, vector<int> &v){
    while(toAdd <= goal ){
        if( toAdd == goal ) break;
        toAdd += amount;
        v.push_back(amount);
    }
}

void subtract(int &number, int goal, vector<int> &v){
    if( v.size() == 0 ) return;

    int toSubtract =0;
    do{
        toSubtract = v.back();
        v.pop_back();
        number -= toSubtract;
    } while( toSubtract > goal );
}

bool packing_sum(int threshold ){ 

    if( threshold < 3 ){
        cout << "threshold less than smallest number" << endl;
        return false;
    }

    int pack[]={17,9,3};
    int sum=0,MAX=3, min=-1;
    int element_count=0;
 
    bool inReverse = false;
    vector<int> sequence;
     
    while( element_count > min ){
        min = 0;
        if( !inReverse ){
            for(int i=0; i != MAX; ++i){
                add(sum,pack[i],threshold,sequence); 
                if(sum == threshold ) return true;
                subtract(sum,threshold,sequence);
            }
            element_count = sequence.size();
            inReverse = true;   
        }

        if( sequence[element_count] == pack[MAX-1]) { 
            --element_count; 
            continue;
        }
        int toChange = sequence[element_count];
        sum -= toChange;

        int nextItem=0;
        while( nextItem != MAX ){
            if( pack[nextItem] >= toChange){ ++nextItem; continue; }
            toChange = pack[nextItem];
        }
        sequence[element_count] = pack[MAX];
        add(sum,pack[MAX],threshold,sequence);
        if(sum == threshold) return true;

        subtract(sum,threshold,sequence);
        element_count = sequence.size();
    }

    return false;
}

int main(int argc, char *argv[]){
    int input = atoi( argv[argc-1] );
    cout << " You entered: " << input << endl;
    bool result = packing_sum(input);
    
    if( result )
        cout << "Yes"<< endl;
    else
        cout << "No"<< endl;
    
    return 0;
}
