#ifndef amlCoreExporterH
#define amlCoreExporterH

#if defined (_WIN32)
    #if defined(AML_STATIC)
        #define AML_CORE
    #else
        #if defined(AML_SHARED)
            #define AML_CORE __declspec(dllexport)
        #else
            #define AML_CORE __declspec(dllimport)
        #endif
    #endif
#else
    #define AML_CORE
#endif

#endif
