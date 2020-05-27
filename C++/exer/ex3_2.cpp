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
exercise3_2:
Write a program that uses two nested for loops and modolus operator(%) to
detects and print prime numbers( integral numbers that are not evenly diviable
by other numbers excepts for themselves and it.
дһ�������������������õ�forѭ����ȡģ����������Ϻʹ�ӡ������
*/
#include <iostream>
#include <ctime>
#include <vector>
#include <math>
#include <algorithm>
#include <iterator>
//
void prime(unsigned long x){
    using namespace std;
    unsigned long limit=ceil( x/2 );
    vector<unsigned long> v(limit);
    unsigned long count(0);
    vector<unsigned long>::iterator itr=v.begin();
    if( x <= 1 ){
        cout<<x<<" has none prime number."<<endl;
    }
    for( unsigned long a = 2; a <= x; a++){
        for( unsigned long b=2; b<=a; b++){
            if( a % b >0 ){
                #ifdef DEBUG
                cout<<"\n"<<a<<">"<<b<<endl;
                #endif //debug
                continue;
            }
            else{
                if( b!=a ){
                    #ifdef DEBUG
                    cout<<"\n"<<a<<"!="<<b<<endl;
                    #endif //debug
                    break;
                }
                else{
                    *itr=a;
                    #ifdef DEBUG
                    cout<<"\n*itr="<<*itr<<endl;
                    #endif //debug
                    if(itr != v.end() ){
                        itr++;
                        ++count;
                    }
                    //v.push_back(a);
                }
            }
        }
    }
    copy(v.begin(), itr, ostream_iterator<unsigned long>(cout," ") );
    cout<<"\n"<<x<<" has "<<count<<" prime numbers."<<endl;
    cout<<endl;
}
//
int main( ){
    using namespace std;
    cout<<"This is a program that print prime number in your area."<<endl;
    cout<<"limit:";
    clock_t t1=clock();
    unsigned long x;
    cin>>x;
    prime(x);
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
