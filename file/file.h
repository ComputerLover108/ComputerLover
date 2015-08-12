/**
	Description: 

	Arguments:

	Returns:

*/
#include <string>
#include <windows.h>
//
#ifndef FILE_H
#define FILE_H
//
namespace MS{
	enum FileAttribute { 
		ARCHIVE=FILE_ATTRIBUTE_ARCHIVE,
		SYSTEM=FILE_ATTRIBUTE_SYSTEM,
		READONLY=FILE_ATTRIBUTE_READONLY,
		HIDDEN=FILE_ATTRIBUTE_HIDDEN,
		DIRECTORY=FILE_ATTRIBUTE_DIRECTORY,
		COMPRESSED=FILE_ATTRIBUTE_COMPRESSED,
		NORMAL=FILE_ATTRIBUTE_NORMAL,
		OFFLINE=FILE_ATTRIBUTE_OFFLINE,
		TEMPORARY=FILE_ATTRIBUTE_TEMPORARY,
		SPARSE=FILE_ATTRIBUTE_SPARSE_FILE,
		ENCRYPTED=FILE_ATTRIBUTE_ENCRYPTED,
		REPARSE_POINT=FILE_ATTRIBUTE_REPARSE_POINT
	};
	//
	class FileAttributeMap{
		public:
			char abbreviation_;
			FileAttribute attribute_;
			char* strAttribute_;
		protected:
			friend std::ostream& operator<< (std::ostream& out, const FileAttributeMap& source);	
	};
	bool operator < (FileAttributeMap T1,FileAttributeMap T2);
	//
	std::string fullPathName(std::string fname);
	DWORD stringToAttrib(const std::string s);
	/*
	//结果为文件属性的字符缩写
	std::string fileAttribToStr( const DWORD attrib);
	std::string filetimeToStr( const FILETIME* ft );
	std::string GetFileCreationTime(const char* fname);
	std::string GetFileWriteTime(const char* fname);
	std::string GetFileAccessTime(const char* fname);
	size_t GetFileSize(const std::string fileName);
	//
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
*/	
}
#endif //file.h
