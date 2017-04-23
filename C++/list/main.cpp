#include "../wukexin/file/file_info.h"
#include "../wukexin/file/file.h"
//#include "../wukexin/help/help.h"
//
#include "boost/program_options.hpp"
#include "boost/progress.hpp"
#include "boost/filesystem.hpp"
#include "boost/bind.hpp"
#include "boost/date_time.hpp"
//#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost;
namespace po = boost::program_options;

#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <bitset>
using namespace std;
//
namespace fs = boost::filesystem;
typedef vector<string> C;

// A helper function to simplify the main part.

struct IsFileAttributes : public binary_function<const DWORD,const string,bool>{
	bool operator() (const DWORD aim,const string fname){
		using namespace wukexin;
		DWORD attrib=GetFileAttributes(fname.c_str() );
		//static unsigned limit=32;
		bitset<32> ba(aim),bf(attrib);
		unsigned condition=ba.count();
		unsigned success_count(0);
		for(unsigned i=0;i<32;i++){
			if( ba.test(i) && bf.test(i) ) success_count++;
		}
		if( success_count == condition )
		return true;
		else
		return false;
	}
};
//
enum SelecFileTime{create,write,access};
//

bool isFileTime(const SelecFileTime x,const string ftime,string fname){
	//boost::progress_timer t( std::clog );
	bool result=false;
	try{
		wukexin::Cfile_information file(fname);
		string ftime2;
		if( create == x ) ftime2=file.cFileTime();
		if( write == x )  ftime2=file.wFileTime();
		if( access== x )  ftime2=file.aFileTime();
		using namespace boost::gregorian;
		using namespace boost::posix_time;
		/*
	{
		ptime t1(time_from_string(ftime) );
		ptime t2(time_from_string(ftime2) );
		if(
		//cout<<ftime<<"\t"<<to_iso_extended_string(t1)<<"\t"<<to_iso_extended_string(t2)<<"\n";
	}
	*/
		if( ftime.length() <= 10 ){
			date d1( from_string(ftime) );
			date d2( from_string(ftime2) );
			if( d1 == d2 ) result=true;
		}
	//cout<<"isFileTime("<<x<<","<<ftime<<","<<ftime2<<"\n"<<fname<<")="<<result<<"\n";
	}
	catch( exception& e){
		clog<<e.what()<<"\n";
	}
	return result;
}

//
void pathList(const std::string fileName,C& result){
	using namespace std;
	using namespace fs;
	//boost::progress_timer t( std::clog );
	try{
		if (exists(fileName) && is_directory(fileName) )
		{
			transform(recursive_directory_iterator(fileName), recursive_directory_iterator(),
			back_inserter(result),mem_fun_ref(path::native_file_string)
			);
		}
	}
	catch(const filesystem_error& e ){
		std::clog<<e.what()<<"\n";
	};
}
//
void print(const string fname){
	cout<<fname<<"\n";
}
//
void display(const string fname){
	using namespace fs;
	wukexin::Cfile_information file(fname );
	file.print();
}
//
int main(int ac, char* av[])
{
	try {
		boost::progress_timer t( std::clog );
		namespace po = boost::program_options;
		int opt;
		po::options_description desc("Allowed options");
		desc.add_options()
		("","显示当前目录")
		("help,?", "输出帮助")
		("pathName", po::value< vector<string> >(), "输入目录名")
		//筛选指定文件属性
		("attributes,A",po::value<string>(),"显示指定熟性文件")
		("create_time",po::value< string >(),"[C]  创建时间( \t 例如: 1997-12-31)" )
		("last_access_time",po::value< string >(),"上次访问时间( \t 例如: 12:02:53)" )
		("last_write_time,T",po::value< string >(),"上次写入的时间( \t 例如: 2002-01-19 1:1:1)")
		//
		("complete,C","详细显示目录")
		;

		po::positional_options_description p;
		p.add("pathName", -1);

		po::variables_map vm;
		po::store(po::command_line_parser(ac, av).
		options(desc).positional(p).run(), vm);
		po::notify(vm);

		if (vm.count("help")) {
			cout << "Usage: options_description [options]\n";
			cout << desc;
			return 0;
		}
		//目录列表
		C fileList;
		//
		if (vm.count("pathName"))
		{
			const vector<string>& dirs = vm["pathName"].as< vector<string> >();\
			for(vector<string>::const_iterator itr=dirs.begin();itr!=dirs.end();++itr){
				pathList(*itr,fileList);
			}
		}
		else{
			using namespace boost::filesystem;
			path current_path( initial_path<fs::path>() );
			pathList(current_path.native_file_string(),fileList);
		}
		//
		if(vm.count("attributes") ){
			string sattribs = vm["attributes"].as<string>();
			DWORD attrib = wukexin::stringToAttrib(sattribs);
			erase_if(fileList,!boost::bind(IsFileAttributes(),attrib,_1) );
		}
		//
		if(vm.count("create_time") ){
			string sftime = vm["create_time"].as< string >();
			erase_if(fileList,!boost::bind(isFileTime,create,sftime,_1) );
		}
		if(vm.count("last_access_time") ){
			string sftime = vm["last_access_time"].as< string >();
			erase_if(fileList,!boost::bind(isFileTime,access,sftime,_1) );
		}
		if(vm.count("last_write_time") ){
			string sftime = vm["last_write_time"].as< string >();
			erase_if(fileList,!boost::bind(isFileTime,write,sftime,_1) );
		}
		if (vm.count("complete") ){
			for_each(fileList.begin(),fileList.end(),display);
			cout<<"There are "<<fileList.size()<<" objects.\n";
			return 0;
		}
		//缺省输出结果
		//desc.print(cout);
		for_each(fileList.begin(),fileList.end(),print);
		clog<<"There are "<<fileList.size()<<" files and directories.\n";
	}
	catch(exception& e)
	{
		clog << e.what() << "\n";
		return 1;
	}
	return 0;
}
