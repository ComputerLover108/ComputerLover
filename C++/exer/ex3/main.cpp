/*
�⣺����һ��ACCPѧԱ�ĳɼ��ṹ��4���ڲ�ռ30%����ҵ����ռ10%����ҵ����ռ10%����Ŀ���ռ20%��������ռ10%���ۺ�����ռ20%��

ʵ��Ҫ��
����һ�������� struct score input( )
ʵ�ֶ�һ��ѧԱ�ɼ�������
����һ��������void display(struct score stud[])
ʵ�ֶ�ѧԱ��Ϣ�������Ҫ���Ը�ʽ�����
����һ��������void sort(struct score stud[])
ʵ�ֶ�ѧԱ��Ϣ������
���������У�������ʾ��ʽ����input()����������ѧԱ�ɼ���������ɺ����display()�������������ѧԱ�ɼ���Ϣ������sort()���������ճɼ��Ľ�������ѧԱ�ɼ���Ϣ����������display()�����������ĺ�ĳɼ���Ϣ
�ú�������
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
	float count() const;//�ܳɼ� 
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
		cout<<"ѧ��������";
		cin>>m_name;
		cout<<"�ձ�";
		cin>>m_sex;
		cout<<"���Գɼ���";
		cin>>m_jishi;
		cout<<"���Գɼ���";
		cin>>m_bishi;
		cout<<"��Ŀ�ɼ���";
		cin>>m_xiangmu;
		cout<<"���ڳɼ���";
		cin>>m_chuqing;
		for(int i=0;i<NUMBER ;i++ )
		{
			cout<<"��"<<i+1<<"���ڲ�ɼ�Ϊ:";
			cin>>m_zhonghe[i];
		}
		cout<<"�ۺϳɼ���";
		cin>>m_zhonghel;
	};
};
void Cscore::print() const{
		using namespace std;
		cout<<"ѧ��������"<<m_name
			<<"\t�ձ�"<<m_sex
			<<"\t���Գɼ���"<<m_jishi
			<<"\t���Գɼ���"<<m_bishi
			<<"\t��Ŀ�ɼ���"<<m_xiangmu
			<<"\t���ڳɼ���"<<m_chuqing;
		for(int i=0;i<NUMBER ;i++ )
		{
			cout<<"\t��"<<i+1<<"���ڲ�ɼ�Ϊ:"<<m_zhonghe[i];
		}
		cout<<"�ۺϳɼ���"<<m_zhonghel<<"\n";
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
		return x.count();//�����������Զ��� 
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
		cout<<"ѧ��"<<i<<"\n";
		Cscore student;
		v[i]=student;
	}
	display(v);
	sort( v.begin(),v.end(),Crule_sort() );
	display(v);
	vector<Cscore>::const_iterator itr=max_element(v.begin(),v.end(),Crule_sort() );
	float sum=0;//ѧ���ɼ�����
	for(unsigned int i=0;i<v.size();i++)
	{
		sum+=v[i].count();
	}
	cout<<"��ѳɼ�:"<<itr->count()
		<<"������"<<itr->name()
		<<"ƽ���ɼ���"<<sum/MAX
		<<"\n";
	return 0;
}
