// ############################################################################
//
//  Project:  Cuc480Dll Dynymic loading of camera dll
//
//  Module:    Dynamic_uc480.cpp  
//
//  Target:    Win32    Win NT
//
// ----------------------------------------------------------------------------
//  History:  Ed   When   Who   What                          in Version
//  -------- ---- ------- ---- ------------------------------ -----------------
//
// ----------------------------------------------------------------------------
//
// ############################################################################

//////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include "dynamic_uc480.h"
#include <tchar.h>

// -------------------------------------------------------------------
// function:      Cuc480Dll()
// description:   constructor
// -------------------------------------------------------------------
Cuc480Dll::Cuc480Dll()
{
  m_hMod = NULL;
}

// -------------------------------------------------------------------
// function:      ~Cuc480Dll()
// description:   destructor
// -------------------------------------------------------------------
Cuc480Dll::~Cuc480Dll()
{
  Disconnect();
}

// -------------------------------------------------------------------
// function:      IsLoaded()
// description:   returns wether the DLL is loaded already or not
// return value:  TRUE  if loaded
//                FALSE if not loaded
// -------------------------------------------------------------------
bool Cuc480Dll::IsLoaded()
{
  return m_hMod!=NULL;
}


// -------------------------------------------------------------------
// function:      _SetPointers()
// description:   Internal function. Sets all the function pointers
// parameters:    Load    TRUE  - load pointers
//                        FALSE - reset pointers to NULL
// return value:  TRUE  if all pointers are set
//                FALSE if some function addresses could not be set
// -------------------------------------------------------------------
bool Cuc480Dll::_SetPointers(bool Load)
{
  int tried  = 0;
  int made   = 0;

#define USB2CAMERA_MACRO_DO(name) tried++;if (!Load) \
                       { \
                         made++; \
                         is_##name=NULL; \
                       } \
                       else \
                       { \
                         if ((is_##name=(IS__##name)GetProcAddress(m_hMod,"is_"#name))!=NULL) \
                           made++; \
                       }
#define DECLARE(pars)

    #include "uc480_macro.h"

#undef DECLARE
#undef USB2CAMERA_MACRO_DO

  return tried==made;

}


// -------------------------------------------------------------------
// function:      Connect()
// description:   Loads the interface DLL and sets function pointers
// parameters:    dllname - name of DLL to load
// return value:  IS_SUCCESS      on successful load
//                IS_NO_SUCCESS   on load error
// -------------------------------------------------------------------
long Cuc480Dll::Connect(const IS_CHAR* dllname)
{
  long lRet = IS_SUCCESS;

  if(dllname != NULL)
  {
    if(strlen(dllname) != 0)
    {
      m_hMod = LoadLibrary(dllname);

      if(m_hMod != NULL)
      {                       
        if(!_SetPointers(true))
        {
          Disconnect();
          lRet = IS_NO_SUCCESS;
        }
      }
      else
        lRet = IS_NO_SUCCESS;
    }
    else
      lRet = IS_NO_SUCCESS;
  }
  else
    lRet = IS_NO_SUCCESS;

  return lRet;
}


// -------------------------------------------------------------------
// function:      Disconnect()
// description:   Resets function pointers and unloads the DLL
// parameters:    <none>
// return value:  IS_SUCCESS      on successful unload
//                IS_NO_SUCCESS   on load error
// -------------------------------------------------------------------
long Cuc480Dll::Disconnect()
{
  _SetPointers(false);
  if(m_hMod != NULL)
    FreeLibrary(m_hMod);
  m_hMod = NULL;
  return IS_SUCCESS;
}




