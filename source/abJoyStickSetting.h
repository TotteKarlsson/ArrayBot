#ifndef abJoyStickSettingH
#define abJoyStickSettingH
#include "abExporter.h"
#include "abABObject.h"
#include <string>
#include <vector>
//---------------------------------------------------------------------------
using std::string;
using std::vector;

//! The JoystickSetting class holds motor settings for all motors.
/*!The settings are saved/retrieved from a INI file.
*/
class AB_CORE JoyStickSetting : public ABObject
{
    public:
 				       	            JoyStickSetting(const string& lbl, 	double XYVel = 0, double xyAcc = 0,
                                    									double ZVel = 0, double zAcc = 0,
                                                                        double angleVel = 0, double angleAcc = 0);
                       	            ~JoyStickSetting();
		void			            setLabel(const string& lbl){mLabel = lbl;}
		string  		            getLabel(){return mLabel;}
        vector<double> 	            get();
        void			            set(double XYVel, double XYAcc, double ZVel, double ZAcc, double angleVelocity, double angleAcc);
        string			            asIniRecord();

    protected:
		string			            mLabel;
		double			            mXYVelocity;
        double			            mXYAcceleration;
        double 			            mZVelocity;
        double			            mZAcceleration;
        double			            mAngleControllerVelocity;
        double			            mAngleControllerAccleration;

};
#endif
