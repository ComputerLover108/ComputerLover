#include <list>
#include <algorithm>
#include <iterator>
//
#include "boost/filesystem.hpp"
//
#include "path_list.h"
#include "../file/file.h"
//

//
void Cpath_list::run(){
	using namespace std;
	using namespace fs;
	//boost::progress_timer t( std::clog );
	try{
		if (exists(fileName) && is_directory(fileName))
		{
			transform(recursive_directory_iterator(fileName), recursive_directory_iterator(),
			back_inserter(m_files),mem_fun_ref(path::native_file_string) ); 
			);
		}
	}
	catch(const filesystem_error& e ){
		std::clog<<e.what()<<"\n";
	};
  	
}
//
void Cpath_list::display(){
	using namespace std;
	copy(m_files.begin(),m_files.end(),ostream_iterator<string>(cout,"\n") );
	cout<<"There are "<<m_files.size()<<" files and directories in "<<m_fname<<"\n";  
}
//
typedef std::list<std::string> R;
R& Cpath_list::content() const{
	using namespace std;
	return m_files;
}


