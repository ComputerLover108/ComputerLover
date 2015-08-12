#include <iostream>
#include <string>
#include "help.h"
using namespace std;
//

int main()
{

    int i=5,ni=-3,result=i*ni;
    WKX::MemoryMap<long long > x(i);
    WKX::MemoryMap<long long > y(ni);
    WKX::MemoryMap<long long > z(result);
    cout
        <<i<<'\t'<<x<<'\n'
        <<ni<<'\t'<<y<<'\n'
        <<result<<'\t'<<z<<'\n'
        <<i<<'*'<<ni<<'='<<result<<'\n'
        <<x<<'*'<<y<<'='<<z<<'\n'
        <<"\n";
    char s[]="abc";
    WKX::MemoryMap<char*> ms(s);
    string ss="abc012";
    WKX::MemoryMap<std::string> mss(ss);
    cout<<s<<'\t'<<ms<<'\n'
        <<ss<<'\t'<<mss<<'\n'
        <<'\n';
    return 0;
}
