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
exercise2_10:
Creat a vector<float> and put 25 elements into it as in the previous exercises.
Now square each number and put the result into the same location in the vector.
Display the vector before and after the multiplication.
像上个练习一样，产生一个浮点数容器，并放置25各元素在里面。现在平方每个元素并把
结果放置回原来的位置。在乘法前和后分别显示容器内容。
*/

//

/*
*/
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iterator>
//
void print(std::vector<float>& v){
    using namespace std;
    copy( v.begin(), v.end(), ostream_iterator<float>(cout," ") );
    cout<<endl;
}
//
float g(){
    using namespace std;
    const float PI = 3.1415926;
    return ( rand()/PI );
}
//
void square(float& x){
    float result=x;
    x = result * result;
}
//
void f(){
    using namespace std;
    clock_t t1 = clock();
    vector<float> v(25);
    generate( v.begin(),v.end(),g );
    cout<<"Before multiplication.\n"<<endl;
    print(v);
    //本想用 generate,可是用不好，有人可以说说他吗。
    for_each( v.begin(), v.end(), square );
    cout<<"After multiplication.\n"<<endl;
    print(v);
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
