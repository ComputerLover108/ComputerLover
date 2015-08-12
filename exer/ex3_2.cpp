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
exercise3_2:
Write a program that uses two nested for loops and modolus operator(%) to
detects and print prime numbers( integral numbers that are not evenly diviable
by other numbers excepts for themselves and it.
写一个程序，它是用两个内置的for循环和取模操作符来诊断和打印质数。
*/
#include <iostream>
#include <ctime>
#include <vector>
#include <math>
#include <algorithm>
#include <iterator>
//
void prime(unsigned long x){
    using namespace std;
    unsigned long limit=ceil( x/2 );
    vector<unsigned long> v(limit);
    unsigned long count(0);
    vector<unsigned long>::iterator itr=v.begin();
    if( x <= 1 ){
        cout<<x<<" has none prime number."<<endl;
    }
    for( unsigned long a = 2; a <= x; a++){
        for( unsigned long b=2; b<=a; b++){
            if( a % b >0 ){
                #ifdef DEBUG
                cout<<"\n"<<a<<">"<<b<<endl;
                #endif //debug
                continue;
            }
            else{
                if( b!=a ){
                    #ifdef DEBUG
                    cout<<"\n"<<a<<"!="<<b<<endl;
                    #endif //debug
                    break;
                }
                else{
                    *itr=a;
                    #ifdef DEBUG
                    cout<<"\n*itr="<<*itr<<endl;
                    #endif //debug
                    if(itr != v.end() ){
                        itr++;
                        ++count;
                    }
                    //v.push_back(a);
                }
            }
        }
    }
    copy(v.begin(), itr, ostream_iterator<unsigned long>(cout," ") );
    cout<<"\n"<<x<<" has "<<count<<" prime numbers."<<endl;
    cout<<endl;
}
//
int main( ){
    using namespace std;
    cout<<"This is a program that print prime number in your area."<<endl;
    cout<<"limit:";
    clock_t t1=clock();
    unsigned long x;
    cin>>x;
    prime(x);
    clock_t t2=clock();
    double t = static_cast<double>(t2-t1) / CLOCKS_PER_SEC;
    cout<<"The program run "<<t<<"s."<<endl;
    return 0;
}
