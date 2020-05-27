#ifndef dirH
#define dirH
//
#include "windows.h"
//
#include "boost/filesystem.hpp"
//
#include <list>
#include <string>
#include <memory>
//
namespace fs = boost::filesystem ;
//
size_t dir_size(const std::string fileName);
#endif// dirH
