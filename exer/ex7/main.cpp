/*
���ʵ�֣�
a�����ļ�abc.txt�ж���ȫ�����ݵ�һ�����������У�
b: �Ը�����Ϊ���ߣ��������������е����ݰ���λ����֮ƽ���͵Ĵ�С����
c: abc.txt�ļ��е���Ϊ��12 567 91 33 657 812 2221 3 77
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
//ʹ�÷º������Ի�ø�������ɶ� 
class Rule : public binary_function<unsigned int,unsigned int,bool>
{
	public:
	bool operator()(const unsigned int arg1,const unsigned int arg2){
		return f(arg1)<f(arg2);
	}
	private:
	unsigned int f(unsigned int arg){
		unsigned int sum=0;
		//��ʵ����Ҳ����ʹ�÷º����ģ���Ҫ����ô���˿����е���ˡ� 
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
������Ԫ���� 
