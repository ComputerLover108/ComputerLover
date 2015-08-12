/*
��Neutronia���������ҵ�λ��tvarp����������˰�ļ��㷽ʽ���£�
5000 tvarps: ����˰
5001��15000 tvarps: 10%
15001-35000 tvarps: 15%
35000 tvarps����: 20%
���磬ĳ�˵�����Ϊ38000 tvarps����������˰Ϊ5000��0.00��10000��0.10��20000��0.15��3000��0.20����4600 tvarps��
���дһ������ʹ��ѭ����Ҫ���û��������룬����������˰�����û����븺���������ʱ��ѭ����������
*/
/**
	Module Name: 

	Description:

	Author:wukexin
	Created:
	Last Change:

	Functions:

*/
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
using namespace std;
//
double rule_tax(double income,double tax_level,double tax_rate){
	double result(0);
	if( income >= tax_level	 ){
		 result = (income-tax_level)*tax_rate;
	}
	return result;
}
//
class Ctax_rule {
	public:
		Ctax_rule(double x=0,double y=0):m_x(x),m_y(y){}
	protected:
		friend istream& operator>> (istream& in, Ctax_rule x);
		friend ostream& operator<< (ostream& out,const Ctax_rule x);
	private:
		double m_x,m_y;
};
//
istream& operator>> (istream& in,Ctax_rule arg){
	in>>arg.m_x>>arg.m_y;
	cout<<arg.m_x<<","<<arg.m_y<<" ";
	return in;
}
//
ostream& operator<< (ostream& out,const Ctax_rule arg	){
	out<<"["<<arg.m_x<<","<<arg.m_y<<"]";
	return out;
}
//
int main(int argc,char* argv[])
{
	if( argc == 1){
		cout<<"\n����һ�������������˰��С����\n"
			<<"��������˰����\n"
			<<"���磬5000 Ԫ: ����˰\n" 
			<<"5001��15000 Ԫ: 10%\n"
			<<"15001-35000 Ԫ: 15%\n"
			<<"35000 Ԫ����: 20%\n"
			<<"��ʾΪ��" 
			<<"35000,0.2 15000,0.15 5000,0.1\n";
			Ctax_rule x;
			vector<Ctax_rule> vc;
			while(cin >> x){
				vc.push_back(x);
			}
			copy(vc.begin(),vc.end(),ostream_iterator<Ctax_rule>(cout," ") );
	}
	double income(0);
	do{
		cout<<"Please input your income: ";
		cin>>income;
		//cout<<"Your income tax is "<<tax(income)<<endl;	
	}while(income > 0);
	return EXIT_SUCCESS;
}
