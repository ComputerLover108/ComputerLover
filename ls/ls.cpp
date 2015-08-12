#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <functional>
#include <sstream>
#include <memory>
#include "boost/filesystem.hpp"
#include "boost/progress.hpp"
#include "boost/program_options.hpp"
#include "boost/foreach.hpp"
//
namespace fs = boost::filesystem;
using namespace std;
typedef std::vector<std::string> C;
//

//
size_t dir_size(const std::string fileName){
	using namespace fs;
	//boost::progress_timer t( std::clog );
	size_t ds=0;
	try{
		if (exists(fileName) && is_directory(fileName) )
		{
			for(recursive_directory_iterator itr(fileName);itr!=recursive_directory_iterator();itr++){
				if( !fs::is_directory(*itr) ) ds+=fs::file_size(*itr);
				//if( fs::is_directory(*itr) ) {cout<<dir_size(*itr)<<"\t"<<*itr<<"\n";}
			}			
		}
		
	}
	catch(const filesystem_error& e ){
		std::clog<<e.what()<<"\n";
	};
	return ds;				
}
//
size_t size(const std::string fileName){
	using namespace fs;
	size_t ds=0;
	try{
		if ( exists(fileName) &&is_directory(fileName) )
		{
			ds=dir_size(fileName);
		}
		else{
			ds=fs::file_size(fileName);
		}		
	}
	catch(const filesystem_error& e ){
		std::clog<<e.what()<<"\n";
	};
	return ds;
}
//
void pathList(const string path, C& result) {
	using namespace fs;
	C dir_temp;
	fs::path p(path);
	if (!fs::exists(p))
	{
		std::cout << "\nNot found: " << p << std::endl;
		return ;
	}
	if( p.empty()){
		return ;
	}
	if (fs::is_directory(p) )
	{
		fs::directory_iterator end_iter;
		fs::directory_iterator itr(p);
		while(itr != end_iter)
		{
			if( fs::is_directory( itr->status() ) ){
				//cout<<"dir:\t"<<itr->path().file_string()<<"\n";
				dir_temp.push_back(itr->path().file_string());
			}
			result.push_back(itr->path().file_string());
			itr++;
		}
		BOOST_FOREACH(string item,dir_temp){
			try{
				//cout<<item<<"\n";
				pathList(item,result);
				
			}
			catch(const filesystem_error& e){
				cerr<<e.what()<<"\n";
			}
		}
		
	}

}
//
//
int main(int argc, char *argv[])
{
	using namespace std;
	try {
		boost::progress_timer t( std::clog );
		namespace po = boost::program_options;
		int opt;
		po::options_description desc("Allowed options");
		desc.add_options()
		("","显示当前目录")
		("help,?", "输出帮助")
		("pathName", po::value< vector<string> >(), "输入目录名")
		;

		po::positional_options_description p;
		p.add("pathName", -1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
		options(desc).positional(p).run(), vm);
		po::notify(vm);
		if (vm.count("help")) {
			cout << "Usage: options_description [options]\n";
			cout << desc;
			return 0;
		}		
		//目录列表
		C ss;
		if (vm.count("pathName"))
		{
			const vector<string>& dirs = vm["pathName"].as< vector<string> >();
			for(vector<string>::const_iterator itr=dirs.begin();itr!=dirs.end();++itr){
				pathList(*itr,ss);
			}
		}
		else{
			using namespace boost::filesystem;
			path current_path( initial_path<fs::path>() );
			pathList(current_path.native_file_string(),ss);
		}		
		BOOST_FOREACH(string item,ss){
			cout<<item<<"\n";
		}
	}
	catch(exception& e)
	{
		cout << e.what() << "\n";
		return 1;
	}
	return (0);
}
