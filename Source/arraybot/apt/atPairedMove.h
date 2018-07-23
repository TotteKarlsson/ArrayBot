#ifndef atPairedMoveH
#define atPairedMoveH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include <string>
//---------------------------------------------------------------------------
using std::string;

namespace at
{
    class APTMotor;
    class AT_AB PairedMove : public ATObject
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
}

#endif
