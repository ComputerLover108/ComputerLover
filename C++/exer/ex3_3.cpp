/*
    learning C++(homework) 学习C++笔记。
    我是一个电脑爱好者，希望找到志同道合的朋友，这是我的家庭作业，希望有人和我
    一起学习，并指教我的错误和不足。我发现网上的讨论，不是太简单，就是太难了，
    好容易有一个合适的，总是蜻蜓点水，点到即止。所以我希望把我的学习过程，详细
    的打印出来，对我和初学者都有裨益。可能刚开始特别简单，但我认为随着学习的
    深入会越来越难的，因为我认为 C++ 真的很难，不爱好的话，还是别学了。我的
    英文和打字水平很一般，如有错误请指正，谢谢大家。
*/
/*
        Think in c++ second version (homework)
        (author: wukexin)
        C++ 编程思想（第二版）（家庭作业）
        （作者：吴珂鑫）

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
写一个程序，他使用 while 循环从标准输入中读取单词到字符串。 这是一个无限循环，你
使用 break 来结束程序。每一个读取的单词，你首先用一个整数来对应它，然后使用switch
来选择他。 在每种情况下，打印它的意思。你必须决定关键单词何它的意思。测试程序，
用也个文件代替标准输入。
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
