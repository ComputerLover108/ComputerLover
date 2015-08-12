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
exercise2_3:
Create a program that opens a file and counts the whitespace-separated words in
that file.
дһ����������һ���ļ�����ͳ��������ļ����ж��ٸ��пհ׷ָ��ĵ��ʡ�
*/

//

/*
*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
int main( ){
    clock_t t1=clock();
    cout<<"Please input the name of the file."<<endl;
    string filename;
    cin>>filename;
    ifstream in( filename.c_str() );
    unsigned long result(0);
    string word;
    while( in >> word ){
        result++;
        #ifdef DEBUG
        cout<<"("<<result<<")"<<word<<" ";
        #endif //debug
    }
    cout<<filename<<" has "<<result<<" words."<<endl;
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
/*
��������е�С���⣬��gcc2.952��̣��ڻ������ĵ�����£��ò�����ȷ���������
bcc5.5.1�¾Ϳ��ˣ���֪�������æ������Ϊʲô��������
*/
