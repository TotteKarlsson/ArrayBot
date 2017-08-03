#ifndef InitArrayBotThreadH
#define InitArrayBotThreadH
#include "mtkThread.h"

using mtk::Thread;
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *callback)(void);

class ArrayBot;

class PACKAGE InitBotThread : public mtk::Thread
{
	public:
    					InitBotThread();
        void            assingBot(ArrayBot* bot);
    	ArrayBot* 		mTheBot;
        void			run();
        callback		onFinishedInit;
};

#endif
