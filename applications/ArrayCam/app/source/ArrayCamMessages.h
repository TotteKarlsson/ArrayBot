#ifndef ArrayCamMessagesH
#define ArrayCamMessagesH

//#define UWM_AM_MESSAGE            	(WM_APP + 1)

#define UWM_MESSAGE      	  	(WM_APP + 5)
#define UWM_AM_MESSAGE          (WM_APP + 50)


enum ApplicationMessageEnum
{
    atUC7SplashWasClosed = 0,
    atUC7Message = 1,
    atMiscMessage = 2,
    atEnableResumeBtn = 3
};


#endif
