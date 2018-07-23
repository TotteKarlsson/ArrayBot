#ifndef atCameraExporterH
#define atCameraExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_CAMERA
    #else
        #if defined(AT_EXPORT_CAMERA)
            #define AT_CAMERA __declspec(dllexport)
        #else
            #define AT_CAMERA __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_CAMERA
#endif

#endif
