#include <windows.h>
#include <iostream>
int main(int argc,char* argv[])
{
		SECURITY_INFORMATION secInfo = DACL_SECURITY_INFORMATION;
		// 和文件相关的安全描述符 SD 的变量
		PSECURITY_DESCRIPTOR pFileSD  = NULL;     // 结构变量
		DWORD          cbFileSD       = 0;        // SD的size
		char lpszFileName[MAX_PATH];
		strncpy(lpszFileName,argv[1],MAX_PATH);
		BOOL fAPISuccess=0;
		fAPISuccess = GetFileSecurity(lpszFileName,secInfo, pFileSD, 0, &cbFileSD);
    return 0;
}