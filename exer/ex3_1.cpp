/*
    learning C++(homework) ѧϰC++�ʼǡ�
    ����һ�����԰����ߣ�ϣ���ҵ�־ͬ���ϵ����ѣ������ҵļ�ͥ��ҵ��ϣ�����˺���
    һ��ѧϰ����ָ���ҵĴ���Ͳ��㡣�ҷ������ϵ����ۣ�����̫�򵥣�����̫���ˣ�
    ��������һ�����ʵģ��������ѵ�ˮ���㵽��ֹ��������ϣ�����ҵ�ѧϰ���̣���ϸ
    �Ĵ�ӡ���������Һͳ�ѧ�߶������档���ܸտ�ʼ�ر�򵥣�������Ϊ����ѧϰ��
    �����Խ��Խ�ѵģ���Ϊ����Ϊ C++ ��ĺ��ѣ������õĻ������Ǳ�ѧ�ˡ��ҵ�
    Ӣ�ĺʹ���ˮƽ��һ�㣬���д�����ָ����лл��ҡ�
*/
/*
        Think in c++ second version (homework)
        (author: wukexin)
        C++ ���˼�루�ڶ��棩����ͥ��ҵ��
        �����ߣ������Σ�

*/
//

/*
exercise3_1:
Creat a header file( with an extension of '.h'). In this file, declare a group
of functions by varying the argument lists and return values from among the
following: void, char, int, and float. Now creat a .cpp file that includes your
head file and creats definitions for all of these functions. Each definition
should simply print out the function name, argument list, and return type so you
know it's been called.  Creat second .cpp file that include your header file and
defines int main(), containing calls to all of your functions. Compiler and run
your program.
����һ����.h��׺����ͷ�ļ���������ļ������һ�麯�������в�ͬvoid, char, int,
float �����ͷ���ֵ����дһ��.cpp��׺�����ļ������������ͷ�ļ���������Щ�����Ķ�
�塣ÿһ������Ӧ�ü򵥵Ĵ�ӡ���������ĺ������Ͳ����б��з���ֵ��д�ڶ���cpp
�ļ�����ͷ�ļ���int main(),������ĺ������á������������ĳ���
*/

//

/*
*/
#include <iostream>
#include <ctime>
#include "ex3_1.h"
int main( ){
    using namespace std;
    clock_t t1=clock();
    f1();
    f2('a');
    f3(1);
    f4(9.87);
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
