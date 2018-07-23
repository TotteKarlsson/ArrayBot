#ifndef atDataBaseExporterH
#define atDataBaseExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_DATABASE
    #else
        #if defined(AT_SHARED)
            #define AT_DATABASE __declspec(dllexport)
        #else
            #define AT_DATABASE __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_DATABASE
#endif

#endif
