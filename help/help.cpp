#include <iostream>
#include <cstring>
#include "help.h"
namespace WKX
{
    //
    namespace NUMERIC{
        void print(int n,int base){
        }
        //
        void print(long n,int base){
        }
    }
    void binaryPrint(unsigned char c)
    {
        for (int i = BYTE_LENGTH-1; i >= 0; i--)
        {
            if ( c & (1 << i) )
                std::cout << '1';
            else
                std::cout << '0';
        }
    }
    //
    Byte& operator + (const Byte& x,const Byte& y)
    {
        Byte result;
        result.ch_=x.ch_ & y.ch_;
        return result;
    }
    Byte& operator * (const Byte& x,const Byte& y)
    {
        Byte result;
        return result;
    }
    //
    Byte::Byte(const char cs[BYTE_LENGTH] )
    {
        ch_=0;
        size_t length=std::strlen(cs);
        assert( length <= BYTE_LENGTH+1); //"00001111"
        int count=BYTE_LENGTH;
        if(length < BYTE_LENGTH ) count=length;
        for ( int i=0;i<count;i++)
        {
            if ( '1'==cs[i] )
            {
                int position=count-1-i;
                ch_ |= ( 1<< position) ;
            }
        }
    }
    //
    std::istream& operator >> (std::istream& in,Byte& x)
    {
        in>>x;
        return in;
    }
//
    std::ostream& operator << (std::ostream& out,const Byte& x)
    {
        for (int i = BYTE_LENGTH-1; i >= 0; i--)
        {
            if ( x.ch_ & (1 << i) )
                out << '1';
            else
                out << '0';
        }
        return out;
    }

//
} //end namespace WKX
