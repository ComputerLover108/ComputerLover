/*
void get()
{
ifstream ifs("d:\\prime.txt");
while (ifs.good()) {
int i ,k=0;
char ch;
ch=ifs.get();
int result = static_cast<int>(ch);
cout<<result<<endl;
};
ifs.close();
}
primt.txtÄÚÈÝ:
12
2
3
4
5
6
*/
#include <iostream>
#include <fstream>
using namespace std;
//
int main(int argc, char *argv[])
{
	if( 2!=argc){
		cout<<"Example:\t job primt.txt \n";
		return 0;
	}
	if( 2==argc ){
		ifstream in(argv[1]);
		int int_value;
		while( in >> int_value){
			cout<<int_value<<"\n";
		}
	}
	return 0;
}
