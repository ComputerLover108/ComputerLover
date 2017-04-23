#include "windows.h"
#include <list>
#include <string>
#include <cstring>
#ifndef PATH_LIST_H
#define PATH_LIST_H
typedef std::list<std::string> C;
class Cpath_list{
    public:
    Cpath_list(const char* s):m_fname(s){};
    ~Cpath_list(){};
    void run();
    void display();
    C& Cpath_list::content() const;
    private:        
    static C m_files;
    std::string m_fname;
};
C Cpath_list::m_files;
#endif
