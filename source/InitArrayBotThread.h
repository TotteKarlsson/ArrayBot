#ifndef InitArrayBotThreadH
#define InitArrayBotThreadH
#include "dslThread.h"

using dsl::Thread;
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *callback)(void);

class ArrayBot;

class PACKAGE InitBotThread : public dsl::Thread
{
	public:
    					InitBotThread();
        void            assingBot(ArrayBot* bot);
    	ArrayBot* 		mTheBot;
        void			run();
        callback		onFinishedInit;
};

#endif
