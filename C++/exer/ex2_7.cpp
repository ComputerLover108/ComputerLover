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
exercise2_7:
Display a file a line at a time, waiting for user press the "Enter" key after
each line.
һ����ʾһ���ļ���һ�У�����ÿһ�еȺ��û������س�������
*/

//

/*
*/
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
void f(){
    using namespace std;
    clock_t t1=clock();
    cout<<"Please input a file's name. ";
    string filename;
    cin>>filename;
    ifstream in( filename.c_str() );
    string line;
    //���ѭ����ĺܳ�ª��ϣ����Ұ�æ�Ľ�һ�¡�
    while( getline(in,line) ){
        cout<<"Please press 'Enter' key to display one line."<<endl;
        cout<<line<<endl;
        if( '\n'==getchar() ){
            continue;
        }
    }
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
