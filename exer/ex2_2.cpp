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
exercise 2.2:
Using Stream2.cpp and Numconv.cpp as guidelines, create a program that ask for
the radius of circle and print the area of the circle. You can use the '*'
operator to square the radius. Do not try to print out the value as octal or
hex( these only work with integral types).
使用 stream2.cpp 和 numconv.cpp 作为指导，产生一个程序，它要求输入圆的半径，然后
输出这个圆的面积。你能使用操作符‘＊’来平方圆的半径。不要试图输出八进制或十六
进制的结果（八进制和十六进制只对整数类型有效）。
*/

//

/*
stream2.cpp:
#include <iostream>
using namespace std;
int main(){
    //Specifying formats with manipulators:
    cout<<" a number in decimal: "<<dec<<15<<endl;
    cout<<" in octal: "<<octal<<15<<endl;
    cout<<" in hex: "<<hex<<15<<endl;
    cout<<" a floating-point number: "<<3.14159<<endl;
    cout<<" no-printing char (escape) :"<<char(27)<<endl;
}

numconv.cpp:
#include <iostream>
using namespace std;
int main(){
    int number;
    cout<<"Enter a decimal number: ";
    cin<<number;
    cout<<"Value in octal = 0"<<oct<<number<<endl;
    cout<<"Value in hex =0x"<<hex<<number<<endl;
}
*/
#include <iostream>
#include <ctime>
using namespace std;
int main( ){
    clock_t t1=clock();
    const double PI=3.1415926;
    double r,a;
    cout<<"Please input a number of the radius of the circle: ";
    cin>>r;
    a=PI*r*r;
    cout<<"The area of the circle is: "<<a<<endl;
    clock_t t2=clock();
	double t=(t2-t1)/CLK_TCK;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
