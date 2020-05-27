#include "dlib/logger.h"
#include "dlib/misc_api.h"
using namespace dlib;
//
#include "boost/program_options.hpp"
#include "boost/foreach.hpp"
using namespace boost;
namespace po = boost::program_options;
//
#include <iostream>
#include <regex>
//
using namespace std;
//
logger dlog("logger");
//
typedef vector<string> Container;
//
bool checkTimeFormat(const string& s);
//
int main(int argc, char *argv[])
{
	try{
		dlog.set_level(LALL);
		//int opt;
		string description = "这是一个计算时间流逝的小程序！";
		po::options_description desc(description);
		desc.add_options()
		("help", "produce help message")
		//("century,C","过了多少个世纪")
		("year,Y","过了多少年")
		("month,M","过了多少月")
		("day,D","过了多少天")
		("week,W","过了多少星期")
		("hour","过了多少小时")
		("minute","过了多少分钟")
		("second","过了多少秒")
		("microsecond","过了多少微秒")
		("input",po::value< Container >(),"输入两个时间")
		;
		//
		po::positional_options_description p;
		p.add("input",-1);
		
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
		po::notify(vm);
		//
		if (vm.count("help")) {
			cout << "Usage: options_description [options]\n";
			cout << desc;
			return EXIT_SUCCESS;
		}
		//
		if(vm.count("input") ){
			const vector<string>& d2 = vm["input"].as< Container >();
			//static_assert( d2.size() == 2, "请输入两个时间！" );
			if( 2 != d2.size() ){
				dlog << LWARN << "请输入两个时间！" ;
				return EXIT_FAILURE;
			}
			BOOST_FOREACH(string time, d2){
				if( !checkTimeFormat(time) ){
					dlog << LWARN <<"不正确的时间格式！\n例如：2011-11-5日 20:47:36";
					return EXIT_FAILURE;
				}
			}
			//dlog << LTRACE << "options[--input]"; 
		}
	}
	catch( const std::exception& e){
		cerr<<e.what()<<"\n";
	}
	return EXIT_SUCCESS;
}
//
bool checkTimeFormat(const string& s){
	//感谢 雁过无痕雁过也，了无痕
	//http://blog.csdn.net/lxcnn/article/details/4362500
	string sc1 = "(\d{0,4}[-/.]\d{1,2}[-/.]\d{1,2})|(\s\d{1,2}:\d{1,2}:\d{1,2}:\d{1,3})";
	regex re(sc1);
	dlog << LTRACE << s <<"\tresult:"<<regex_match(s, re);
	if( regex_match(s,re) == false ) return false;
	//	
	string TimeFormat="^(?:(?:(?:0?[1-9]|1[0-9]|2[0-8])([-/.]?)(?:0?[1-9]|1[0-2])|(?:29|30)([-/.]?)(?:0?[13-9]|1[0-2])|31([-/.]?)(?:0?[13578]|1[02]))([-/.]?)(?!0000)[0-9]{4}|29([-/.]?)0?2([-/.]?)(?:[0-9]{2}(?:0[48]|[2468][048]|[13579][26])|(?:0[48]|[2468][048]|[13579][26])00))\s([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$";
	re=TimeFormat;
	dlog << LTRACE << s <<"\tresult:"<<regex_match(s, re);
	return ( regex_match(s, re) );
}
