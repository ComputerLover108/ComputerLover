////
#include <string>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>
//
#ifndef helpH
#define helpH
//
namespace WKX
{
    const int BYTE_LENGTH=8; //假定一个字节8位
    void binaryPrint(unsigned char c);
    class Byte
    {
    public:
        Byte(const unsigned char c=0):ch_(c) {};
        Byte(const char cs[BYTE_LENGTH]);
        friend Byte& operator + (const Byte& x,const Byte& y);
        friend Byte& operator * (const Byte& x,const Byte& y);
    protected:
        friend std::ostream& operator << (std::ostream& out,const Byte& b);
        friend std::istream& operator >> (std::istream& in,Byte& b);
    private:
        unsigned char ch_;
    };
    //
    template <typename T>
    class MemoryMap;
    template <typename T>
    std::ostream& operator<< (std::ostream& out, MemoryMap<T>& x);
    template <>
    std::ostream& operator<< <char*>(std::ostream& out,MemoryMap<char*>& x);//必须有，不然不特例
//
    template <typename T>
    class MemoryMap
    {
    public:
        MemoryMap(const T x):data_(x) {};
    protected:
        friend std::ostream& operator<< <T>(std::ostream& out, MemoryMap<T>& x);
        friend std::ostream& operator<< <char*>(std::ostream& out,MemoryMap<char*>& x);
    private:
        T data_;
    };
//
    template <typename T>
    std::ostream& operator<< (std::ostream& out, MemoryMap<T>& x)
    {
        size_t length=sizeof(x.data_);
        Byte* p=reinterpret_cast<Byte*>(&x.data_);
        for (size_t i=0;i<length;i++)
        {
            assert( i<length );
            out<<*p++<<' ';
        }
        return out;
    }
//
    template<class C, class P> void erase_if(C & c, P pred)
    {
        c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
    }
//
    template<class InIt,class OutIt,class P> inline
    OutIt copy_if(InIt First, InIt Last, OutIt Dest, P Pred)
    {
        // copy omitting each element satisfying _Pred
        for (; First != Last; ++First)
            if ( Pred(*First) )
                *Dest++ = *First;
        return (Dest);
    }
    //
    namespace NUMERIC{
        void print(int n,int base=2);
        void print(long n,int base=2);
    }
}//end namespace WKX
//
#endif //helH
