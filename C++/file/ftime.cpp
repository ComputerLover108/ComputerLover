#include <iostream>
#include <ctime>

#include "boost/progress.hpp"
#include "boost/program_options.hpp"
#include "boost/date_time.hpp"
#include "windows.h"
//
// these constants come from inspecting some Microsoft sample code
std::time_t to_time_t( const FILETIME & ft )
{
	using namespace std;
	__int64 t = (static_cast<__int64>( ft.dwHighDateTime ) << 32)
	+ ft.dwLowDateTime;
	cout<<t<<"\n";
# if !defined( BOOST_MSVC ) || BOOST_MSVC > 1300 // > VC++ 7.0
	t -= 116444736000000000LL;
# else
	t -= 116444736000000000;
# endif
	cout<<"vc2003:\t"<<t<<"\n";
	t /= 10000000;
	//cout<<sizeof(__int64)<<\t<<sizeof(std::time_t)<<"\n";
	cout<<static_cast<std::time_t>( t )<<"\n";
	return static_cast<std::time_t>( t );
}

void to_FILETIME( std::time_t t, FILETIME & ft )
{
	__int64 temp = t;
	temp *= 10000000;
# if !defined( BOOST_MSVC ) || BOOST_MSVC > 1300 // > VC++ 7.0
	temp += 116444736000000000LL;
# else
	temp += 116444736000000000;
# endif
	ft.dwLowDateTime = static_cast<DWORD>( temp );
	ft.dwHighDateTime = static_cast<DWORD>( temp >> 32 );
}
//
void print_tm(const tm* t){
	std::cout<<t->tm_sec<<"sec\t"   
		<<t->tm_min<<"min\t"     
		<<t->tm_hour<<"hour\t"    
		<<t->tm_mday<<"mday\t"    
		<<t->tm_mon<<"mon\t"     
		<<t->tm_year<<"year\t"    
		<<t->tm_wday<<"wday\t"    
		<<t->tm_yday<<"yday\t"    
		<<t->tm_isdst<<"isdst\n";   
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
		("help,?", "修改文件创建时间，例：ftime d:\backup.cpp -D 1999-12-01")
		("fileName", po::value<string>(), "输入文件名")
		("time,T",po::value<string>(),"时间")
		("date,D",po::value<string>(),"日期")
		;

		po::positional_options_description p;
		p.add("fileName", -1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
		options(desc).positional(p).run(), vm);
		po::notify(vm);
		if (vm.count("help")) {
			cout << "Usage: options_description [options]\n";
			cout << desc;
			return 0;
		}
		/*
HANDLE CreateFile(
	LPCTSTR lpFileName,	// pointer to name of the file 
	DWORD dwDesiredAccess,	// access (read-write) mode 
	DWORD dwShareMode,	// share mode 
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,	// pointer to security attributes 
	DWORD dwCreationDistribution,	// how to create 
	DWORD dwFlagsAndAttributes,	// file attributes 
	HANDLE hTemplateFile 	// handle to file with attributes to copy  
);

struct tm {
		int tm_sec;     /* seconds after the minute - [0,59] 
		int tm_min;     /* minutes after the hour - [0,59] 
		int tm_hour;    /* hours since midnight - [0,23] 
		int tm_mday;    /* day of the month - [1,31] 
		int tm_mon;     /* months since January - [0,11] 
		int tm_year;    /* years since 1900 
		int tm_wday;    /* days since Sunday - [0,6] 
		int tm_yday;    /* days since January 1 - [0,365] 
		int tm_isdst;   /* daylight savings time flag 
		};
*/
		string fname,fdate,ftime;
		HANDLE hfile;
		if(vm.count("fileName") ){
			fname=vm["fileName"].as<string>();
			hfile=CreateFile(fname.c_str(),
							FILE_WRITE_ATTRIBUTES,
							FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL,
							OPEN_EXISTING,
							FILE_FLAG_BACKUP_SEMANTICS,
							NULL
							);
			//cout<<fname<<"\t"<<hfile<<"\t"<<INVALID_HANDLE_VALUE<<"\n";				
			if( hfile==INVALID_HANDLE_VALUE){cout<<"CreateFile() run error!\n"; throw;}	;
		}
		FILETIME ftc,fta,ftw;
		if(0==GetFileTime(hfile,&ftc,&fta,&ftw) ){cout<<"GetFileTime() run error!\n";throw;};
		//time_t tc=to_time_t(ftc);
		using namespace boost::gregorian;
		using namespace boost::posix_time;
		ptime pta;
		//tm *pft=gmtime(&tc);
		tm ft;
		//print_tm(ft);
		if(vm.count("time") ){
			ftime=vm["time"].as<string>();
			ptime ptt=time_from_string(ftime);
			tm temp=to_tm(ptt);
			//ft.tm_sec=temp.tm_sec;
			//ft.tm_min=temp.tm_min;                              
			//ft.tm_hour=temp.tm_hour;
			ft=temp;
			//print_tm(ft);
		}
		if(vm.count("date") ){
			fdate=vm["date"].as<string>();
			date td=from_string(fdate);
			//cout<<fdate<<"\t"<<td;
			tm temp=to_tm(td);
			ft.tm_year=temp.tm_year;
			ft.tm_mon=temp.tm_mon;
			ft.tm_mday=temp.tm_mday;
			td=date_from_tm(ft);
			//cout<<"\t*"<<td;
			ft=to_tm(td);
		}
		FILETIME ptc;
		cout<<to_time_t(ftc)<<"\n"<<asctime(&ft)<<"\n";
		std::time_t tt=mktime(&ft);
		if( -1==tt){cout<<"mktime() run error!\n";	throw;}
		to_FILETIME(tt,ptc);
		if( 0==::SetFileTime(hfile,&ptc,NULL,NULL) ){cout<<"SetFileTime() run error!\n"; throw ;}
		if( 0==::CloseHandle(hfile) ){cout<<"CloseHandle() run error!\n";	throw;}

	}
	catch(exception& e)
	{	
		cout << e.what() << "\n";
		return 1;
	}
	return 0;
}