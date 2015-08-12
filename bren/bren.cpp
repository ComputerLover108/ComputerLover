#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"
#include "boost/progress.hpp"
#include "boost/foreach.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/thread.hpp"
// 
#include <iostream>
#include <functional>
#include <regex>
#include <vector>
#include <string>
#include <memory>
// 
using namespace std;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
//
static bool isDisplay = false;
static bool isImitate = false;
static bool noPattern = false;
//
typedef vector < string > Container;
void pathList(const string& path, Container& fileList,unsigned long maxdepth=0);
// 
struct SedFormat {
	string pattern_;
	string replacement_;
	string flag_;
};
bool prase(const string& s, SedFormat & x);
// 
struct Table {
	string oldName_;
	string newName_;
};
void rule(const string& oldName, const SedFormat & x, Table & y);
void newName(const std::vector<std::string>& invariant,unsigned long index,string& name);
void threadRename(const Table & table);
//
struct Record {
	long location_;
	unsigned long length_;
};
//
typedef vector < Record > Cell;
void record(const string & s, const string & pattern, Cell & t);
//
bool cmp(const Record& a, const Record& b);
void noRecord(const string& s, Cell& t);
// 
int main(int argc, char *argv[])
{
	//cout<<__LINE__<<":"<<__FUNCTION__<<"\n";
	try{
		boost::progress_timer t(clog);
		namespace po = boost::program_options;
		//int opt;
		po::options_description desc("Allowed options");
		desc.add_options()
		("help,?", "�������")
		("verbose,V", "��ʾ����ִ�����")
		("imitate,I", "�������ִ���ļ����޸ģ�ֻ��ģ����ʾ")
		("maxdepth,M",po::value <unsigned long>() ,"������Ŀ¼������")
		("directory,D", po::value < vector < string > >(), "����Ŀ¼��")
		("filter,F",po::value < string > (), "ɸѡ�ض��ļ������ļ�")
		("prefix,P", po::value < string > (), "�޸��ļ�����ǰ׺")
		("begin",po::value <unsigned long> (),"��ĳ��ʼ��ţ���ϡ�prefix��һ��ʹ�ã�")
		("rule,R", po::value < string > (),
		"���޸ķ���s/ƥ��Ŀ��/�滻/λ��")
		;
		//
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
		po::notify(vm);
		//
		if (vm.count("help")) {
			cout			// <<"����һ�������������������ʽ����:\n
			// bren -Dir d:\picture -prefix ��Ů\n"
			// <<"�����d:\backup\��Ů1.jpg \n d:\backup\��Ů2.jpg
			// ......\n"
			<< "Usage: options_description [options]\n" << desc
			<<"���޸ķ���s/ģʽ/�滻/λ��\n"
			<<"��ģʽ�滻���滻��ƥ���ģʽ����!s/ģʽ/�滻/λ��[����������]\n"		
			;
			return EXIT_SUCCESS;
		}
		//
		if (vm.count("verbose")) {
			isDisplay = true;
		}
		//
		if (vm.count("imitate")) {
			isImitate = true;
			isDisplay = true;
		}	
		//
		unsigned long limitDepth=0;
		if (vm.count("maxdepth") ){
			limitDepth = vm["maxdepth"].as <unsigned long>();
		}
		// Ŀ¼�б�
		Container fileList;
		// 
		if (vm.count("directory")) {
			const Container& dirs = vm["directory"].as < Container > ();
			if( dirs.empty() == true ) return EXIT_FAILURE;
			BOOST_FOREACH(string fname , dirs) {
				pathList(fname, fileList,limitDepth);
			}
		}
		else{
			fs::path p=fs::current_path();
			string DefaultDir = p.string();
			//cout<<"Current path is "<< 	DefaultDir <<"\n"; 
			pathList(DefaultDir,fileList,limitDepth);
		}
		//
		if (vm.count("filter") ){
			string filter=vm["filter"].as< string > ();
			regex re(filter);
			Container v;
			BOOST_FOREACH( string fname , fileList){
				if( regex_match(fname,re) ) v.push_back(fname);
				clog<<fname<<"\t"<<filter<<"\t"<<regex_match(fname,re)<<"\n";
			}
			fileList.swap(v);
		}
		//	
		if (vm.count("prefix")) {
			string prefix = vm["prefix"].as < string > ();
			sort(fileList.begin(),fileList.end() );//
			unsigned long index = 0;
			if( vm.count("begin") ){
				index = vm["begin"].as <unsigned long> ();
			}
			string temp = boost::lexical_cast < string > (fileList.size());
			const unsigned int FormatLength = temp.length();
			string ss(FormatLength, '0');
			Table table;
			Container vc;
			string name;
			for(unsigned long index=0;index < fileList.size();index++){
				fs::path dir( fileList[index] );
				string extension = dir.extension().string();
				std::vector<std::string> invariant;
				invariant.push_back(prefix);
				invariant.push_back(extension);
				invariant.push_back(ss);
				newName(invariant,index,name);
				vc.push_back(name);
				cout<<"+"<<fileList[index]<<"<-->\t-"<<name<<"\n";
			}
			assert( vc.size() == fileList.size() );
			cout<<"begin\t"<<fileList.size()<<"\t"<<vc.size()<<"\n";
			Container t1,t2;
			back_insert_iterator< Container > bi1(t1);
			set_difference(fileList.begin(),fileList.end(),vc.begin(),vc.end(),bi1);
			swap(fileList,t1);
			BOOST_FOREACH(string name,fileList){
				cout<<"+"<<name<<"\n";
			}
			back_insert_iterator< Container > bi2(t2);
			set_difference(vc.begin(),vc.end(),fileList.begin(),fileList.end(),bi2);
			swap(vc,t2);
			BOOST_FOREACH(string s,vc){
				cout<<"-"<<s<<"\n";
			}
			assert( fileList.size() == vc.size() );
			cout<<"after\t"<<fileList.size()<<"\t"<<vc.size()<<"\n";
			Container::iterator itr1=fileList.begin();
			Container::iterator itr2=vc.begin();
			while( itr1 != fileList.end() ) {
				table.oldName_ = *itr1;
				table.newName_ = *itr2;
					if (table.oldName_ != table.newName_) {
						boost::thread t(threadRename, table);
						t.join();
					}
				++itr1;
				++itr2;
			}
			return EXIT_SUCCESS;
		}
		// 
		if (vm.count("rule")) {
			// using namespace boost;
			string s = vm["rule"].as < string > ();
			string sed("!?s/.*/.*/(-?[0-9]*|[aig])");
			regex re(sed);
			if (!regex_match(s, re)) {
				clog << "������޸ķ���!\n" <<
				"���޸ķ���s/ģʽ/�滻/λ��\n"
				"��ģʽ�滻���滻��ƥ���ģʽ����!s/ģʽ/�滻/λ��[����������]\n";
				return EXIT_FAILURE;
			}
			SedFormat r;
			if (prase(s, r) == false) {
				cout << __LINE__ << ":" << __FUNCTION__ << "\n";
				return EXIT_FAILURE;
			}
			regex e(r.pattern_);
			Table table;
			BOOST_FOREACH(string fileName, fileList) {
				rule(fileName, r, table);
				if (table.oldName_ != table.newName_) {
					boost::thread t(threadRename, table);
					t.join();
				}
			}
		}
		//
	}
	catch( const std::exception& e){
		cerr<<e.what()<<"\n";
	}
	return EXIT_SUCCESS;
}

