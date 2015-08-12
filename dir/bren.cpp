#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <sstream>
#include <vector>
#include "boost/filesystem.hpp"
#include "boost/progress.hpp"
#include "boost/program_options.hpp"

namespace fs = boost::filesystem;
using namespace std;

void pathList(const std::string fileName,std::ostream& ss){
	using namespace std;
	using namespace fs;
	//boost::progress_timer t( std::clog );
	try{
		if (exists(fileName) && is_directory(fileName) )
		{
			transform(recursive_directory_iterator(fileName), recursive_directory_iterator(),
			ostream_iterator<string>(ss,"\n"),
			mem_fun_ref(path::native_file_string)
			);
		}
	}
	catch(const filesystem_error& e ){
		std::clog<<e.what()<<"\n";
	};
}
//

int main(int argc,char* argv[])
{
	using namespace std;
	try {
		boost::progress_timer t( std::clog );
		namespace po = boost::program_options;
		int opt;
		po::options_description desc("Allowed options");
		desc.add_options()
		("help,?", "批量修改文件名，例：bren d:\backup -A wkx -R WKX")
		("pathName", po::value< vector<string> >(), "输入目录名")
		("aim,A",po::value<string>(),"修改目标")
		("replace,R",po::value<string>(),"修改结果 ")
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
		stringstream ss;
		string aim,replace;
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
		if(vm.count("aim") ){
			aim=vm["aim"].as<string>();
		}
		if(vm.count("replace") ){
			replace=vm["replace"].as<string>();
		}
		string old_filename,new_filename;
		while( getline(ss,old_filename) ){
				new_filename=old_filename;
				unsigned int index=new_filename.find(aim,0);
				if(index!=string::npos){
					new_filename.replace(index,aim.length(),replace);
					if(fs::is_regular_file(old_filename) ){
						fs::rename(old_filename,new_filename);
					}
				cout<<old_filename<<"\t"<<new_filename<<"\n";	
				}			
		}
		//


	}
	catch(exception& e)
	{
		cout << e.what() << "\n";
		return 1;
	}
	return 0;
}
