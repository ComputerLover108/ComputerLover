/*
�����ѧϰ��������д�㷨�����ֻ��Ӧ����C++��׼��ɣ��ְ�ȫ��Ч����Ư���� 

��Ҫ��һ���ļ�������,�ٴ�ӡ,���ǽ�����Ǵ�261786�������,���λ���ְ�æ�������.
�ļ�:
012452 Wong Andrew 23.56
891756 Simmons Angela 24.94
268174 Tindall Jeremy 18.56
718756 Ting Susan 27.86
261786 Murdock Brian 25.98
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
//
//
class Crecord 
{
	public:
		unsigned int index() const { return m_number;}
		double rate() const { return m_rate; }
	protected: 
		friend std::istream& operator>> (std::istream& in, Crecord& aim);
		friend std::ostream& operator<< (std::ostream& out, const Crecord& source);
	private:
	unsigned int m_number;
	std::string m_last_name;
	std::string m_first_name;
	double m_rate;
};
// The date will be read from a stream in the following form Crecord
std::istream& operator>>(std::istream& in, Crecord& aim){
	using namespace std;
	in>>aim.m_number>>aim.m_last_name>>aim.m_first_name>>aim.m_rate;
	return in;		
}
//
std::ostream& operator<< (std::ostream& out, const Crecord& source){
	using namespace std;
	out<<source.m_number<<"\t"<<source.m_last_name<<"\t"
		<<source.m_first_name<<"\t"<<source.m_rate;
	return out;
}
//
//�����������Զ���Ϊһ��Rule�� 
class Rule : public std::binary_function< Crecord, Crecord, bool >{
	public:
		bool operator() (const Crecord& arg1, const Crecord& arg2)
		{
			//return ( arg1.index() < arg2.index() ); //��ѧ������ 
			return ( arg1.rate() < arg1.rate() ); //���������� 
		}
};
//
int main(int argc, char *argv[])
{
	using namespace std;
	if( 2 == argc ){
		fstream in(argv[1]);
		Crecord record;
		vector<Crecord> ls;
		while( in>>record ){
			ls.push_back(record);
		}
		sort(ls.begin(),ls.end(),Rule() );
		std::copy(ls.begin(),ls.end(),std::ostream_iterator<Crecord>(std::cout,"\n") );
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}
