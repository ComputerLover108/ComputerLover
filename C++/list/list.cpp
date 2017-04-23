
#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "boost/progress.hpp"
#include "boost/bind.hpp"


//

#include <ostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <cstring>
//
#include "../file/file.h"
#include "../help/help.h"
///nologo /MT /W3 /GX /GR /D "WIN32" /D "_CONSOLE"
//
namespace fs = boost::filesystem;
using namespace fs;
//
void pathList(const std::string& path, Container& result,unsigned long maxdepth=0);
//
class IsDirectory : public std::unary_function<std::string, bool>{
	public:
	bool operator() (const std::string fileName) {
		return fs::is_directory(fileName);
	}	
};
//
struct NotDirectory : public std::unary_function<std::string,bool>{
	bool operator() (const std::string fileName){
		return !fs::is_directory(fileName);
	}
};
//
typedef std::vector<std::string> Container;
//
void pathList(const std::string pathName,Container& result){
	using namespace std;
	using namespace fs;
	try{
		if (exists(pathName) && is_directory(pathName) )
		{
			transform(recursive_directory_iterator(pathName), 
			recursive_directory_iterator(),
			back_inserter(result),
			mem_fun_ref(path::native_file_string)
			);
		}
	}
	catch(const filesystem_error& e ){
		std::clog<<e.what()<<"\n";
	};
}
//
void pathList(const string& path, Container& result,size_t maxdepth){
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
int main(int argc, char* argv[])
{
	using namespace std;
	try{
		boost::progress_timer t( std::clog );
		namespace po = boost::program_options;
		//int opt;
		po::options_description desc("Allowed options");
		desc.add_options()
		("","显示当前目录")
		("help,?", "输出帮助")
		("pathName", po::value< vector<string> >(), "输入目录名")
		("maxDepth,M",po::value<size_t>(),"输入目录深度")
		("directory,D","只输出目录名")
		("file,F","只输出文件名")
		("complete,C","详细显示目录")
		("create_time","输出文件产生时间")
		("write_time","输出文件最后写入时间")
		("access_time","输出文件访问时间")
		("size","输出文件或目录的大")
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
		size_t depth=0;
		//
		if(vm.count("maxDepth") ){
			depth = vm["depth"].as< size_t >();
			//clog<<"depth="<<depth<<"\n";
		}
		//
		if (vm.count("pathName"))
		{
			const vector<string>& dirs = vm["pathName"].as< vector<string> >();
			for(vector<string>::const_iterator itr=dirs.begin();itr!=dirs.end();++itr){
				//clog<<"depth="<<depth<<"\tfilename="<<*itr<<"\n";
				if( depth<= 0)	pathList(*itr,vc);
				else 	pathList(*itr,depth,vc);
			}
		}
		else{
			using namespace boost::filesystem;
			path current_path( initial_path<fs::path>() );
			if( depth<= 0 )	pathList(current_path.native_file_string(),vc);
			else	pathList(current_path.native_file_string(),vc,depth);
		}
		//
		if( vm.count("directory") ){
			erase_if(vc,NotDirectory() );
		}
		if( vm.count("file") ){			
			erase_if(vc,IsDirectory() );
		}		
		//
		if(vm.count("create_time") ){
			for(Container::iterator itr=vc.begin();itr!=vc.end();itr++){
				ostringstream os;
				os.imbue( std::locale("") );
				os<<setw(26)<<setiosflags(ios::left)
				<<MWin::GetFileCreationTime(itr->c_str() )<<"\t"<<*itr;
				*itr=os.str();
			}
		}
		//
		if(vm.count("write_time") ){
			for(Container::iterator itr=vc.begin();itr!=vc.end();itr++){
				ostringstream os;
				os.imbue( std::locale("") );
				os<<setw(26)<<setiosflags(ios::left)
				<<MWin::GetFileWriteTime(itr->c_str() )<<"\t"<<*itr;
				*itr=os.str();
			}		
		}
		//
		if(vm.count("access_time") ){
			for(Container::iterator itr=vc.begin();itr!=vc.end();itr++){
				ostringstream os;
				os.imbue( std::locale("") );
				os<<setw(26)<<setiosflags(ios::left)
				<<MWin::GetFileAccessTime(itr->c_str() )<<"\t"<<*itr;
				*itr=os.str();
			}		
		}
		//
		if(vm.count("size") ){
			for(Container::iterator itr=vc.begin();itr!=vc.end();itr++){
				ostringstream os;
				os.imbue( std::locale("") );
				os<<setw(12)<<setiosflags(ios::right)<<MWin::GetFileSize(*itr)<<"\t"<<*itr;
				*itr=os.str();
			}	
		}
		//
		if(vm.count("complete") ){
			using namespace MWin;
			for(Container::iterator itr=vc.begin();itr!=vc.end();itr++){
				//std::auto_ptr<Cfile_information> ptr(new Cfile_information(*itr) );
				//ptr->print();
				cout.imbue( std::locale("") );
				cout<<setw(12)<<setiosflags(ios::right)
				<<GetFileSize(*itr)<<"\t"
				<<GetFileWriteTime( itr->c_str() ) <<"\t"
				<<*itr<<"\n";				
			}
			return 0;
		}
		copy(vc.begin(),vc.end(),ostream_iterator<string>(cout,"\n") );
		clog<<"Get "<<vc.size()<<" results!\n";	
	}
	catch( std::exception& e){
		std::cout<<e.what()<<"\n";
	}
	return 0;
}
