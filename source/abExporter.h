#ifndef abExporterH
#define abExporterH

#if defined (_WIN32)
    #if defined(AB_STATIC)
        #define AB_CORE
    #else
        #if defined(AB_SHARED)
            #define AB_CORE __declspec(dllexport)
        #else
            #define AB_CORE __declspec(dllimport)
        #endif
    #endif
#else
    #define AB_CORE
#endif

#endif
