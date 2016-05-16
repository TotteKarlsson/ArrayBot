#ifndef abMotorMessageCreatorH
#define abMotorMessageCreatorH
#include "abExporter.h"
#include <string>
#include "abABObject.h"
#include "mtkThread.h"
#include "mtkConstants.h"
//---------------------------------------------------------------------------

class AB_CORE MotorMessageCreator : public mtk::Thread, public ABObject
{
	public:
													MotorMessageCreator(const string& threadName = mtk::gEmptyString);
													~MotorMessageCreator();

													// overridden from Thread
		void                                        run();
		virtual void                                worker();
		void                                        stop();
		void										setRepeatRate(int rate);

		bool                                        start(bool in_thread = true);

	protected:

		int											mRepeatRate;

};

#endif
