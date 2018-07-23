#ifndef atArduinoExporterH
#define atArduinoExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_ARDUINO
    #else
        #if defined(AT_EXPORT_ARDUINO)
            #define AT_ARDUINO __declspec(dllexport)
        #else
            #define AT_ARDUINO __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_ARDUINO
#endif

#endif
