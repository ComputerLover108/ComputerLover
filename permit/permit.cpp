#include "windows.h"

struct file_perms {
  char user_domain[2050];
  unsigned long user_mask;
};


//This function determines the username and domain
void lookup_sid ( ACCESS_ALLOWED_ACE* pACE, char user_domain[] ) {
	char username[1024]="";
	char domain[1024]="";

	ULONG len_username = sizeof(username);
	ULONG len_domain = sizeof(domain);
	PSID pSID =(PSID)(&(pACE->SidStart));
	SID_NAME_USE sid_name_use;         

	if (!LookupAccountSid(NULL, pSID, 
		username, &len_username, domain, &len_domain, &sid_name_use)){  
		strcpy(user_domain, "unknown");
	} else {
		strcat(user_domain,domain);
		strcat(user_domain,"\\");
		strcat(user_domain,username);
	}


}

//Store the mask and username in the file_perms structure.
//call lookup_sid to get the username
void acl_info( PACL pACL, ULONG AceCount, file_perms fp[]){		
	for (ULONG acl_index = 0;acl_index < AceCount;acl_index++){
		ACCESS_ALLOWED_ACE* pACE;
		
		if (GetAce(pACL, acl_index, (PVOID*)&pACE))			
		{		
			char user_domain[2050]="";	
			lookup_sid(pACE,user_domain);
			strcpy(fp[acl_index].user_domain,user_domain);
			fp[acl_index].user_mask=(ULONG)pACE->Mask;
		}
	}
}

static PyObject *get_perms(PyObject *self, PyObject *args)
{

	PyObject *py_perms = PyDict_New();
	//get file or directory name
    char *file;

    if (!PyArg_ParseTuple(args, "s", &file))
        return NULL;

	//setup security code
	PSECURITY_DESCRIPTOR pSD;
	PACL pDACL; 
    //GetNamedSecurityInfo() will give you the DACL when you ask for
    //DACL_SECURITY_INFORMATION. At this point, you have SIDs in the ACEs contained in the DACL. 
	ULONG result = GetNamedSecurityInfo(file,SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, 
	&pDACL, NULL, &pSD);

	if (result != ERROR_SUCCESS){ return NULL;}
	if (result == ERROR_SUCCESS){
		ACL_SIZE_INFORMATION aclSize = {0};
		if(pDACL != NULL){   
			if(!GetAclInformation(pDACL, &aclSize, sizeof(aclSize),
				AclSizeInformation)){
				return NULL;
			}
		}
	
		file_perms *fp = new file_perms[aclSize.AceCount];
		acl_info(pDACL, aclSize.AceCount, fp );
		
		//Dict
		for (ULONG i=0;i




//Boilerplate functions

//3 parts 
//name of python function
//C++ function
//flags METH_VARARGS means function takes variable number of args
static PyMethodDef fileperm_methods[] = {
	{ "get_perms", get_perms, METH_VARARGS },
	{ NULL }
};



void initfileperm()
{

Py_InitModule("fileperm",fileperm_methods);

}

