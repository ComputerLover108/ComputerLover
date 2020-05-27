#ifndef TIMER_H
#define TIMER_H
//
#include <ctime>
namespace WKX {
class Timer{
public:
       Timer(char const* s);
       Timer(std::string const& s);
       ~Timer();
       void   restart();
       double elapsed() const;
       //double elapsed_max() const;
       //double elapsed_min() const;   
private:
        std::clock_t m_start;
        std::string m_message;
}; // timer
//
} // namespace WKX

#endif  // timer
