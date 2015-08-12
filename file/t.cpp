#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;
#include<cstring>
using std::memcpy;

//得到指定地址和大小的内存区域中数据的二进制表示 ，用一个string返回结果
string getMemoryBits(const void * const memAdr, const int& size)
{
    string result;
    unsigned char buffer, key = 1;
    for(int i = 0; i < size; ++i)
    {
        memcpy(&buffer, reinterpret_cast<const unsigned char*>(memAdr) + i, 1);
        for(int j = 7; j >= 0; --j)
        {
            if( (buffer >> j) & key )
                result += '1';
            else
                result += '0';
        }
    }
    return result;
}
//
string toSeegetMemoryBits(const void * const memAdr, const int& size)
{
    string result;
    unsigned char buffer, key = 1;
    for(int i = size - 1; i >= 0; --i)
    {
        memcpy(&buffer, reinterpret_cast<const unsigned char*>(memAdr) + i, 1);
        for(int j = 7; j >= 0; --j)
        {
            if( (buffer >> j) & key )
                result += '1';
            else
                result += '0';
        }
    }
    return result;
}
//
void printBits(const void* const memAdr, const int& size)
{
    for(int i = 0; i < size * 8; ++i)
    {
        cout << getMemoryBits(memAdr, size)[i];
        if(i % 8 == 7)
            cout << ' ';
    }
    cout << endl;
}
//
int main(){
	int a1=0;
	int* a=&a1;
	double b1=0.0;
	double* b=&b1;
	for(int i=0;i<9;i++){
		printBits(a,sizeof(int) );
		cout<<*a<<"\t"<<a<<"\n";
		a1++;
		cout<<"double:\n";
		printBits(b,sizeof(double) );
		b1+=0.1;
		cout<<*b<<"\t"<<b<<"\n";
	}
}
/*
上面的 getMemoryBits 函数是按照由低地址到高地址的byte order（字节序）获取的内存数据，由于常见的x86机器是little规则的，所以直接调用printBits时输出的字节顺序会与平时的阅读习惯不符（关于byte order见本博客上一篇日志），比如下面的调用，输出整形数1在内存中的二进制序列：

得到的结果是：00000001 00000000 00000000 00000000

正常我们自己书写4字节的值为1的二进制整数时，应该会是00000000 00000000 00000000 00000001

想要阅读方便的话可以修改getMemoryBits函数，使其按与机器相反的byte order来获取内存数据：
*/
