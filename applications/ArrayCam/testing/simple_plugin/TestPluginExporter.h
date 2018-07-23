#ifndef TestPluginExporterH
#define TestPluginExporterH

#if defined(_WIN32)
    #if defined(EXPORT_PLUGIN)
        #define EXPORTED __declspec(dllexport)
    #else
        #define EXPORTED __declspec(dllimport)
    #endif
#else
    #define EXPORTED
#endif

#endif

