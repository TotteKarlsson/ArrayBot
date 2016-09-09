#ifndef abRibbonLengthControllerH
#define abRibbonLengthControllerH
#include "abExporter.h"
#include "abABObject.h"
//---------------------------------------------------------------------------

class ArduinoServer;

class AB_CORE RibbonLengthController : public ABObject
{
    public:
						                    RibbonLengthController(ArduinoServer& s);
						                    ~RibbonLengthController();

                                            //!The check function checks the status
                                            //!of the current length of the ribbon.
                                            //!If ribbon separation is enabled, autopuff and
                                            //!auto zerocut will prepare the HW for puffing and
                                            //!zerocutting in order to obtain a ribbon of proper
                                            //!length
		void								check();

        									//!A manual puff overrides the automatic puff
                                            //!initiated by the enablePuffer command.
                                            //!manualPuff simply sets off the puffer manually
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

        void								enablePuffer();
        void								enableAutoZeroCut();
        void								disableAutoZeroCut();
        bool								getAutoZeroCutSetting();

        int									getDesiredRibbonLength();
        void								setDesiredRibbonLength(int r);

	protected:
    	ArduinoServer&			            mArduinoServer;

 		int									mCutThicknessPreset;

									        //!The section count is compared to the mDesiredRibbonLength
                                            //used for emitting a puff
        int						            mSectionCount;

        									//!The desired ribbon length is used
                                            //!to make the decision on when to separate the
                                            //!ribbon
        int									mDesiredRibbonLength;

        bool								mAutoPuff;
        bool								mAutoZeroCut;

};
#endif
