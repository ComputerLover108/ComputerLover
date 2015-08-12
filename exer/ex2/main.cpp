/*
#include "iostream.h"
#include "stdio.h"
max(int x,int y)
{
int z;
if(x>y) z=x;
else z=y;
return z;
}

min(int x,int y)
{
int z;
if(x<y) z=x;
else z=y;
return z;
}

add(int x,int y)
{
int z;
z=x+y;
return z;
}

process(int x,int y,int (*fun)(int,int))
{//int (*fun)();
 int result=(*fun)(x,y);
 return result;
//cout<<result<<endl;
}

void main()

{
//int max(),min(),add();

int a,b;
cout<<"input value a,b"<<endl;
cin>>a>>b;
cout<<"max=";
process(a,b,max);
cout<<"min=";
process(a,b,min);
cout<<"sum=";
process(a,b,add);
}


*/
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;
//
template < typename Arg1, typename Arg2, typename Result >
Result process( Arg1 x, Arg2 y, Result z  ){
	return z;
}
int main()
{
	int a,b;
	cout<<"input value a,b"<<endl;
	cin>>a>>b;
	cout<<"max="<<process<int,int,int >(a,b,std::max(a,b) )<<"\n";
	cout<<"min="<<process<int,int,int >(a,b,std::min(a,b) )<<"\n";
	cout<<"sum="<<process<int,int,int >(a,b,a+b ) <<"\n" ;	
	return 0;
}
