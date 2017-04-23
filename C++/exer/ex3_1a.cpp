#include <iostream>
#include "ex3_1.h"
//
void f1( void ){
   using namespace std;
   cout<<"void f1( void )"<<endl;
}
//
char f2( char x){
    using namespace std;
    cout<<"char f2( char x )"<<endl;
    char result=x;
    cout<<"argument: "<<x<<"\tresult: "<<result<<endl;
    return result;
}
//
int f3( int x){
    using namespace std;
    int result=x;
    cout<<"int f3( int x)"<<endl;
    cout<<"argument: "<<x<<"\tresult: "<<result<<endl;
    return result;
}
//
float f4( float x){
    using namespace std;
    float result=x;
    cout<<"float f4( float x )"<<endl;
    cout<<"argument: "<<x<<"\tresult: "<<result<<endl;
    return result;
}
