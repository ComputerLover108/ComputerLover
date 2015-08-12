/*
    learning C++(homework) 学习C++笔记。
    我是一个电脑爱好者，希望找到志同道合的朋友，这是我的家庭作业，希望有人和我
    一起学习，并指教我的错误和不足。我发现网上的讨论，不是太简单，就是太难了，
    好容易有一个合适的，总是蜻蜓点水，点到即止。所以我希望把我的学习过程，详细
    的打印出来，对我和初学者都有裨益。可能刚开始特别简单，但我认为随着学习的
    深入会越来越难的，因为我认为 C++ 真的很难，不爱好的话，还是别学了。我的
    英文和打字水平很一般，如有错误请指正，谢谢大家乐。
*/
/*
        Think in c++ second version (homework)
        (author: wukexin)
        C++ 编程思想（第二版）（家庭作业）
        （作者：吴珂鑫）
        
*/
//
/*
exercise 2.1:
Modify Hello.cpp so that it prints your name and age( or shoe size, or your
 dog's age, if that makes you feel better). Complier and run the program.
 编辑 hello.cpp，让它打印出你的名字（或者鞋的尺寸，或者你的狗的名字，
 如果你感觉更好）。编译并运行的这个程序。
*/
//
/*
hello.cpp:
#include <iostream> //stream declaration:
using namespace std;

int main(){
    cout<<"Hello, World! I am "<<8<<" Today!"<endl;
}
*/
#include <iostream>
#include <ctime>
using namespace std;
int main( ){
    clock_t t1=clock();
    cout<<"My name is wukexin, I am 27 old."<<endl;
    clock_t t2=clock();
	double t=(t2-t1)/CLK_TCK;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
