#ifndef ibExporterH
#define ibExporterH

#if defined (_WIN32)
    #if defined(IB_STATIC)
        #define IB_CORE
    #else
        #if defined(AB_SHARED)
            #define IB_CORE __declspec(dllexport)
        #else
            #define IB_CORE __declspec(dllimport)
        #endif
    #endif
#else
    #define IB_CORE
#endif

#endif
