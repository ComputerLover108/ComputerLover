/*
    learning C++(homework) ѧϰC++�ʼǡ�
    ����һ�����԰����ߣ�ϣ���ҵ�־ͬ���ϵ����ѣ������ҵļ�ͥ��ҵ��ϣ�����˺���
    һ��ѧϰ����ָ���ҵĴ���Ͳ��㡣�ҷ������ϵ����ۣ�����̫�򵥣�����̫���ˣ�
    ��������һ�����ʵģ��������ѵ�ˮ���㵽��ֹ��������ϣ�����ҵ�ѧϰ���̣���ϸ
    �Ĵ�ӡ���������Һͳ�ѧ�߶������档���ܸտ�ʼ�ر�򵥣�������Ϊ����ѧϰ��
    �����Խ��Խ�ѵģ���Ϊ����Ϊ C++ ��ĺ��ѣ������õĻ������Ǳ�ѧ�ˡ��ҵ�
    Ӣ�ĺʹ���ˮƽ��һ�㣬���д�����ָ����лл����֡�
*/
/*
        Think in c++ second version (homework)
        (author: wukexin)
        C++ ���˼�루�ڶ��棩����ͥ��ҵ��
        �����ߣ������Σ�
        
*/
//
/*
exercise 2.1:
Modify Hello.cpp so that it prints your name and age( or shoe size, or your
 dog's age, if that makes you feel better). Complier and run the program.
 �༭ hello.cpp��������ӡ��������֣�����Ь�ĳߴ磬������Ĺ������֣�
 �����о����ã������벢���е��������
*/
//
/*
hello.cpp:
#include <iostream> //stream declaration:
using namespace std;

int main(){
    cout<<"Hello, World! I am "<<8<<" Today!"<endl;
}
*/
#include <iostream>
#include <ctime>
using namespace std;
int main( ){
    clock_t t1=clock();
    cout<<"My name is wukexin, I am 27 old."<<endl;
    clock_t t2=clock();
	double t=(t2-t1)/CLK_TCK;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
