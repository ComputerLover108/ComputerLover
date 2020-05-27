#include <windows.h>
#ifndef CHDIR_H
#define CHDIR_H
class chdir
{
public:
    chdir();
    ~chdir();
	void cd(const char* name);
	private:
		char m_s[MAX_PATH];
};
#endif