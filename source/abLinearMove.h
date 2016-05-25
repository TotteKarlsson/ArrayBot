#ifndef abLinearMoveH
#define abLinearMoveH
#include "abExporter.h"
#include "abProcess.h"
#include "abPosition.h"
//---------------------------------------------------------------------------

enum MoveType {mtAbsolute = 0, mtRelative, mtUnknown};
MoveType	toMoveType(const string& mt);
string		toString(MoveType mt);

//!The move baseclass contain the general logic for a 'move' of
//any type of object
class AB_CORE LinearMove : public Process
{
    public:
        	   			            LinearMove(const string& lbl, ABObject* unit, MoveType type = mtAbsolute, const ab::Position& p = ab::Position("", 0,0,0), double maxVel = 0, double acc = 0, double dwellTime = 0);
    	virtual			            ~LinearMove(){}

        virtual bool				write(mtk::IniSection* sec);
        virtual bool				read(mtk::IniSection* sec);

        virtual bool	            execute();
		bool 						isDone();
        virtual	bool	            undo();
        virtual bool	            isActive();
        virtual MoveType            getMoveType(){return mMoveType;}

        ab::Position&	            getPosition(){return mPosition;}
        double			            getMaxVelocity(){return mMaxVelocity;}
        double			            getAcceleration(){return mAcceleration;}
        double			            getDwellTime(){return mDwellTime;}

        bool 			            setPosition(const ab::Position& pos){mPosition = pos; return true;}
        bool			            setMaxVelocity(double v){mMaxVelocity = v; return true;}
        bool			            setAcceleration(double a){mAcceleration = a; return true;}
        bool			            setDwellTime(double dt){mDwellTime = dt; return true;}

        string			            getPositionName(){return mPosition.getLabel();}
        void			            setPositionName(const string& l){mPosition.setLabel(l);}

    protected:
        				            //!The exact meaning of the position attribute is
                                    //made clear in derived classes
        ab::Position                mPosition;

        				            //!An absolute move, moves the unit to a defined position in space
                                    //!A 'relative' move, moves the unit relative to current
                                    //position, using position as a 'delta'.
        MoveType 		            mMoveType;
        double			            mMaxVelocity;
        double			            mAcceleration;
        string						mMotorName;
};

#endif
