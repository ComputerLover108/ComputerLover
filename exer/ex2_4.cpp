
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
exercise2_4:
Create a program that opens a file and counts the occurence of a particular
word in a file( use the string class's operator '==' to find the word).
写一个程序，它打开一个文件，并且统计在这个文件中某个特殊单词的数量。（可以使用
string 类的操作符‘＝＝’来寻找特定单词）。
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
    //这真是漂亮呀，比count0()强多了，可是它对任意字符的统计，不太好，比如
    //hello wo shi shiiy yi ge zhong guo ren. 能统计shi shiiy,但不能统计hi。
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



