#include "windows.h"
#include <lmerr.h>

#include "string.h"
#include "stdio.h"
//
int pathList(const char* dir);
void DisplayErrorText(DWORD dwLastError);
//
int main(int argc, char *argv[])
{
	return pathList(argv[1]);
}
//
int pathList(const char* dir){
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char DirSpec[MAX_PATH];  // directory specification
	DWORD dwError;

	printf ("Target directory is %s.\n", dir);
	strncpy (DirSpec, dir, strlen(dir)+1);
	strncat (DirSpec, "\\*", 3);
	
	char DirBuffer[MAX_PATH];
	strncpy (DirBuffer, dir, strlen(dir)+1);

	hFind = FindFirstFile(DirSpec, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE) 
	{
		printf ("Invalid file handle. Error is %u\n", GetLastError());
		DisplayErrorText(GetLastError() );
		return (-1);
	} 
	else 
	{
		//printf( "%d\n", FindFileData.dwFileAttributes);
		printf ("%s\n", FindFileData.cFileName);
		//
		while (FindNextFile(hFind, &FindFileData) != 0) 
		{
			//printf( "%d\n", FindFileData.dwFileAttributes);
			char FileName[MAX_PATH];
			strncpy(FileName,DirBuffer,strlen(DirBuffer)+1);
			strncpy(FileName,FindFileData.cFileName,strlen(FindFileData.cFileName)+1);
			printf ("%s\n", FileName );
			if( FindFileData.dwFileAttributes &= FILE_ATTRIBUTE_DIRECTORY){
            // ºöÂÔ.ºÍ..
            if ( 0==strcmp(FindFileData.cFileName, ".") || 0==strcmp(FindFileData.cFileName, "..")){
			}
			else{	
				pathList(FileName);
			}
			}
		}
		dwError = GetLastError();
		if(0 == FindClose(hFind) ){
			DisplayErrorText(GetLastError() );
			return (-1);
		};
		if (dwError != ERROR_NO_MORE_FILES) 
		{
			printf ("FindNextFile error. Error is %u\n", dwError);
			DisplayErrorText(GetLastError() );
			return (-1);
		}
	}
	return 0;
}
//
void DisplayErrorText(DWORD dwLastError)
{
	HMODULE hModule = NULL; // default to system source
	LPSTR MessageBuffer;
	DWORD dwBufferLength;

	DWORD dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
	FORMAT_MESSAGE_IGNORE_INSERTS |
	FORMAT_MESSAGE_FROM_SYSTEM ;

	//
	// If dwLastError is in the network range, 
	//  load the message source.
	//

	if(dwLastError >= NERR_BASE && dwLastError <= MAX_NERR) {
		hModule = LoadLibraryEx(
		TEXT("netmsg.dll"),
		NULL,
		LOAD_LIBRARY_AS_DATAFILE
		);

		if(hModule != NULL)
		dwFormatFlags |= FORMAT_MESSAGE_FROM_HMODULE;
	}

	//
	// Call FormatMessage() to allow for message 
	//  text to be acquired from the system 
	//  or from the supplied module handle.
	//

	if(dwBufferLength = FormatMessageA(
				dwFormatFlags,
				hModule, // module to get message from (NULL == system)
				dwLastError,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
				(LPSTR) &MessageBuffer,
				0,
				NULL
				))
	{
		DWORD dwBytesWritten;

		//
		// Output message string on stderr.
		//
		WriteFile(
		GetStdHandle(STD_ERROR_HANDLE),
		MessageBuffer,
		dwBufferLength,
		&dwBytesWritten,
		NULL
		);

		//
		// Free the buffer allocated by the system.
		//
		LocalFree(MessageBuffer);
	}

	//
	// If we loaded a message source, unload it.
	//
	if(hModule != NULL)
	FreeLibrary(hModule);
}
//
