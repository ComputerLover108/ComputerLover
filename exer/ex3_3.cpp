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
exercise3_3:
Write a program that uses a while loop to read words from standard input(cin)
into string. This is an "infinite" while loop, which you break out of (exit the
program) using a break statement. For each word that is read, evaluate it by
first using a sequence of if statements to "map" an integral value to the word,
and then use a switch statement that uses that integral value as its selector (
this sequence of events is not meant to be good programming stytle; it's just
supposed to give you exercise with control flow). Inside each case, print
something meaningful. You must decide what the "intertestin" words are and what
the meaning is. You also must decide what word will singal the end of the
program. Test the program by rediecting a file into the program's standard input
(if you want to save typing, this file can be your program's source file).
дһ��������ʹ�� while ѭ���ӱ�׼�����ж�ȡ���ʵ��ַ����� ����һ������ѭ������
ʹ�� break ����������ÿһ����ȡ�ĵ��ʣ���������һ����������Ӧ����Ȼ��ʹ��switch
��ѡ������ ��ÿ������£���ӡ������˼�����������ؼ����ʺ�������˼�����Գ���
��Ҳ���ļ������׼���롣
*/

//

/*
*/
#include <iostream>
#include <string>
#include <ctime>
//
    const int IGNORER=99;
//
int translate( std::string& word ){
    int result( IGNORER );
    if ( "exit" == word ){
        result=0;
    }
    if ( "wukexin" == word ){
        result=1;
    }
    if ( "wkx" == word ){
        result=2;
    }
    if ( "wangyan" == word){
        result=3;
    }
    return result;
}
//
int main( int argc, char* argv[] ){
    using namespace std;
    clock_t t1=clock();
    if( 1 == argc ){
        cout<<"This is program that it exercise menu."<<endl;
        cout<<"Please input a word: ";
        string word;
        cin>>word;
        int selector(IGNORER);
        while ( true ){
            selector=translate( word );
            switch( selector ){
                case 0: {}
                case 1: {}
                case 2: {}
                case 3: {}
                default: {}
            }
            cin>>word;
        }//end wihle;
    }//endif
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
