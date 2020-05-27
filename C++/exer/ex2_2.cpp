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
exercise 2.2:
Using Stream2.cpp and Numconv.cpp as guidelines, create a program that ask for
the radius of circle and print the area of the circle. You can use the '*'
operator to square the radius. Do not try to print out the value as octal or
hex( these only work with integral types).
ʹ�� stream2.cpp �� numconv.cpp ��Ϊָ��������һ��������Ҫ������Բ�İ뾶��Ȼ��
������Բ�����������ʹ�ò�������������ƽ��Բ�İ뾶����Ҫ��ͼ����˽��ƻ�ʮ��
���ƵĽ�����˽��ƺ�ʮ������ֻ������������Ч����
*/

//

/*
stream2.cpp:
#include <iostream>
using namespace std;
int main(){
    //Specifying formats with manipulators:
    cout<<" a number in decimal: "<<dec<<15<<endl;
    cout<<" in octal: "<<octal<<15<<endl;
    cout<<" in hex: "<<hex<<15<<endl;
    cout<<" a floating-point number: "<<3.14159<<endl;
    cout<<" no-printing char (escape) :"<<char(27)<<endl;
}

numconv.cpp:
#include <iostream>
using namespace std;
int main(){
    int number;
    cout<<"Enter a decimal number: ";
    cin<<number;
    cout<<"Value in octal = 0"<<oct<<number<<endl;
    cout<<"Value in hex =0x"<<hex<<number<<endl;
}
*/
#include <iostream>
#include <ctime>
using namespace std;
int main( ){
    clock_t t1=clock();
    const double PI=3.1415926;
    double r,a;
    cout<<"Please input a number of the radius of the circle: ";
    cin>>r;
    a=PI*r*r;
    cout<<"The area of the circle is: "<<a<<endl;
    clock_t t2=clock();
	double t=(t2-t1)/CLK_TCK;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
