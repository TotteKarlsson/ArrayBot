#ifndef atCoreExporterH
#define atCoreExporterH

#if defined (_WIN32)
    #if defined(AT_EXPORT_CORE)
        #define AT_CORE __declspec(dllexport)
    #else
        #define AT_CORE __declspec(dllimport)
    #endif
#else
    #define AT_CORE
#endif

#endif
