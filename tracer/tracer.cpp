#include <string>
#include <iostream>
#include "tracer.h"
//////////
namespace My_lib{
    Ctracer::Ctracer(const std::string message){
        _message=message;
        std::cout<<"Come in "<<_message<<" .\n";
    }
//

    Ctracer::Ctracer(const std::string message, const std::string arg){
        _message=message;
        _message.append("( ");
        _message.append(arg);
        _message.append(" )");
        std::cout<<"Come in "<<_message<<" .\n";
    }
//
    Ctracer::~Ctracer(){
        std::cout<<"Go out "<<_message<<" .\n";
    }
//
    void Ctracer::append(const std::string result){
        _message.append("=");
        _message.append(result);
    };
}//end namespace My_lib
