/**
	Module Name: 

	Description:

	Author: wukexin
	Created:
	Last Change:

	Functions:

*/
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <map>
#include <utility>
//
using namespace std;
//
//
class Rule : public binary_function<const string&,const string&,bool>
{
	public:
	bool operator() (const string& arg1,const string& arg2){
		return ( arg1.length()< arg2.length() ) ? true : false;
	}
};
//
class F : public unary_function< pair<size_t,size_t>,bool >
{
	public:
		F( const pair<size_t,size_t>& val ):m_value(val){}
		bool operator() (const pair<size_t,size_t>& arg ){
			if(m_value.first+1==arg.first && m_value.second+1==arg.second)
			{
				cout<<"["<<m_value.first<<","<<m_value.second<<"] ";
				return true;
			}
			else{
				return false;
			}
		};	
	private:
	pair<size_t,size_t> m_value;
};
//
class Find : public binary_function<string,string,string>
{
	public:
		string operator() (string& arg1,string& arg2){
			//在字符串arg2中，找出字符串arg1里出现的字符，
			//并把它在arg1,arg2里的位置记录在record里
			cout<<arg1<<"\n"<<arg2<<"\n";
			vector<size_t> t1,t2,t3;
			typedef pair<size_t,size_t> Cpair;
			Cpair index;
			vector<Cpair> vp;
			for(size_t i=0;i<arg1.length() ;i++ )
			{
				for(size_t j=0;j<arg2.length() ;j++ )
				{
					if( arg1[i] == arg2[j] ){
						cout<<true;
						index=make_pair(i,j);
						vp.push_back( index );
					}
					else{
						cout<<false;
					}
				}
				cout<<"\n";			
			}
			cout<<"\n";
			vector<Cpair>::iterator itr=vp.begin();
			vector<Cpair>::iterator loc;
			map<size_t,size_t,less<size_t> > vp1;
			for( ;itr != vp.end() ;itr++ )
			{
				loc=find_if(itr,vp.end(),F(*itr));
				if( loc != vp.end() ){
					vp1.insert(*itr);
					vp1.insert(*loc);
				}
			}
 			string guess=do_string(vp1,arg1);
			cout<<"\nguess is "<<guess<<"\n";
			return guess;
		}
	private:
	//把两个字符串中可能是密码字符作成一个新的字符串。
	string do_string(map<size_t,size_t>& C ,const string& source){
		string result;
		map<size_t,size_t>::const_iterator itr=C.begin();
		for(;itr!=C.end();itr++)
		{
			result.push_back( source.at(itr->first) );
		}
		return result;		
	}
};
//
int main(int argc, char *argv[])
{
	using namespace std;
	if( 2 == argc ){
		fstream file(argv[1]);
		string s;
		vector<string> collect;
		while( file >> s){
			collect.push_back(s);
		}
		sort(collect.begin(),collect.end(), Rule() );//按字符串长度排序
		string Init=collect.at(0);
		cout<<"password is "
			<<accumulate(collect.begin()+1,collect.end(),Init,Find() )
			<<endl;
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}
