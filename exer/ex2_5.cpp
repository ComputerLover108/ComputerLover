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
exercise2_5:
Change Fillvector.cpp so that it prints the lines (backward) from last to first.
�ı� Fillvector.cpp ʹ���Ӻ���ǰ����С�
*/
//
/*
Fillvector.cpp:
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main(){
    vector<string> v;
    ifstream in("Fillvector.cpp");
    string line;
    while( getline(in,line) ){
        v.push_back(line);
    }
    for(int i=0;i<v.size();i++)
        cout<<v[i]<<",";
    cout<<endl;
}
*/
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
void f1(){
    using namespace std;
    clock_t t1=clock();
    ifstream in("ex2_5.cpp");
    vector<string> v;
    string line;
    while( getline(in,line) ){
        v.push_back(line);
    }
    for( int i=v.size();i>0;i--){
        cout<<v[i]<<",";
    }
    cout<<endl;
    in.close();
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The f1() run "<<t<<"s."<<endl;

}
//
void f2(){
    using namespace std;
    clock_t t1=clock();
    ifstream in("ex2_5.cpp");
    vector<string> v;
    string line;
    while( getline(in,line) ){
        v.push_back(line);
    }
    vector<string>::reverse_iterator itr=v.rbegin();
    for( ; itr!=v.rend();itr++){
        cout<<*itr<<",";
    }
    cout<<endl;
    in.close();
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The f2() run "<<t<<"s."<<endl;

}
//
int main( ){
    using namespace std;
    f1();
    f2();
    return 0;
}
