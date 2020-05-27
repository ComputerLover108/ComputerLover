/*
编程实现：
a：从文件abc.txt中读入全部数据到一个整数向量中；
b: 以该向量为菜蔬，将该整数向量中的数据按各位数字之平方和的大小排序；
c: abc.txt文件中的数为：12 567 91 33 657 812 2221 3 77
*/
/**
	Module Name: 

	Description:

	Author:wukexin
	Created:
	Last Change:

	Functions:

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;
//使用仿函数可以获得更大的自由度 
class Rule : public binary_function<unsigned int,unsigned int,bool>
{
	public:
	bool operator()(const unsigned int arg1,const unsigned int arg2){
		return f(arg1)<f(arg2);
	}
	private:
	unsigned int f(unsigned int arg){
		unsigned int sum=0;
		//其实这里也可以使用仿函数的，但要是这么做了可能有点过了。 
		while(arg>0){
			sum+=(arg%10)*(arg%10);
			arg/=10;
		}
		return sum;
	}
};
//
int main(int argc, char *argv[])
{
	if( 2== argc ){
		ifstream file(argv[1]);
		unsigned int s;
		vector<unsigned int > vc;
		while( file >> s){
			vc.push_back(s);
		}
		cout<<"Before sort()\n";
		copy(vc.begin(),vc.end(),ostream_iterator<unsigned int>(cout," "));
		cout<<"\nAfter sort()\n";
		sort(vc.begin(),vc.end(),Rule() );
		copy(vc.begin(),vc.end(),ostream_iterator<unsigned int>(cout," "));
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}
声明友元函数 
