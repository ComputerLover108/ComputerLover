#include <boost/program_options.hpp>
using namespace boost;
namespace po = boost::program_options;
//
#include <iostream>
//
using namespace std;
//
int main(int argc, char *argv[])
{
	try{		
		int opt;
		po::options_description desc("Allowed options");
		desc.add_options()
		("help", "produce help message")
		;
		//
		po::positional_options_description p;
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
		po::notify(vm);
		//
		if (vm.count("help")) {
			cout << "Usage: options_description [options]\n";
			cout << desc;
			return EXIT_SUCCESS;
		}
		//
	}
	catch( const std::exception& e){
		cerr<<e.what()<<"\n";
	}
	return EXIT_SUCCESS;
}
