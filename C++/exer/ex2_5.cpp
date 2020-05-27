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
exercise2_5:
Change Fillvector.cpp so that it prints the lines (backward) from last to first.
改变 Fillvector.cpp 使他从后往前输出行。
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
