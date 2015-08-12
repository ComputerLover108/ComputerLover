#include <iostream>
#include <iterator>
#include "..\help\help.h"

namespace WKX{
    template<>
    std::ostream& operator<< <char*> (std::ostream& out, MemoryMap<char*>& x){
        std::cout<<"I is MemoryMap<char*> !\n";
        return out;
    }
//
    template<>
    std::ostream& operator<< <std::string> (std::ostream& out,MemoryMap<std::string>& x){
        std::cout<<"I is MemoryMap<std::string> !\n";
        return out;
    }
//
    template <> //必须加
    std::ostream& operator<< <char*>(std::ostream& out,MemoryMap<char*>& x);
    template <> //必须加
    std::ostream& operator<< <std::string>(std::ostream& out,MemoryMap<std::string>& x);
}//end WKX
