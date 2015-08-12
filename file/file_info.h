/**
	Module Name:

	Description:

	Author:
	Created:
	Last Change:

	Functions:

*/
#include "windows.h"
#include <string>
#include <iostream>
//#include "..\wukexin\help\help.h"
//
#ifndef FILE_info_H
#define FILE_info_H
namespace MWin{
	//
	class Cfile_information{
	public:
		explicit Cfile_information(std::string fname){ initializer(fname); };
		std::string cFileTime() {return cFileTime_;};
		std::string wFileTime() {return wFileTime_;};
		std::string aFileTime() {return aFileTime_;};
		std::string fileName() {return fileName_;};
		std::string sAttribute() {return sAttribute_;};
		size_t fileSize() {return fileSize_;};
		void print();
	protected:
		//friend ostream& operator<< (std::ostream& os, const Cfile_information& file);
	private:
		void initializer(std::string fname);
		std::string cFileTime_;
		std::string wFileTime_;
		std::string aFileTime_;
		std::string sAttribute_;
		std::string fileName_;
		size_t fileSize_;
	};
	//
}
#endif //file1.h
