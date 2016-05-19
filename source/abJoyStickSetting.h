#ifndef abJoyStickSettingH
#define abJoyStickSettingH
#include "abExporter.h"
#include "abABObject.h"
#include <string>
#include <vector>
//---------------------------------------------------------------------------
using std::string;
using std::vector;

class AB_CORE JoyStickSetting : public ABObject
{
    public:
 				       	JoyStickSetting(const string& lbl, double maxXYVel = 0, double xyAcc = 0, double maxZVel = 0, double zAcc = 0);
                       	~JoyStickSetting();
		void			setLabel(const string& lbl){mLabel = lbl;}
		string  		getLabel(){return mLabel;}
        vector<double> 	get();
        void			set(double maxXYVel, double xyAcc, double maxZVel, double zAcc);
        string			asIniRecord();

    protected:
		string			mLabel;
		double			mMaxXYVelocity;
        double			mXYAcceleration;
        double 			mMaxZVelocity;
        double			mZAcceleration;



};
#endif
