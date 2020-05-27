#include "windows.h"
#include "dir.h"
//
#include <cstring>
#include <string>
#include <iostream>
#include <list>
#include <iterator>
//
#include "boost/filesystem.hpp"
//
using namespace boost::filesystem;
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
