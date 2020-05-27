#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include "boost/progress.hpp"
#include <boost/regex.hpp>

namespace po = boost::program_options;
//
boost::regex_constants::syntax_option_type flags = boost::regex_constants::basic;
boost::regex re;
boost::smatch what;
bool is_insert,is_append;
std::string pattern;
//
//
//
void process_file(const std::string& name)
{
   using namespace std;
	ifstream file(name.c_str() );
   if(file.bad())
   {
      std::cerr << "Unable to open file " << name << std::endl;
	  throw;
   }
	vector<string> vs;
   std::string line;
   //int linenum = 1;
   while(std::getline(file, line))
   {
      vs.push_back(line);
	  //clog<<line<<"\n";
   }
   file.close();
   ofstream of(name.c_str());
	if(is_append){
		for(vector<string>::const_iterator itr=vs.begin();itr!=vs.end();itr++){
			of<<*itr<<pattern<<"\n";
		}		
	}
	if(is_insert){
		for(vector<string>::const_iterator itr=vs.begin();itr!=vs.end();itr++){
			of<<pattern<<*itr<<"\n";
			//cout<<pattern<<*itr<<"\n";
		}		
	}
}
//
int main(int argc, char * argv[])
{
	try{
		//boost::progress_timer t( std::clog );   
		po::options_description opts("Options");
		opts.add_options()
		("help,h", "produce help message") 
		("insert,I","在每行的头部插入")
		("append,A","在每行的尾部添加")
		("fileName,F",po::value<std::string>(),"输入文件名")
		("pattern",po::value<std::string>(),"输入样式")
		;

		//po::options_description cmdline_options;
		//cmdline_options.add(opts);

		po::positional_options_description p;
		p.add("pattern", 1);
		p.add("fileName", -1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv)
		.options(opts)
		.positional(p)
		.run(), vm);
		po::notify(vm);

		if (vm.count("help")) 
		{
			std::cout << opts << "\n";
			return 0;
		}
		//
		if(vm.count("insert") ){
			is_insert=true;
			//std::cout<<is_insert<<"\n";
		}
		//
		if(vm.count("append") ){
			is_append=true;
			//std::cout<<is_append<<"\n";
		}
		//
		if(vm.count("pattern"))
		{
			pattern = vm["pattern"].as< std::string >();
			//std::cout<<"pattern="<<pattern<<"\n";
		}
		else
		{
			std::cerr << "No pattern specified" << std::endl;
			return 1;
		}
		if (vm.count("fileName"))
		{
			std::string file = vm["fileName"].as< std::string >();
			//std::cout<<"fileName="<<file<<"\n";
			process_file(file);
		}
		else{
			std::cerr<<" No file!\n";
			return 1;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
