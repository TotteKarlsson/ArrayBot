#ifndef atDBCoreExporterH
#define atDBCoreExporterH

#if defined (_WIN32)
    #if defined(ATDB_CORE_STATIC)
        #define ATDB_CORE
    #else
        #if defined(ATDB_EXPORT_CORE)
            #define ATDB_CORE __declspec(dllexport)
        #else
            #define ATDB_CORE __declspec(dllimport)
        #endif
    #endif
#else
    #define ATDB_CORE
#endif

#endif
