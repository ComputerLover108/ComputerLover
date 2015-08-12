#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>
#include <functional>
#include <iomanip>
#include <map>
#include <utility>
#include "boost/filesystem.hpp"
#include "boost/progress.hpp"
#include "boost/program_options.hpp"
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
namespace fs = boost::filesystem;
using namespace boost;
using namespace std;
typedef std::vector<std::string> C;
//stringstream ss;
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
int main(int ac, char* av[])
{
	using namespace boost::program_options;
	try {
		boost::progress_timer t( std::clog );
		options_description desc("Allowed options");
		desc.add_options()
		("help,?", "produce a help message")
		("pathName", value< vector<string> >(), "输入目录名")
		("file,@", value<string>(),"输入放置目录名的文件名")
		;
		
		positional_options_description p;
		p.add("pathName", -1);	
		
		variables_map vm;
		store(command_line_parser(ac, av).
		options(desc).positional(p).run(), vm);
		notify(vm);
		if (vm.count("help")) {
			cout << desc;            
		}
		//
		if (vm.count("file")) {
			string fileName=vm["file"].as<string>();
			ifstream ifs(fileName.c_str());
			if (!ifs) {
				cout << "Could not open the response file\n";
				return 1;
			}
			string pathName;
			multimap<size_t,string,std::greater<size_t> > mm;
			while( getline(ifs,pathName) ){
				//clog<<pathName<<"\n";
				using namespace fs;
				try{			
					if (exists(pathName) && is_directory(pathName) )
					{
						//cout<<"*\t"<<pathName<<"\n";
						path p(pathName);
						string date=p.file_string();
						size_t key=count(date.begin(),date.end(),'\\');
						mm.insert(make_pair<size_t,string>(key,date) );
						//cout<<key<<"\t"<<date<<"\n";						
					}
					
				}
				catch(const filesystem_error& e ){
					std::clog<<e.what()<<"\n";
				};	
			}
			for( multimap<size_t,string,std::greater<size_t> >::iterator itr=mm.begin();itr!=mm.end();itr++){
				cout.imbue( std::locale("") );
				cout<<setw(12)<<setiosflags(ios::right)<<dir_size(itr->second)<<"\t"<<itr->second<<"\n";
			}
			//copy(mm.begin(),mm.end(),ostream_iterator<pair<size_t,string> >(cout,"\n") );
			clog<<"打印了"<<mm.size()<<"目录\n";
			return 0;	
		}
		//
		if (vm.count("pathName")){
			const vector<string>& dirs = vm["pathName"].as< vector<string> >();
			for(vector<string>::const_iterator itr=dirs.begin();itr!=dirs.end();++itr){
				cout.imbue( std::locale("") );
				cout<<setw(12)<<setiosflags(ios::right)<<dir_size(*itr)<<"\t"<<*itr<<"\n";
			}
			return 0;
		}
	}   
	catch(const std::exception& e) {
		cout << e.what() << "\n";
	}
	return 0;
}