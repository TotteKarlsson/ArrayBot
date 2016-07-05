#ifndef abPairedMoveH
#define abPairedMoveH
#include "abExporter.h"
#include "abABObject.h"
#include <string>
//---------------------------------------------------------------------------
using std::string;

class APTMotor;
class AB_CORE PairedMove : public ABObject
{
    public:
                                        PairedMove(const string& name, double d = 0, double v = 0, double a = 0);
                                        ~PairedMove();
		void							assignMotor1(APTMotor* motor);
		void							assignMotor2(APTMotor* motor);
		string            				mLabel;
        double            		        mDistance;
        double            		        mVelocity;
        double            		        mAcceleration;

        bool							execute();
        bool							check();
        string							getCheckMessage();
        string			            	asIniRecord();

    protected:
		APTMotor*						mMotor1;
		APTMotor*						mMotor2;
        string							mCheckMessage;
};

#endif
