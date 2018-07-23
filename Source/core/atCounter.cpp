#pragma hdrstop
#include "atCounter.h"
//---------------------------------------------------------------------------

namespace at
{
    Counter::Counter()
    :
    mCount(0),
    mCountTo(10),
    mOnCountCallBack(NULL),
    mOnCountedToCallBack(NULL),
    mEnabled(false)
    {}

    void Counter::increase(int count)
    {
    	if(!mEnabled)
        {
        	return;
        }

    	mCount += count;

        //Check....
        if(mCount >= mCountTo)
        {
            if(mOnCountedToCallBack)
            {
                mOnCountedToCallBack();
            }
        }

        if(mOnCountCallBack)
        {
            mOnCountCallBack();
        }
    }

    void Counter::decrease()
    {
    	if(!mEnabled)
        {
        	return;
        }

    	mCount--;
        if(mCount <= mCountTo)
        {
        	if(mOnCountCallBack)
            {
            	mOnCountCallBack();
            }
        }
    }

    void Counter::reset(int count)
    {
    	mLastCount = mCount;
    	mCount = count;
    }

    int	Counter::getLastCount()
    {
    	return mLastCount;
    }

    int	Counter::getCount()
    {
    	return mCount;
    }

    int& Counter::getCountReference()
    {
    	return mCount;
    }

    int& Counter::getCountToReference()
    {
    	return mCountTo;
    }

    void Counter::assignOnCountCallBack(CounterCallBack cb)
    {
    	mOnCountCallBack = cb;
    }

    void Counter::assignOnCountedToCallBack(CounterCallBack cb)
    {
    	mOnCountedToCallBack = cb;
    }

    void Counter::enable()
    {
    	mEnabled = true;
    }

    void Counter::disable()
    {
    	mEnabled = false;
    }
}
