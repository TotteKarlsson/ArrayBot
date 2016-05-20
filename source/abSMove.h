#ifndef abSMoveH
#define abSMoveH
#include "abExporter.h"
#include "abABObject.h"
#include "abPosition.h"
//---------------------------------------------------------------------------

//!The move baseclass contain the general logic for a 'move' of
//any type of object
class AB_CORE SMove : public ABObject
{
    public:
        				SMove(ABObject* unit, const ab::Position& p, double maxVel = 0, double acc = 0, double dwellTime = 0);
    	virtual			~SMove(){}
		void			assignUnit(ABObject* o){mUnit = o;}
        virtual bool	execute() = 0;
        virtual	bool	undo() = 0;
        virtual bool	isActive() = 0;
        virtual string	getType() = 0;
        virtual bool	achievedPosition() = 0;

        ab::Position&	getPosition(){return mPosition;}
        double			getMaxVelocity(){return mMaxVelocity;}
        double			getAcceleration(){return mAcceleration;}
        double			getDwellTime(){return mDwellTime;}

        bool 			setPosition(const ab::Position& pos){mPosition = pos; return true;}
        bool			setMaxVelocity(double v){mMaxVelocity = v; return true;}
        bool			setAcceleration(double a){mAcceleration = a; return true;}
        bool			setDwellTime(double dt){mDwellTime = dt; return true;}

        string			getPositionName(){return mPosition.getLabel();}
        void			setPositionName(const string& l){mPosition.setLabel(l);}

    protected:
    					//!Making object for moving abstract allow us
                        //to move 'any' object. Just specialize in the
                        //execute function..
    	ABObject* 		mUnit;

        				//!The exact meaning of the position attribute is
                        //made clear in derived classes
        ab::Position    mPosition;
        double			mMaxVelocity;
        double			mAcceleration;
        double			mDwellTime;
};

#endif
