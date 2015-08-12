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
exercise2_7:
Display a file a line at a time, waiting for user press the "Enter" key after
each line.
一次显示一个文件的一行，并在每一行等候用户按‘回车键’。
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
    //这个循环编的很丑陋，希望大家帮忙改进一下。
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
