#ifndef atCounterH
#define atCounterH
#include "atATObject.h"
//---------------------------------------------------------------------------
typedef void (__closure *CounterCallBack)();

namespace at
{
    class AT_CORE Counter : public ATObject
    {
    	public:
        								Counter();
    		void						increase(int count = 1);
    		void						decrease();
    		void						reset(int count = 0);
            int							getCount();
            int							getLastCount();
            int&		  				getCountReference();
            int&		  				getCountToReference();
    		void 						assignOnCountCallBack(CounterCallBack cb);
    		void 						assignOnCountedToCallBack(CounterCallBack cb);
            void						enable();
            void						disable();
            bool						isEnabled(){return mEnabled;}

        private:
        	int							mCount;
            int							mLastCount;
            int							mCountTo;
            bool						mEnabled;

            							//!The onCountedCallback is called when the counter reaches
                                        //!the mCountTo value
            CounterCallBack				mOnCountedToCallBack;
            CounterCallBack				mOnCountCallBack;
    };

}
#endif
