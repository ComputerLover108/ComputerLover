/*
	Program Name(程序名称): 

	Description(描述):
	输入一个九进制数,输出相应的二进制数
	Author(作者):wukexin
	Created Date(第一次编写时间):
	Last Change(最后一次修改备注):
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
//进制规则类，暂时为空 
 class Cnumber_rule 
 {
 	public:
 
 	protected:
 
 	private:
 
 };
//判断字符串s，sign_c表示数字所用的符号集合,rule表示进制规则 
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
