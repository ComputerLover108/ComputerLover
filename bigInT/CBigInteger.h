#ifndef __CBigInteger__
#define __CBigInteger__ 4096
#include <stdio.h>
class CBigInteger
{
private:
	char data[__CBigInteger__];
	char chmode[__CBigInteger__ + 1];
	int toDec(char k)
	{
		if (k >= '0' && k <= '9') return k - '0';
		printf("toDec(%c)=%d\n",k,k-'0');
		if (k >= 'a' && k <= 'f') return k - 'a' + 10;
		printf("toDec(%c)=%d\n",k,k-'a'+10);
		if (k >= 'A' && k <= 'F') return k - 'A' + 10;
		printf("toDec(%c)=%d\n",k,k-'A'+10);
		return -1;
	}
public:
	CBigInteger(const char* toParse = "1", bool ignoreElse = false)
	{
		Parse(toParse, ignoreElse);
	}
	CBigInteger(unsigned long int toParse)
	{
		char a[100];
		sprintf(a, "%lu", toParse);
		Parse(a, false);
	}
	const char* toString()
	{
		int i;
		for (i = __CBigInteger__ - 1; i >= 0; i--)
		{
			chmode[__CBigInteger__ - 1 - i] = data[i] + '0';
		}
		chmode[__CBigInteger__] = 0;
		i = 0;
		while (chmode[i] == '0') i++;
		if (!chmode[i]) i--;
		return chmode + i;
	}
	bool Parse(const char* ch, bool ignoreElse = false)
	{
		if (ch[0] == '0' && (ch[1] == 'x' || ch[1] =='X'))//16进制
		{
			/*
			*this = "0";
			CBigInteger nowhex = "1";
			CBigInteger temp;
			ch++; ch++;
			int len = 0;
			for (; ch[len]; len++);//没看懂，很奇怪的用法
			for (int i = len - 1; i >= 0; i--)
			{
				if (toDec(ch[i]) == -1)
				{
					if (!ignoreElse) return false;
				}
				else//很奇怪的16进制转10进制方法
				{
					temp = nowhex;
					for (int j = 1; j < toDec(ch[i]); j++)
					{
						temp = temp + nowhex;
					}
					nowhex = nowhex + nowhex;
					nowhex = nowhex + nowhex;
					nowhex = nowhex + nowhex;
					nowhex = nowhex + nowhex;
					*this = *this + temp;
				}
			*/	
			}
			return true;
		}
		else
		{
			int offset = 0;
			for (int i = 0; i < __CBigInteger__; i++) data[i] = 0;
			int len = 0;
			for (; ch[len]; len++);//没看懂，很奇怪的用法
			printf("ch[%d]:\t%s\n",len,ch);
			/*
			好像目的是
			ch="12345" --> data="000..00012345"
			不知道理解对吗？如果是这样，进行如下修改。
			*/
			for (int i = len - 1; i >= 0; i--)
			{
				if (ch[i] >= '0' && ch[i] <= '9')
				{
					int temp=__CBigInteger__-len+i;
					data[temp] = ch[i];
					printf("data[%d]=%c\tch[%d]=%c\n",temp,data[temp],i,ch[i]);
				}
				else
				{
					if (ignoreElse) offset++;
					else return false;
				}
			}
			//
			printf("ch[]:\t%s\ndata[]:\t%s\n",ch,data);
			return true;
		}
	}
	const CBigInteger operator + (const CBigInteger another)
	{
		CBigInteger result = another;
		for (int i = 0; i < __CBigInteger__; i++)
		{
			result.data[i] += this->data[i];
			if (result.data[i] > 9)
			{
				result.data[i + 1]++;
				result.data[i] -= 10;
			}
		}
		return result;
	}
};
#endif