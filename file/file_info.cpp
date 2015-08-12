#include "file_info.h"
#include "file.h"
//
#include "windows.h"
#include <string>
#include <iostream>
#include <stdexcept>
//#include <locale>
#include <iomanip>
//
//#include "boost/date_time/posix_time/posix_time.hpp" 
//#include "boost/filesystem.hpp" 

namespace MWin{
	
	//
	void Cfile_information::initializer(std::string fname){
		//std::cout<<fname<<"construct success!\n";
		WIN32_FIND_DATA file_;
		HANDLE hfile_=FindFirstFile(fname.c_str(),&file_);
		if(INVALID_HANDLE_VALUE == hfile_){
			std::string message("FindFirstFile(,&file) run error!");
			size_t loc=message.find('(',0);
			message.insert(loc,fname);
			throw std::runtime_error(message);
		}
		//
		fileName_=fname;
		sAttribute_=fileAttribToStr( file_.dwFileAttributes );
		cFileTime_=filetimeToStr( &file_.ftCreationTime );
		wFileTime_=filetimeToStr( &file_.ftLastWriteTime );
		aFileTime_=filetimeToStr( &file_.ftLastAccessTime );
		fileSize_ =file_.nFileSizeHigh * MAXDWORD + file_.nFileSizeLow;
		//
		if( 0==FindClose(hfile_))
		{
			std::string message("FindClose(,hfile) run error!\n");
			size_t loc=message.find('(',0);
			message.insert(loc,file_.cFileName);
			throw std::runtime_error(message);
		}
	}
	//
	//
	void Cfile_information::print(){
		//std::cout<<"Cfile_information::print("<<file_.cFileName<<")"<<hfile_<<" \n";
		using namespace std;
		//using namespace wukexin;
		size_t wide=26; //微软时间宽度26位
		cout.imbue( std::locale("") );
		cout
		<<sAttribute() 
		<< "\t"
		<<setiosflags(ios::right)<<setw(18)
		<<fileSize()
		<< "\t"
		<<resetiosflags(ios::right)
		<<setiosflags(ios::left)
		<<setw(wide)<<setfill(' ')
		<< cFileTime()
		<< "\t"
		<<setw(wide)<<setfill(' ')
		<< wFileTime()
		<< "\t" 
		<<setw(wide)<<setfill(' ')
		<< aFileTime()
		<<"\t"
		<<fileName_ 
		<< "\n";
	}
	//
}