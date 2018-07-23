#ifndef atFocusControllerH
#define atFocusControllerH
#include "dslRange.h"
#include <deque>
//---------------------------------------------------------------------------

using dsl::Range;
using std::deque;

class FocusController
{
    public:
                                        FocusController();
                                        ~FocusController();

        void                            onScore();
	    double                          setNewFocus();
        string                          getSnapShotFileName();

    protected:
    	Range<int>                      mFocusRange;
        double                          mStepFocus;
        string                          mLiveImagePath;
        string                          mLiveImageFileName;
        string                          mSharpnessFileName;
        deque<double>                   mScores;


                                        //!In seconds
        double                          mImageUpdateIntervall;
};
#endif
