#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;
#include<cstring>
using std::memcpy;

//�õ�ָ����ַ�ʹ�С���ڴ����������ݵĶ����Ʊ�ʾ ����һ��string���ؽ��
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
����� getMemoryBits �����ǰ����ɵ͵�ַ���ߵ�ַ��byte order���ֽ��򣩻�ȡ���ڴ����ݣ����ڳ�����x86������little����ģ�����ֱ�ӵ���printBitsʱ������ֽ�˳�����ƽʱ���Ķ�ϰ�߲���������byte order����������һƪ��־������������ĵ��ã����������1���ڴ��еĶ��������У�

�õ��Ľ���ǣ�00000001 00000000 00000000 00000000

���������Լ���д4�ֽڵ�ֵΪ1�Ķ���������ʱ��Ӧ�û���00000000 00000000 00000000 00000001

��Ҫ�Ķ�����Ļ������޸�getMemoryBits������ʹ�䰴������෴��byte order����ȡ�ڴ����ݣ�
*/
