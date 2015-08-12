#ifndef BIGINT_H
#define BIGINT_H
//
#include <string>
#include <iostream>
//
#include "..\help\help.h"
namespace WKX
{
//
    class BigInt
    {
    public:
        BigInt(const std::string& s);
        BigInt():ptr_(NULL),size_(0){};
        BigInt(const BigInt& x);
        BigInt& operator = (const BigInt& x);
        ~BigInt();
    protected:
        friend std::istream& operator >> (std::istream& is,BigInt& x);
        friend std::ostream& operator << (std::ostream& os,const BigInt& x);
    private:
        WKX::Byte* ptr_;
        size_t size_;
    };
//
}//end WKX
#endif // BIGINT_H
