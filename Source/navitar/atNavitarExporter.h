#ifndef atNavitarExporterH
#define atNavitarExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_NAVITAR
    #else
        #if defined(AT_EXPORT_NAVITAR)
            #define AT_NAVITAR __declspec(dllexport)
        #else
            #define AT_NAVITAR __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_NAVITAR
#endif

#endif