// 
void pathList(const string& path, Container& result,unsigned long maxdepth){
	using namespace fs;
	try{
		fs::path p(path);
		if (p.empty()) 	return;
		if (fs::is_directory(p)) {
			fs::recursive_directory_iterator end_iter;
			fs::recursive_directory_iterator itr(p);
			while (itr != end_iter) {
				result.push_back(itr->path().string());
				if( fs::is_directory(*itr) ){
					try{
						fs::directory_iterator dir(*itr);
					}
					catch( const filesystem_error& e){
						clog<<__LINE__<<":"<<e.what()<<"\n";
						itr.no_push();
					}
				}
				if( itr.level() == maxdepth ) itr.no_push();
				++itr;
			}
		}
	}
	catch( const filesystem_error& e){
		clog<<__LINE__<<":"<<e.what()<<"\n";
	}
}
//
bool prase(const string& s, SedFormat & x)
{
	//cout << __LINE__ << ":" << __FUNCTION__ << "\n";
	if( s[0]=='!' ) noPattern=true;
	const char FLAG = '/';
	auto itr1 = find(s.begin(), s.end(), FLAG);
	auto itr2 = find(itr1 + 1, s.end(), FLAG);
	auto itr3 = find(itr2 + 1, s.end(), FLAG);
	string pattern(++itr1, itr2);
	string replaced(++itr2, itr3);
	string flag(++itr3, s.end());
	x.pattern_ = pattern;
	x.replacement_ = replaced;
	x.flag_ = flag;
	//
	return true;
}

