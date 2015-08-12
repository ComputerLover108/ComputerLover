#include <iostream>
#include <regex>
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <cstdio>
#include <cstdlib>
#include "boost/lexical_cast.hpp"
#include "boost/thread.hpp"
#include "boost/program_options.hpp"
#include "boost/foreach.hpp"
//
using namespace std;
static bool isDisplay=false;
static bool isImitate=false;
static bool noPattern = false;
//
struct SedFormat {
	string pattern_;
	string replacement_;
	string flag_;
};
//
bool prase(const string s, SedFormat & x)
{
	//cout << __LINE__ << ":" << __FUNCTION__ << "\n";
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
struct Table {
	string oldName_;
	string newName_;
};
//
struct Record{
	unsigned long head_;
	unsigned long last_;
};
//
typedef vector < Record > Cell;
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
		record.head_ = m[0].first-s.begin();
		record.last_ = m[0].second-s.begin();
		t.push_back(record);
		itr = m[0].second;
	}
}
//
void noRecord(const string& s,Cell& t){
	if( t.empty() == true ) return;
	Cell temp;
	Record a={0,0};
	for( auto itr=t.begin();itr != t.end();itr++){
		if( itr->head_ == 0 ) continue;
		if( itr->last_ == 0 ) break;
		
	}
}
//
void rule(const string oldName, const SedFormat& x, Table & y)
{
	//cout << __LINE__ << ":" << __FUNCTION__ << "\n";
	y.oldName_ = oldName;
	y.newName_ = oldName;
	//
	if (x.pattern_.empty())
	return;
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
		if (table.empty())	return;
		long loc = boost::lexical_cast < long >(x.flag_);
		//cout<<__LINE__<<":\t"<<loc<<"\t"<<table.size()<<'\n';
		if (labs(loc) > table.size() ) {
			return;
		}
		if( loc > 0){
			loc--;	
		}
		else if( loc < 0){
			loc += table.size();
		}
		unsigned long position=table[loc].head_;
		unsigned long length=table[loc].last_ - table[loc].head_;
		y.newName_.replace(position,length,x.replacement_);
		return;		
	}
	//

}
//
void threadRename(const Table & y)
{
	if (isImitate == false){
		int c = rename(y.oldName_.c_str(), y.newName_.c_str());
		if (c)
		cerr << "rename " << y.oldName_ << " to " << y.newName_ << "failed!\n";

	}
	if (isDisplay == true)
	cout << y.oldName_ << "\t->\t" << y.newName_ << "\n";
}
//
int main(int argc, char *argv[])
{
	namespace po = boost::program_options;
	try{
		po::options_description desc("Allowed options");
		desc.add_options()
		("help", "produce help message")
		("imitate,I","Imitate progress")
		("verbose,V", "Display progress")
		("rule,R", po::value < string > (),
		"sed rule[s/pattern/replacement/flag]")
		("file-name,F", po::value < string > (), "file name");

		po::positional_options_description p;
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(desc).run(),
		vm);
		po::notify(vm);
		//
		if (vm.count("help")) {
			cout << "Usage: options_description [options]\n";
			cout << desc;
			cout << "\n" <<
			"example:\t sren -R pattern/s/source/result/location" <<
			endl;
			return EXIT_SUCCESS;
		}
		//
		if(vm.count("imitate") ){
			isImitate=true;
			isDisplay=true;
		}
		//
		if (vm.count("verbose")) {
			isDisplay = true;
		}
		//
		string oldName;
		if (vm.count("file-name")) {
			oldName = vm["file-name"].as < string > ();
		}
		//
		SedFormat x;
		if (vm.count("rule")) {
			string s = vm["rule"].as < string > ();
			if (prase(s, x) == false) {
				cerr << "regex error!\n";
				return EXIT_FAILURE;
			}
			Table y;
			rule(oldName, x, y);
			if (y.oldName_ != y.newName_) {
				boost::thread t(threadRename, y);
				t.join();
			}
			//      
		}
		//
	}
	catch( const exception& e){
		cerr<<e.what()<<"\n";
	}
	return EXIT_SUCCESS;
}
