#ifndef atSerialExporterH
#define atSerialExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_SERIAL
    #else
        #if defined(AT_EXPORT_SERIAL)
            #define AT_SERIAL __declspec(dllexport)
        #else
            #define AT_SERIAL __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_SERIAL
#endif

#endif
