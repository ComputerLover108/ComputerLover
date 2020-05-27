#include "BigInt.h"
#include "..\help\help.h"
#include <string>
//
namespace WKX
{
    BigInt::BigInt(const std::string& s)
    {
        size_=s.length()/byte_length;
        if ( 0 != s.length() % byte_length ) size_++;
        ptr_=new WKX::Byte[size_];
        for (size_t i=0;i<size_;i++)
        {
            size_t pos=i*byte_length;
            std::string temp(s,pos,byte_length);
            ptr_[i]=WKX::Byte(temp);
        }
        for(size_t i=0;i<s.length();i++){
            std::cout<<s[i];
            if( 0==(i+1) % byte_length ) std::cout<<' ';
        }
        std::cout<<'\n';

    }
//
    BigInt::BigInt(const BigInt& x)
    {
        ptr_= new WKX::Byte[x.size_];
        for (size_t i=0;i<x.size_;i++)
        {
            ptr_[i]=x.ptr_[i];
        }
    }
//
    BigInt& BigInt::operator = (const BigInt& x)
    {
        //assert(size_ == x.size_ );
        if ( this != &x )
            if( size_ != x.size_ ){
                delete []ptr_;
                size_=x.size_;
                ptr_=new WKX::Byte[size_];
                for(size_t i=0;i<size_;i++) ptr_[i]=x.ptr_[i];
            }
        return *this;
    }
//
    BigInt::~BigInt()
    {
        delete []ptr_;
    }
//
    std::istream& operator >> (std::istream& is,BigInt& x)
    {
        std::string temp;
        is>>temp;
        x=BigInt(temp);
        return is;
    }
//
    std::ostream& operator << (std::ostream& os,const BigInt& x)
    {
        std::cout<<"x="<<x.size_<<'\n';
        for (size_t i=0;i<x.size_;i++)
        {
            os<<x.ptr_[i]<<' ';
        }
        return os;
    }
}//end WKX
