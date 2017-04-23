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
exercise2_3:
Create a program that opens a file and counts the whitespace-separated words in
that file.
写一个程序，它打开一个文件并且统计在这个文件中有多少个有空白分隔的单词。
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
这个程序有点小问题，用gcc2.952编程，在混有中文的情况下，得不到正确结果，而用
bcc5.5.1下就可了，有知道的请帮忙告诉我为什么会这样。
*/
