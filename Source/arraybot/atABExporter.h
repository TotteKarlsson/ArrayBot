#ifndef atABExporterH
#define atABExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_AB
    #else
        #if defined(AT_EXPORT_AB)
            #define AT_AB __declspec(dllexport)
        #else
            #define AT_AB __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_AB
#endif

#endif
