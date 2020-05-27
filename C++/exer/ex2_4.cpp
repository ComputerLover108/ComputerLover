
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
exercise2_4:
Create a program that opens a file and counts the occurence of a particular
word in a file( use the string class's operator '==' to find the word).
дһ����������һ���ļ�������ͳ��������ļ���ĳ�����ⵥ�ʵ�������������ʹ��
string ��Ĳ���������������Ѱ���ض����ʣ���
*/

//

/*
*/
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
//
void count0(std::string filename,std::string particular_word);
void count1(std::string filename,std::string particular_word);
void count2(std::string filename,std::string particular_word);
//
int main( ){
    using namespace std;
    //
    cout<<"Please input a name of the file."<<endl;
    string filename;
    cin>>filename;
    cout<<"Please input a word that you want it."<<endl;
    string particular_word;
    cin>>particular_word;
    //
    count0( filename,particular_word );
    count1( filename,particular_word );
    count2( filename,particular_word );
    //
    return 0;
}
//
void count0(std::string filename,std::string particular_word){
    using namespace std;
    clock_t t1=clock();
    unsigned long result(0);
    ifstream in( filename.c_str() );
    string word;
    while( in>>word ){
        if( word == particular_word ){
            result++;
        }
    }
    in.close();
    clock_t t2=clock();
    cout<<particular_word<<" show "<<result<<" times."<<endl;
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The count0() run "<<t<<"s."<<endl;
}
//
void count1(std::string filename,std::string particular_word){
    using namespace std;

    clock_t t1=clock();
    ifstream in( filename.c_str() );
    stringstream temp;
    temp<<in.rdbuf();
    string ss=temp.str();
    unsigned long result(0);
    long i=ss.find(particular_word,0);
    #ifdef DEBUG
        cout<<"ss="<<ss<<endl;
        cout<<i<<":"<<particular_word<<endl;
    #endif DEBUG
    for(;i<ss.length();i++){
        i=ss.find(particular_word,i);
        if(i == string::npos ){
            break;
        }
        else{
            result++;
            #ifdef DEBUG
                cout<<i<<":"<<particular_word<<endl;
            #endif DEBUG
            continue;
        }
    }
    in.close();
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<particular_word<<" show "<<result<<" times."<<endl;
    cout<<"The count1() run "<<t<<"s."<<endl;

 }
//
void count2(std::string filename,std::string particular_word){
    /*
    using namespace std;
    clock_t t1=clock();
    ifstream in( filename.c_str() );
    //������Ư��ѽ����count0()ǿ���ˣ��������������ַ���ͳ�ƣ���̫�ã�����
    //hello wo shi shiiy yi ge zhong guo ren. ��ͳ��shi shiiy,������ͳ��hi��
    long result = count( istream_iterator<string>(in),
                         istream_iterator<string>(),
                         particular_word
    );
    in.close();
    clock_t t2=clock();
    cout<<particular_word<<" show "<<result<<" times."<<endl;
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The count2() run "<<t<<"s."<<endl;
    */
}



