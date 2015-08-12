#include <iostream>
#include <regex>
using namespace std;
int main(int argc,char* argv[]){
    string sed("s/.*/.*/(-?\d+|[aig])");
	regex re(sed);
	return EXIT_SUCCESS;
}