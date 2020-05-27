#include "chdir.h"
#include "windows.h"
#include "..\log\log.h"
#include <iostream>
#include <string>
chdir::chdir()
{
	if( 0 == GetCurrentDirectory(MAX_PATH,m_s) ){
		 std::string errorMessage("[ GetCurrentDirectory() ]不能得到当前目录！");
         throw errorMessage; 
	} 
}
chdir::~chdir()
{
    try{           
    cd(m_s);
    }
    catch( std::string exceptionMessage ){
          std::cerr<<exceptionMessage<<"\n"; 
          std::string fname("e:\\program\\wukexin\\list\\list.log"); 
          WKX::log(fname,exceptionMessage);
    }
}
void chdir::cd(const char* x){
	if( 0==SetCurrentDirectory(x) ) {
        std::string errorMessage("[ SetCurrentDirectory() ]不能设置当前目录为: ");
        errorMessage.append(x);
        throw errorMessage;
	}
}

