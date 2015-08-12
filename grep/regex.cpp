#include <boost/program_options.hpp>
using namespace boost;
namespace po = boost::program_options;

#include <iostream>
//
using namespace std;
//
int main(int argc, char *argv[])
{
    try {
	int opt;
	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "produce help message")
	    ("test,S", po::value < string > (), "test string")
	    ("regex,R", po::value < string > (), " regex express");

	po::positional_options_description p;
	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).options(desc).run(),
		  vm);
	po::notify(vm);

	if (vm.count("help")) {
	    cout << "Usage: options_description [options]\n";
	    cout << desc;
	    return 0;
	}
	string s, e;
	if (vm.count("test")) {
	    s = vm["test"].as < string > ();
	}
	if (vm.count("regex")) {
	    e = vm["regex"].as < string > ();
	}


    }
    catch(std::exception & ex) {
	cerr << ex.what() << "\n";
	return 1;
    }
    catch(...) {
	cerr << "Program run error!\n";
	return 1;
    }
    return 0;
}
