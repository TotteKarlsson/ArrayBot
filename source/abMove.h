#ifndef abMoveH
#define abMoveH
#include "abExporter.h"
#include "abProcess.h"
#include "abPosition.h"
//---------------------------------------------------------------------------

namespace ab
{

//enum MoveType {mtAbsolute = 0, mtRelative, mtContinous, mtUnknown};
//MoveType	toMoveType(const string& mt);
//string		toString(MoveType mt);

//!The move baseclass contain the general logic for a 'move' of
//any type of object
class AB_CORE Move : public Process
{
    public:
        	   			            Move(const string& lbl, double maxVel = 0, double acc = 0);
    	virtual			            ~Move(){}

        string						getMotorName(){return mMotorName;}
        void						setMotorName(const string& n){mMotorName = n;}

		virtual mtk::XMLElement*    addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot) = 0;
		virtual void	            assignUnit(ABObject* o);


        virtual bool	            stop();
        virtual bool	            isBeingProcessed();
        bool 						isProcessed();
		bool						isMotorCommandPending();
        virtual	bool	            undo();

									//!Any subclass need to implement these
        virtual bool 				isDone() = 0;
        virtual bool	            start() = 0;

        bool	            		isMotorActive();

        							//!MotorVelocity
        bool			            setMaxVelocity(double v){mMaxVelocity = v; return true;}
        double			            getMaxVelocity(){return mMaxVelocity;}

        							//!Motor acceleration
        bool			            setAcceleration(double a){mAcceleration = a; return true;}
        double			            getAcceleration(){return mAcceleration;}

    protected:
        string						mMotorName;
        double			            mMaxVelocity;
        double			            mAcceleration;
};

}
#endif
