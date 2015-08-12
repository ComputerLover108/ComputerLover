#include <ctime>
#include <string>
#include <iostream>
//
#include "timer.h"
    namespace WKX{
     Timer::Timer(char const * s):m_message(s){
    m_start=std::clock();
    }
     Timer::Timer(std::string const& s):m_message(s){
    m_start=std::clock();
    }
     Timer::~Timer(){
    std::cout<<"\n"<<m_message<<" run "<<elapsed()<<" s.\n";
    }
     void Timer::restart(){
    m_start=std::clock();
    }	
    double Timer::elapsed() const{
    double end=std::clock();
    double result=(end-m_start) / CLOCKS_PER_SEC;
    return result;
    } 
}
           
