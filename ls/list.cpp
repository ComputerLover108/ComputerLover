//
//#include <cstdio>
//#include "windows.h"
//
//#include "ezlogger_headers.hpp"
//
#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "boost/progress.hpp"
#include "boost/bind.hpp"
#include "boost/foreach.hpp"
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
//
namespace fs = boost::filesystem;
using namespace std;
using namespace fs;
//
bool isDir( const std::string fileName){
	return fs::is_directory(fileName);
}
//
typedef std::deque<std::string> Container;
Container errorMessage; 
//
enum Status { INFINITE,DEPTH,MINDEPTH,MAXDEPTH };
struct Controller {
	Status status_;
	int depth_;
};
//
void pathList(const std::string& pathName,const Controller& c,Container& result);
//
int main(int argc, char* argv[])
{
	using namespace std;
	try{
		namespace po = boost::program_options;
		//int opt;
		po::options_description desc("Allowed options");
		desc.add_options()
		("",			"显示当前目录")
		("help,?", 		"输出帮助")
		("verbose,V",	"详细显示结果")
		("directory,D",	"只输出目录名")
		("file,F",		"只输出文件名")
		("recursive,R",	"遍历指定目录，包括子目录")	
		("pathName",	po::value< vector<string> >(),	"输入目录名"		)
		("maxDepth",	po::value< size_t >(),			"输入最大目录深度"	)
		("minDepth",	po::value< size_t >(),			"输入最小目录深度"	)
		("depth",		po::value< size_t >(),			"输入目录深度"		)
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
		Container vc;
		Controller c={ DEPTH,0 };//默认不遍历子目录
		//
		if(vm.count("depth") ){
			c.status_ = DEPTH;
			c.depth_  = vm["depth"].as< size_t >();
		}
		//
		if(vm.count("minDepth") ){
			c.status_ = MINDEPTH;
			c.depth_  = vm["minDepth"].as< size_t >();
		}
		//
		if(vm.count("maxDepth") ){
			c.status_ = MAXDEPTH;
			c.depth_  = vm["maxDepth"].as< size_t >();
		}
		//
		if(vm.count("recursive") ){
			c.status_ = INFINITE;
			c.depth_  = -1;
		}
		//
		if (vm.count("pathName"))
		{
			const vector<string>& dirs = vm["pathName"].as< vector<string> >();
			for(vector<string>::const_iterator itr=dirs.begin();itr!=dirs.end();++itr){
				pathList(*itr,c,vc);
			}
		}
		else{
			using namespace boost::filesystem;
			path current_path( initial_path<fs::path>() );
			pathList(current_path.string(),c,vc);
		}
		//
		auto endItr=vc.end();
		if( vm.count("directory") ){
			endItr=remove_if(vc.begin(),vc.end(),!boost::bind<bool>(isDir,_1) );
			copy(vc.begin(),endItr,ostream_iterator<string>(cout,"\n") );
			return EXIT_SUCCESS;
		}
		if( vm.count("file") ){
			endItr=remove_if(vc.begin(),vc.end(),boost::bind<bool>(isDir,_1) );
			copy(vc.begin(),endItr,ostream_iterator<string>(cout,"\n") );
			return EXIT_SUCCESS;
		}		
		//
		if( vm.count("verbose") ){
			if( errorMessage.empty() == true ) return EXIT_SUCCESS;
			errorMessage.push_back("\n");
			copy(errorMessage.begin(),errorMessage.end(),ostream_iterator<string>(cout,"\n") );
		}
		copy(vc.begin(),endItr,ostream_iterator<string>(cout,"\n") );
	}
	catch( std::exception& e){
		errorMessage.push_back(e.what() );
	}
	return EXIT_SUCCESS;
}
//
void pathList(const string& path, const Controller& c,Container& result){
    //EZLOGGERFUNCTRACKER;
	//cout<<path<<"\t"<<c.status_<<"\t"<<c.depth_<<"\n";
	using namespace fs;
	try{
		fs::path p(path);
		if (p.empty()) 	return;
		if (fs::is_directory(p)) {
			fs::recursive_directory_iterator endItr;
			fs::recursive_directory_iterator itr(p);
			while( itr != endItr ){
				//cout<<itr.level()<<","<<c.depth_<<"\t"<<itr->path().string()<<"\n";
				if( fs::is_directory(*itr) ){
					try{
						fs::directory_iterator dir(*itr);
					}
					catch( const fs::filesystem_error& e){
						errorMessage.push_back( e.what() );
						itr.no_push();
					}
				}				
				if( c.status_ == INFINITE ){
					result.push_back(itr->path().string());
				}
				if( c.status_ == MAXDEPTH && itr.level() <= c.depth_ ){
					result.push_back(itr->path().string());
				}
				if( c.status_ == MINDEPTH && itr.level() >= c.depth_ ){
					result.push_back(itr->path().string());
				}
				if( c.status_ == DEPTH	  && itr.level() == c.depth_){
					result.push_back(itr->path().string());
				}
				if( c.depth_ == itr.level() ) itr.no_push();
				++itr;	
			}
		}
	}
	catch( const filesystem_error& e){
		errorMessage.push_back( e.what() );
	}
}
//
