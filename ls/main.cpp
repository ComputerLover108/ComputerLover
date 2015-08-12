#include "windows.h"
#include "string.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
   WIN32_FIND_DATA FindFileData;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   char DirSpec[MAX_PATH];  // directory specification
   DWORD dwError;

   printf ("Target directory is %s.\n", argv[1]);
   strncpy (DirSpec, argv[1], strlen(argv[1])+1);
   strncat (DirSpec, "\\*", 3);

   hFind = FindFirstFile(DirSpec, &FindFileData);

   if (hFind == INVALID_HANDLE_VALUE) 
   {
      printf ("Invalid file handle. Error is %u\n", GetLastError());
      return (-1);
   } 
   else 
   {
      printf ("First file name is %s\n", FindFileData.cFileName);
      while (FindNextFile(hFind, &FindFileData) != 0) 
      {
         printf ("Next file name is %s\n", FindFileData.cFileName);
      }
    
      dwError = GetLastError();
      FindClose(hFind);
      if (dwError != ERROR_NO_MORE_FILES) 
      {
         printf ("FindNextFile error. Error is %u\n", dwError);
         return (-1);
      }
   }
   return (0);
}
