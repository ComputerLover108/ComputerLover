/**
    Module Name:

    Description:

    Author: WUKEXIN
    Created: wukexin
    Last Change:

    Functions:

*/


#ifndef CtracerH
#define CtracerH

namespace My_lib{
#include <string>
        class Ctracer{
        public:
            Ctracer(const std::string message);
            Ctracer(const std::string message, const std::string arg);
            void append(const std::string result);
            ~Ctracer();
        private:
            std::string _message;
    };
}//end namespace My_lib
//
#endif //CtracerH
