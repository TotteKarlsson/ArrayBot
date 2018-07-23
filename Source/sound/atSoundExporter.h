#ifndef atSoundExporterH
#define atSoundExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_SOUND
    #else
        #if defined(AT_EXPORT_SOUND)
            #define AT_SOUND __declspec(dllexport)
        #else
            #define AT_SOUND __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_SOUND
#endif

#endif
