#include <cstdio>
#include "windows.h"
#include <cstdlib>
#include "ezlogger_headers.hpp"

void ezlogger_simple_example()
{
        int i = 123;
        std::string somedata = "Hello World";

        //Simple usage with standard verbosity level
        EZLOGGERSTREAM << somedata << " " << i << std::endl;

        //Can use alternate stream
        EZLOGGERSTREAM2(std::cerr) << somedata << " next line " << i << std::endl;

        //Verbosity level logging example
        EZLOGGERVLSTREAM(axter::log_often) << somedata << " " << i << std::endl;

        //Complex extended data example
        EZLOGGERVLSTREAM(axter::levels(axter::log_often, axter::warn, __FUNCSIG__ /*or GNU PRETTY_FUNCTION*/, "Xyz Facility")) << somedata << " " << i << std::endl;
}

