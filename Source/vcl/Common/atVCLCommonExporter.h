#ifndef atVCLCommonExporterH
#define atVCLCommonExporterH

///////////////////////////////////////////////////////////////

#if defined (_WIN32)
	#if defined(AT_VCLCOMMON_STATIC)
		#define VCLCOMMON
	#else
		#if defined(AT_EXPORT_VCLCOMMON)
			#define AT_VCLCOMMON __declspec(dllexport)
		#else
			#define AT_VCLCOMMON __declspec(dllimport)
		#endif
	#endif
#else
	#define AT_VCLCOMMON
#endif

#pragma warn -8118
#endif
