#ifndef atBarcodeExporterH
#define atBarcodeExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_BCR
    #else
        #if defined(AT_EXPORT_BARCODEREADER)
            #define AT_BCR __declspec(dllexport)
        #else
            #define AT_BCR __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_BCR
#endif

#endif
