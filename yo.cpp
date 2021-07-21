#include <iostream> 
#include <vector> 

int main(){

    vector<int> v;

    for(int i=0; i <3; i++){
        v.push(i);
    }

    for(int j = v.begin(); j != v.end(); j++){
        std::cout << *i << " "; 

    }

}