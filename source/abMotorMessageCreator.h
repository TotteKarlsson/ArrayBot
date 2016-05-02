#ifndef abMotorMessageCreatorH
#define abMotorMessageCreatorH
#include "AMLCoreExporter.h"
#include <string>
#include "mtkThread.h"
#include "mtkConstants.h"
//---------------------------------------------------------------------------
class Account;

using namespace mtk;

class AML_CORE MotorMessageCreator : public mtk::Thread
{
	public:
													MotorMessageCreator(const string& threadName=gEmptyString);
													~MotorMessageCreator();
		void										setAccount(Account* acc);
													// overridden from Thread
		void                                        run();
		virtual void                                worker();
		void                                        stop();
		void										setRepeatRate(int rate);

		bool                                        start(bool in_thread = true);

	protected:
		Account*            		                mAccount;
		int											mRepeatRate;

};

#endif
