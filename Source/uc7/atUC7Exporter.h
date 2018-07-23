#ifndef atUC7ExporterH
#define atUC7ExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_UC7
    #else
        #if defined(AT_EXPORT_UC7)
            #define AT_UC7 __declspec(dllexport)
        #else
            #define AT_UC7 __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_UC7
#endif

#endif
