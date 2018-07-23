#pragma hdrstop
#include "atResourceManager.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;

ResourceManager::ResourceManager()
{
	mModuleHandle = NULL;
	loadResourceDLL();
}

ResourceManager::~ResourceManager()
{}

bool ResourceManager::loadResourceDLL()
{
	mModuleHandle = GetModuleHandle("atResources.dll");
    if(!mModuleHandle)
    {
    	Log(lError) << "Failed to load resource DLL";
		return false;
    }
	return true;
}

StringList ResourceManager::loadAllResources()
{
    mResources.clear();
	if (mModuleHandle)
 	{
		EnumResourceTypes((HMODULE) mModuleHandle, (ENUMRESTYPEPROC) EnumTypesFunc,(LONG) &mResources);
  	}
  	return mResources;
}

bool ResourceManager::findResource(int res, const string& type)
{
	if (!mModuleHandle)
    {
    	return false;
    }
    HRSRC hRes = ::FindResourceA((HMODULE) mModuleHandle, MAKEINTRESOURCE(res), type.c_str());

 	return (hRes == NULL) ? false : true;
}

bool ResourceManager::EnumTypesFunc(HANDLE hModule, LPSTR lpType, LONG lParam)
{
	EnumResourceNames((HINSTANCE) hModule, lpType, (ENUMRESNAMEPROC) EnumNames, lParam);
    return true;
}

bool ResourceManager::EnumNames(HANDLE hModule, LPCTSTR lpType, LPTSTR lpName, LONG lParam)
{
	StringList *r = (StringList*) lParam;
	ResourceInfo info;

    if((ULONG)lpName & 0xFFFF0000)
    {
		info.mName = lpName;
    }

	if ((ULONG)lpType & 0xFFFF0000)
    {
       info.mType = lpType;
    }

	if(r)
    {
    	//Only append if resource size is larger than a few bytes
	    HRSRC hRes = ::FindResourceA((HMODULE) hModule, lpName, lpType);

		DWORD sz = SizeofResource((HMODULE)hModule, hRes);

        if(sz > 256)
        {
			r->append(info.mName);
        }
    }

    return true;
}


