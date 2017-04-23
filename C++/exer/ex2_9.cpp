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
exercise2_9:
Creat three vector<float> objects and fill the first two as in the previous.
Write a for loop that adds each corresponding element in the first two vectors
and puts the result in the corresponding element of the third vector. Display
all three vectors.
产生三个浮点数容器，并像上个练习一样填充头两个容器。写一个for 循环添加相应的元素
到头两个容器中，并把结果放在第三个容器里。显示第三个容器。（我的理解可能不对，
英文好的朋友请帮我翻译一个题目，谢谢了。）
*/

//

/*
*/
#include <iostream>
#include <ctime>
#include <iterator>
#include <algorithm>
#include <vector>
//
void print(std::vector<float>& v){
    using namespace std;
    copy(v.begin(),v.end(),ostream_iterator<float>(cout," ") );
    cout<<endl;
}
//
float g(){
    using namespace std;
    return static_cast<float>(rand()/3.2);
}
//
void f(){
    using namespace std;
    clock_t t1=clock();
    const int size=100;
    vector<float> v1(size),v2(size),v3(size);
    generate(v1.begin(),v1.end(),g);
    copy(v1.begin(),v1.end(),v2.begin());
    for( int i=0;i<100;i++){
        v3[i]=v1[i]+v2[i];
    }
    print(v1);
    cout<<endl;
    print(v2);
    cout<<endl;
    print(v3);
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
