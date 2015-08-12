#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "file.h"
int main(){
	using namespace std;
	using namespace MS;
	//extern FileAttributeMapString fs[];
	typedef FileAttributeMap FS;
	FS fs[]={
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
	static size_t limit=sizeof(fs)/sizeof(FS);
	static std::vector<FS> v(fs,fs+limit);
	sort(v.begin(),v.end() );
	copy(v.begin(),v.end(),ostream_iterator<FS>(cout,"\n") );
return 0;
}