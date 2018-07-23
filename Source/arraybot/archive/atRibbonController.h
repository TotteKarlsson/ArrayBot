#ifndef atRibbonControllerH
#define atRibbonControllerH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
//---------------------------------------------------------------------------

class ArduinoServer;

class AT_AB RibbonController : public ATObject
{
    public:
						                    RibbonController(ArduinoServer& s);
						                    ~RibbonController();

                                            //!The check progress function checks the status
                                            //!of the current length of the ribbon.
                                            //!If ribbon separation is enabled, autopuff and
                                            //!auto zerocut will prepare the hardware for puffing and
                                            //!zerocutting in order to obtain a ribbon of proper
                                            //!length
		void								checkProgress();

        									//!A manual puff overrides the automatic puff
                                            //!initiated by the enablePuffer command.
                                            //!manualPuff simply sets off the puffer manually and instantly
		bool								manualPuff();

        bool								setZeroCut();
        bool								setCutThicknessPreset(int preset);
        int									getCutThicknessPreset();
        int									getSectionCount();

        void								incrementSectionCount();
	    void								setSectionCount(int r);
		void								resetSectionCount();

        void								enableAutoPuff();
        void								disableAutoPuff();
        bool								getAutoPuffSetting();

        bool								enablePuffer();
        bool								disablePuffer();
        void								enableAutoZeroCut();
        void								disableAutoZeroCut();
        bool								getAutoZeroCutSetting();

        void								prepareForNewRibbon();

        int									getDesiredRibbonLength();
        void								setDesiredRibbonLength(int n);

	protected:
    	ArduinoServer&			            mArduinoServer;

        									//!Flag to use to reset the controller
        bool								mPrepareForNewRibbon;

        									//!Use this to restore from 0 cut thickness preset
        int									mLastCutThicknessPreset;

									        //!The section count is compared to the mDesiredRibbonLength
                                            //used for emitting a puff
        int						            mSectionCount;

        									//!The desired ribbon length is used
                                            //!to make the decision on when to separate the
                                            //!ribbon
        int									mDesiredRibbonLength;

        									//!If auto puff is true, puffer is enabled
                                            //is set when section count == desiredRibbon length
        bool								mAutoPuff;

        									//!If auto zero cut is true, zero thickness cut
                                            //is set when section count == desiredRibbon length
        bool								mAutoZeroCut;

};
#endif
