#ifndef atDBExporterH
#define atDBExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_DB
    #else
        #if defined(AT_EXPORT_DB)
            #define AT_DB __declspec(dllexport)
        #else
            #define AT_DB __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_DB
#endif

#endif
