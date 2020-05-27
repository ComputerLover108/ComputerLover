/*
现在想用vc 做一件事---对一个文本文件 搜索出 出现关键字的次数（要过程话的）
具体工作过程如下：
运行程序后 在dos窗口 输入相应的文件名和路径（即载入文件）
load c:\text.txt

然后输入 关键字 "good"

然后便可以得到 good 出现的次数
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
