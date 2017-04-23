/*
题：定义一个ACCP学员的成绩结构：4次内测占30%，结业笔试占10%，结业机试占10%，项目设计占20%，出勤率占10%，综合素质占20%。

实现要求：
定义一个函数： struct score input( )
实现对一个学员成绩的输入
定义一个函数：void display(struct score stud[])
实现对学员信息的输出，要求以格式化输出
定义一个函数：void sort(struct score stud[])
实现对学员信息的排序
在主函数中，采用提示方式调用input()函数来输入学员成绩，输入完成后调用display()函数来输出所有学员成绩信息，调用sort()函数按最终成绩的降序排序学员成绩信息，排序后调用display()函数输出排序的后的成绩信息
用函数不会
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

const int NUMBER=4;
//
class Cscore
{
	public:
	Cscore();
	~Cscore();
	void input();
	void print() const;
	std::string name() const ;
	float count() const;//总成绩 
	protected:
	friend class Crule_sort;
	private:
	std::string m_name;
	std::string m_sex;
	float m_jishi;
	float m_bishi;
	float m_xiangmu;
	float m_chuqing;
	float m_zhonghe[NUMBER];
	float m_zhonghel;	
};
Cscore::Cscore(){ input(); }
Cscore::~Cscore(){}
void Cscore::input() {
	using namespace std;
	{
		cout<<"学生姓名：";
		cin>>m_name;
		cout<<"姓别：";
		cin>>m_sex;
		cout<<"机试成绩：";
		cin>>m_jishi;
		cout<<"笔试成绩：";
		cin>>m_bishi;
		cout<<"项目成绩：";
		cin>>m_xiangmu;
		cout<<"出勤成绩：";
		cin>>m_chuqing;
		for(int i=0;i<NUMBER ;i++ )
		{
			cout<<"第"<<i+1<<"次内测成绩为:";
			cin>>m_zhonghe[i];
		}
		cout<<"综合成绩：";
		cin>>m_zhonghel;
	};
};
void Cscore::print() const{
		using namespace std;
		cout<<"学生姓名："<<m_name
			<<"\t姓别："<<m_sex
			<<"\t机试成绩："<<m_jishi
			<<"\t笔试成绩："<<m_bishi
			<<"\t项目成绩："<<m_xiangmu
			<<"\t出勤成绩："<<m_chuqing;
		for(int i=0;i<NUMBER ;i++ )
		{
			cout<<"\t第"<<i+1<<"次内测成绩为:"<<m_zhonghe[i];
		}
		cout<<"综合成绩："<<m_zhonghel<<"\n";
};
//
std::string Cscore::name() const {
	return m_name;
}
//
float Cscore::count() const{
		float sum=0,result=0;
		for(int i=0;i<NUMBER ;i++ )
		{
			sum+=m_zhonghe[i];
		}
		result=sum*0.3+m_jishi*0.1+m_bishi*0.1+m_xiangmu*0.2+m_chuqing*0.1+m_zhonghel*0.2;
		return result;
}
//
class Crule_sort : std::binary_function < Cscore,Cscore,bool>
{
	public:
	bool operator() (const Cscore& arg1,const Cscore& arg2){
		return rule(arg1)<rule(arg2);
	}
	private:
	float rule(Cscore& x){
		return x.count();//排序规则可以自定义 
	}	
};
//
void display(const std::vector<Cscore>& v){
	using namespace std;
	vector<Cscore>::const_iterator itr=v.begin();
	for( ; itr!=v.end(); itr++){
		itr->print();
	}
}
//
int main()
{
	using namespace std;
	const int MAX=3;
	vector<Cscore> v(MAX);
	for(unsigned int i=0;i<v.size();i++){
		cout<<"学号"<<i<<"\n";
		Cscore student;
		v[i]=student;
	}
	display(v);
	sort( v.begin(),v.end(),Crule_sort() );
	display(v);
	vector<Cscore>::const_iterator itr=max_element(v.begin(),v.end(),Crule_sort() );
	float sum=0;//学生成绩汇总
	for(unsigned int i=0;i<v.size();i++)
	{
		sum+=v[i].count();
	}
	cout<<"最佳成绩:"<<itr->count()
		<<"姓名："<<itr->name()
		<<"平均成绩："<<sum/MAX
		<<"\n";
	return 0;
}