//
void record(const string & s, const string & pattern, Cell & t)
{
	auto itr = s.begin();
	auto end = s.end();
	smatch m;
	regex re(pattern);
	Record record;
	while (regex_search(itr, end, m, re)) {
		if (m.empty())
		break;
		record.location_ = m[0].first - s.begin();
		record.length_ = m[0].second - m[0].first;
		t.push_back(record);
		itr = m[0].second;
		//cout<<s<<"\t"<<record.location_<<"\t"<<record.length_<<"\t"<<m[0]<<"\n";
	}
}
//
bool cmp(const Record& a, const Record& b){
	return ( a.location_ < b.location_ );
}
//
void noRecord(const string& s,Cell& t){
	//clog<<__LINE__<<":"<<__FUNCTION__<<"\n";
	if( t.empty() == true ){
		return;
	}
	Cell x(2);
	auto head=x.begin();
	auto end= x.end();
	--end;//ָ�����һ��Ԫ��
	auto itr=t.begin();
	auto endItr= t.end();
	--endItr;//ָ�����һ��Ԫ��	
	unsigned long last = endItr->location_ + endItr->length_ ;
	//
	if( last == s.length() ){
		x.erase(end);
		end=head;
	}
	else{ 
		end->location_ = last;
		end->length_ = s.length() -last;
	}
	//
	if( itr->location_ == 0 ){
		x.erase(head);
	}
	else
	{
		head->location_ = 0;
		head->length_ = itr->location_;
	}
	//
	Record a;
	while( itr != endItr){
		a.location_ = itr->location_ + itr->length_ ;
		++itr;
		a.length_ = itr->location_-a.location_;
		if(a.length_ == 0 ) continue;
		x.push_back(a);		
	}
	sort( x.begin(),x.end(),cmp );
	t.swap(x);
}
//
void rule(const string& oldName, const SedFormat & x, Table & y)
{
	//cout << __LINE__ << ":" << __FUNCTION__ << "\n";
	y.oldName_ = oldName;
	y.newName_ = oldName;
	//
	if (x.pattern_.empty())	return;
	//
	regex re(x.pattern_);
	//
	if (x.flag_.empty()) {
		y.newName_ = regex_replace(oldName, re, x.replacement_,
		regex_constants::format_first_only);
		return;
	}
	//
	string fm = "$&";
	regex rf("[aig]");
	if (regex_match(x.flag_, rf)) {
		if ("a" == x.flag_)
		fm += x.replacement_;
		if ("i" == x.flag_)
		fm = x.replacement_ + fm;
		if ("g" == x.flag_)
		fm = x.replacement_;
		y.newName_ = regex_replace(oldName, re, fm);
		// cout<<fm<<"\t"<<oldName<<"\t->"<<newName<<"\n";
		return;
	}
	//
	regex rn("-?[0-9]*");
	if (regex_match(x.flag_, rn)) {
		Cell table;
		record(oldName, x.pattern_, table);
		if( noPattern == true ){
			noRecord(oldName,table);		
		}
		if (table.empty())
		return;
		long loc = boost::lexical_cast < long >(x.flag_);
		//cout<<__LINE__<<":\t"<<loc<<"\t"<<table.size()<<'\n';
		if (labs(loc) > table.size() ) {
			return;
		}
		if (loc > 0) {
			loc--;
		}
		else if (loc < 0) {
			loc += table.size();
		}
		y.newName_.replace(table[loc].location_,table[loc].length_, x.replacement_);
		return;		
	}
	//
}
//
void newName(const std::vector<std::string>& invariant,unsigned long index,string& name){
				string ss=invariant[2];
				string s = boost::lexical_cast < string > (index);
				if (s.length() <= ss.length() ) {
					ss.replace(ss.length() - s.length(), s.length(), s);
				}
				else{
					ss = s;
				}
				string prefix=invariant[0];
				string extension=invariant[1];
				name = prefix+ss+extension;
}
//
void threadRename(const Table & table)
{
	using namespace fs;
	try {
		if (isImitate == false)
		rename(table.oldName_, table.newName_);
		if (isDisplay == true)
		cout<< table.oldName_ << "\t->\t" << table.newName_ << "\n";
	}
	catch(const filesystem_error & e) {
		cerr << e.what() << "\n";
	}
}

//
