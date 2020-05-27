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
exercise2_9:
Creat three vector<float> objects and fill the first two as in the previous.
Write a for loop that adds each corresponding element in the first two vectors
and puts the result in the corresponding element of the third vector. Display
all three vectors.
�������������������������ϸ���ϰһ�����ͷ����������дһ��for ѭ�������Ӧ��Ԫ��
��ͷ���������У����ѽ�����ڵ������������ʾ���������������ҵ������ܲ��ԣ�
Ӣ�ĺõ���������ҷ���һ����Ŀ��лл�ˡ���
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
