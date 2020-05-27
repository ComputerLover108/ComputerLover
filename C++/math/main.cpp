/*
	Program Name(��������): 

	Description(����):
	����һ���Ž�����,�����Ӧ�Ķ�������
	Author(����):wukexin
	Created Date(��һ�α�дʱ��):
	Last Change(���һ���޸ı�ע):
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include "boost/lexical_cast.hpp"
//
const bool DEBUG=true;
using namespace std;
//���ƹ����࣬��ʱΪ�� 
 class Cnumber_rule 
 {
 	public:
 
 	protected:
 
 	private:
 
 };
//�ж��ַ���s��sign_c��ʾ�������õķ��ż���,rule��ʾ���ƹ��� 
bool is_number(const char* s,const char* sign_c,Cnumber_rule& rule){
	size_t L1=strlen(s);
	size_t L2=strlen(sign_c);
	vector<char> c1(sign_c,sign_c+L2),c2(s,s+L1);
	sort(c1.begin(),c1.end());
	sort(c2.begin(),c2.end());
	if( includes(c1.begin(),c1.end(),c2.begin(),c2.end()) ) {
		return true;
	}
	return false;
}
//
int main(int argc, char *argv[])
{
	if(2 == argc)
	{
		using boost::lexical_cast;
		using boost::bad_lexical_cast;
		char sign_c[]={'-','.','0','1','2','3','4','5','6','7','8'};
		Cnumber_rule rule;
		if(is_number(argv[1],sign_c,rule))
		{
					
		}
		if(DEBUG)
		{
			cout<<"is_number()="<<is_number(argv[1],sign_c,rule)<<endl;
		}
	}
	return EXIT_SUCCESS;
}
