/*
在Neutronia王国，货币单位是tvarp，收入所得税的计算方式如下：
5000 tvarps: 不收税
5001－15000 tvarps: 10%
15001-35000 tvarps: 15%
35000 tvarps以上: 20%
例如，某人的收入为38000 tvarps，则其所得税为5000×0.00＋10000×0.10＋20000×0.15＋3000×0.20，即4600 tvarps。
请编写一个程序，使用循环来要求用户输入收入，并报告所得税。当用户输入负数或非数字时，循环将结束。
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
		cout<<"\n这是一个计算个人所得税的小程序。\n"
			<<"请输入收税规则：\n"
			<<"例如，5000 元: 不收税\n" 
			<<"5001－15000 元: 10%\n"
			<<"15001-35000 元: 15%\n"
			<<"35000 元以上: 20%\n"
			<<"表示为：" 
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
