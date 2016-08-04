//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
//###########################################################################//
//#                                                                         #//
//# Dynamic_uc480.h: interface for the dynamic loading of the api dll       #//
//#                                                                         #//
//#     (c) 2004 - 2014                                                     #//
//#                                                                         #//
//###########################################################################//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///

#ifndef _DYNAMIC_API_H_
#define _DYNAMIC_API_H_

#include "uc480.h"

#define USB2CAMERA_MACRO_DO(name) typedef INT (__cdecl* IS__##name)
#define DECLARE(pars) pars;
  #include "uc480_macro.h"
#undef DECLARE
#undef USB2CAMERA_MACRO_DO

#include "abExporter.h"

class AB_CORE Cuc480Dll
{
    public:
      										Cuc480Dll();
      virtual 								~Cuc480Dll();

      bool 									IsLoaded();

      // Declare functions
      #define USB2CAMERA_MACRO_DO(name) IS__##name is_##name ;
      #define DECLARE(pars)
      #include "uc480_macro.h"
      #undef DECLARE
      #undef USB2CAMERA_MACRO_DO

    protected:
      HMODULE 								m_hMod; // module handle

    public:
      long                                 	Connect(const IS_CHAR* dllName);
      long                            		Disconnect();

    private:
      bool 									_SetPointers(bool Load);
};

#endif


