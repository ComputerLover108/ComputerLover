#include <iostream>
#include <string>
using namespace std;
int main(void){
    cout<<"Please input a serial number:";
    string s;
    cin>>s;
    for( string::reverse_iterator itr=s.rbegin(); itr != s.rend();itr++){
        cout<<*itr;
    }
     cout<<endl;
}

