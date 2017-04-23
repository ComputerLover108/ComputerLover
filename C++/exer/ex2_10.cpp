/*
    learning C++(homework) ѧϰC++�ʼǡ�
    ����һ�����԰����ߣ�ϣ���ҵ�־ͬ���ϵ����ѣ������ҵļ�ͥ��ҵ��ϣ�����˺���
    һ��ѧϰ����ָ���ҵĴ���Ͳ��㡣�ҷ������ϵ����ۣ�����̫�򵥣�����̫���ˣ�
    ��������һ�����ʵģ��������ѵ�ˮ���㵽��ֹ��������ϣ�����ҵ�ѧϰ���̣���ϸ
    �Ĵ�ӡ���������Һͳ�ѧ�߶������档���ܸտ�ʼ�ر�򵥣�������Ϊ����ѧϰ��
    �����Խ��Խ�ѵģ���Ϊ����Ϊ C++ ��ĺ��ѣ������õĻ������Ǳ�ѧ�ˡ��ҵ�
    Ӣ�ĺʹ���ˮƽ��һ�㣬���д�����ָ����лл��ҡ�
*/
/*
        Think in c++ second version (homework)
        (author: wukexin)
        C++ ���˼�루�ڶ��棩����ͥ��ҵ��
        �����ߣ������Σ�

*/
//

/*
exercise2_10:
Creat a vector<float> and put 25 elements into it as in the previous exercises.
Now square each number and put the result into the same location in the vector.
Display the vector before and after the multiplication.
���ϸ���ϰһ��������һ��������������������25��Ԫ�������档����ƽ��ÿ��Ԫ�ز���
������û�ԭ����λ�á��ڳ˷�ǰ�ͺ�ֱ���ʾ�������ݡ�
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
    //������ generate,�����ò��ã����˿���˵˵����
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
