/*
定义一个结构，用来保存学员的信息，包括：学号，姓名，C课程成绩，JAVA成绩，
编写一个程序，用来接收五位学生的信息，计算每位学员的平均成绩并显示详细信息，计算平均成绩的功能通过函数实现!!!
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
using namespace std;
//
class Crecord  
{
	public:
		//Crecord(size_t arg1,string arg2,vector<double> arg3);
		//~Crecord(){};
		size_t index(){return m_index;};
		string name(){return m_name;};
		double average_score();	 
	//protected:
		friend istream& operator>> (istream& in, Crecord& aim);
		friend ostream& operator<< (ostream& out, const Crecord& source);
	private:
		size_t m_index;
		string m_name;
		vector<double> m_scores;
};
//
double Crecord::average_score(){
	double init_value=0;
	double result=accumulate(m_scores.begin(),m_scores.end(),init_value)/m_scores.size();
	return result;
}
//
istream& operator>> (istream& in, Crecord& aim){
	string s;
	getline(in,s);
	stringstream is(s);
	size_t t1;
	string t2;
	is>>t1>>t2;
	aim.m_index=t1;
	aim.m_name=t2;
	double temp;
	aim.m_scores.clear();
	while(is>>temp){
		aim.m_scores.push_back(temp);
	}
	return in;
};
//
ostream& operator<< (ostream& out, const Crecord& source){
	out<<source.m_index<<"\t"<<source.m_name<<"\t";
	vector<double>::const_iterator itr=source.m_scores.begin();
	for(;itr!=source.m_scores.end() ;itr++ )
	{
		out<<*itr<<" ";
	}
	return out;
};
//
int main(int argc, char *argv[])
{
	if( 2 == argc ){
		fstream file(argv[1]);
		Crecord record;
		vector<Crecord> vc;
		vc.clear();
		while( file >> record ){
			vc.push_back(record);
		}
		for(size_t i=0;i<vc.size() ;i++ )
		{
			cout<<vc.at(i)<<"\taverage score: "<<vc.at(i).average_score()<<"\n";
		}
	}
	return EXIT_SUCCESS;
}
