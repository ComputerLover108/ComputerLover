/*
��������vc ��һ����---��һ���ı��ļ� ������ ���ֹؼ��ֵĴ�����Ҫ���̻��ģ�
���幤���������£�
���г���� ��dos���� ������Ӧ���ļ�����·�����������ļ���
load c:\text.txt

Ȼ������ �ؼ��� "good"

Ȼ�����Եõ� good ���ֵĴ���
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;
unsigned int count(const std::string& aim,const std::string& key)
{
	unsigned int loc=0,result=0;
	do{
		loc=aim.find( key, loc  ); 
		if(loc != std::string::npos){
    		++result;
    		++loc;
		}
    }while( loc != std::string::npos);
    return result;
}
//
int main(int argc, char *argv[])
{
	if( 2!=argc){
		std::cout<<"Example:\t load c:\\text\n";
		return 0;
	}
	std::ifstream file(argv[1]);
	std::string content;
	std::stringstream temp;
	temp<<file.rdbuf();
	content=temp.str();
	//std::cout<<content<<std::endl;
	std::cout<<"Please input key word:";
	std::string word;
	std::getline(cin,word);
	std::cout<<"There are "<<count(content,word)<<" "<<word<<"\n";
	return 0;
}
