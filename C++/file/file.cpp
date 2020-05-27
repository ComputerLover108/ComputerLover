
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctype.h>
#include <iterator>
#include <ctype.h>
//
#include "windows.h"
//
#include "boost/filesystem.hpp"
#include "boost/dynamic_bitset.hpp"
//
#include "file.h"
namespace MS{

	//
	std::ostream& operator<< (std::ostream& out, const FileAttributeMap& x){
		using namespace std;
		const boost::dynamic_bitset<> attrib(sizeof(DWORD)*8,x.attribute_);
		out<<x.abbreviation_<<"\t"<<attrib<<"\t"<<x.strAttribute_;
		return out;
	}
	//
	bool operator < (FileAttributeMap T1,FileAttributeMap T2){
		return T1.attribute_ < T2.attribute_ ;
	}
	//test function
	typedef FileAttributeMap FM;
	FM fm[]={
		{'R',READONLY,"READONLY"},
		{'A',ARCHIVE,"ARCHIVE"},
		{'S',SYSTEM,"SYSTEM"},
		{'H',HIDDEN,"HIDDEN"},
		{'D',DIRECTORY,"DIRECTORY"},
		{'C',COMPRESSED,"COMPRESSED"},
		{'N',NORMAL,"NORMAL"},
		{'L',OFFLINE,"OFFLINE"},
		{'T',TEMPORARY,"TEMPORARY"},
		{'E',ENCRYPTED,"ENCRYPTED"},
		{'O',SPARSE,"SPARSE"},
		{'P',REPARSE_POINT,"REPARSE_POINT"}
	};
	static size_t limit=sizeof(fm)/sizeof(FM);
	static std::vector<FM> v(fm,fm+limit);
	//文件属性简写
	std::string fileAttribToStr_A( const DWORD attrib) {
		using namespace std;
		std::string result;
		for(std::vector<FM>::const_iterator itr=v.begin();itr!=v.end();itr++){
			if( attrib & itr->attribute_ ) { result += itr->abbreviation_; }
			sort(result.begin(),result.end());
		}
		return result;
	}
	//
	DWORD stringToAttrib(const std::string s1){
		using namespace std;
		std::string s;
		std::unique_copy(s1.begin(),s1.end(),back_inserter(s) );
		DWORD result=0;
		for(unsigned int i=0;i<s.size();i++){
			for(std::vector<FM>::const_iterator itr=v.begin();itr!=v.end();itr++){
				if( toupper(s[i]) ==itr->abbreviation_ ) { result |= itr->attribute_; }
			}
		}
		//std::cout<<"stringToAttrib("<<s<<")="<<result<<"\t"<<fileAttribToStr(result)<<"\n";
		return result;
	}

/*
	std::string filetimeToStr( const FILETIME* ft ) {
		std::string result;
		using namespace boost::posix_time;
		FILETIME temp(*ft);
		ptime pt = from_ftime<ptime>(temp);
		result=to_iso_extended_string(pt);
		std::replace(result.begin(),result.end(),'T',' ');
		return result;
	}
	//
	std::string GetFileCreationTime(const char* fname){
		HANDLE hfile=
		CreateFile( fname,
		0,
		FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		0
		);
		if ( hfile == INVALID_HANDLE_VALUE ) throw std::runtime_error("CreateFile() run error!\n");
		FILETIME create_time,lc;
		if( 0 == GetFileTime( hfile,&create_time ,0, 0 ) ) throw std::runtime_error("GetFileTime() run error!\n");
		if( 0 == FileTimeToLocalFileTime(&create_time,&lc) ) throw std::runtime_error("FileTimeToLocalFileTime() run error!\n");
		if( 0 == CloseHandle(hfile) ) throw std::runtime_error("CloseHandle() run error!\n");
		return filetimeToStr(&lc);
	}
	//
	std::string GetFileWriteTime(const char* fname){
		HANDLE hfile=
		CreateFile( fname,
		0,
		FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		0
		);
		if ( hfile == INVALID_HANDLE_VALUE ) throw std::runtime_error("CreateFile() run error!\n");
		FILETIME write_time,lt;
		if( 0 == GetFileTime( hfile,0 ,&write_time, 0 ) ) throw std::runtime_error("GetFileTime() run error!\n");
		if( 0 == FileTimeToLocalFileTime(&write_time,&lt) ) throw std::runtime_error("FileTimeToLocalFileTime() run error!\n");
		if( 0 == CloseHandle(hfile) ) throw std::runtime_error("CloseHandle() run error!\n");
		return filetimeToStr(&lt);
	}
	//
	std::string GetFileAccessTime(const char* fname){
		HANDLE hfile=
		CreateFile( fname,
		0,
		FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		0
		);
		if ( hfile == INVALID_HANDLE_VALUE ) throw std::runtime_error("CreateFile() run error!\n");
		FILETIME access_time,lt;
		if( 0 == GetFileTime( hfile,0 ,0, &access_time ) ) throw std::runtime_error("GetFileTime() run error!\n");
		if( 0 == FileTimeToLocalFileTime(&access_time,&lt) ) throw std::runtime_error("FileTimeToLocalFileTime() run error!\n");
		if( 0 == CloseHandle(hfile) ) throw std::runtime_error("CloseHandle() run error!\n");
		return filetimeToStr(&lt);
	}
	//
	size_t GetFileSize(const std::string fileName){
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
		sAttribute_=fileAttribToStr_A( file_.dwFileAttributes );
		FILETIME lc;
		if( 0 == FileTimeToLocalFileTime(&file_.ftCreationTime,&lc) ) throw std::runtime_error("FileTimeToLocalFileTime() run error!\n");
		cFileTime_=filetimeToStr( &lc );

		if( 0 == FileTimeToLocalFileTime(&file_.ftLastWriteTime,&lc) ) throw std::runtime_error("FileTimeToLocalFileTime() run error!\n");
		wFileTime_=filetimeToStr( &lc );

		if( 0 == FileTimeToLocalFileTime(&file_.ftLastAccessTime,&lc) ) throw std::runtime_error("FileTimeToLocalFileTime() run error!\n");
		aFileTime_=filetimeToStr( &lc );
		fileSize_ =file_.nFileSizeHigh * MAXDWORD + file_.nFileSizeLow;
		if( fs::is_directory(fileName_) ) fileSize_=dir_size(fileName_);
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
	void Cfile_information::print(){
		using namespace std;
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

	*/
}
