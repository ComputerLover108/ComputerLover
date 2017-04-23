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
exercise2_6:
Change Fillvector.cpp so that it concatenates all the elements in the vector
into a single string before printing it out, but dont't try to add line number-
ing.
 �޸� Fillvector.cpp ʹ���������е�����Ԫ�������֮ǰ���ӵ�һ���ַ����У�����Ҫ
 ��ͼ����кš�
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
#include <fstream>
#include <string>
#include <vector>
//
void f(){
    using namespace std;
    clock_t t1=clock();

    vector<string> result;
    ifstream in("ex2_6.cpp");
    string line;
    while( getline(in,line) ){
        result.push_back(line);
    }
    line.erase();
    for(int i=0;i<result.size();i++){
        result[i].append("\n");
        line.append(result[i]);
    }
    cout<<line<<endl;
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
