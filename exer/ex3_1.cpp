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
exercise3_1:
Creat a header file( with an extension of '.h'). In this file, declare a group
of functions by varying the argument lists and return values from among the
following: void, char, int, and float. Now creat a .cpp file that includes your
head file and creats definitions for all of these functions. Each definition
should simply print out the function name, argument list, and return type so you
know it's been called.  Creat second .cpp file that include your header file and
defines int main(), containing calls to all of your functions. Compiler and run
your program.
产生一个带.h后缀名的头文件。在这个文件里，声明一组函数，带有不同void, char, int,
float 参数和返回值。再写一个.cpp后缀名的文件，他包含你的头文件和所有这些函数的定
义。每一个定义应该简单的打印出调用它的函数名和参数列表还有返回值。写第二个cpp
文件包含头文件和int main(),包含你的函数调用。编译和运行你的程序。
*/

//

/*
*/
#include <iostream>
#include <ctime>
#include "ex3_1.h"
int main( ){
    using namespace std;
    clock_t t1=clock();
    f1();
    f2('a');
    f3(1);
    f4(9.87);
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
