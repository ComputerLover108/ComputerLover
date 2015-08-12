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
exercise2_8:
Creat a vector<float> and put 25 floating-point numbers into it using for loop.
Display the vector.
����һ����������ͨ��for ѭ������25�������������������ú���ʾ���������
*/

//

/*
*/
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iterator>
//
void f(){
    using namespace std;
    clock_t t1=clock();
    vector<float> v(25);
    const float PI=3.1415926;
    for( int i=0;i<25;i++){
        v[i]=(PI*i+2.6);
    }
    copy(v.begin(),v.end(),ostream_iterator<float>(cout," ") );
    cout<<endl;
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The f() run "<<t<<"s."<<endl;
}
//
int main( ){
    using namespace std;
    f();
    return 0;
}
