#ifndef abMoveH
#define abMoveH
#include "abExporter.h"
#include "abProcess.h"
#include "abPosition.h"
//---------------------------------------------------------------------------

namespace ab
{

enum MoveType {mtAbsolute = 0, mtRelative, mtUnknown};
MoveType	toMoveType(const string& mt);
string		toString(MoveType mt);

//!The move baseclass contain the general logic for a 'move' of
//any type of object
class AB_CORE Move : public Process
{
    public:
        	   			            Move(const string& lbl, MoveType type = mtAbsolute,
                                    		const ab::Position& p = ab::Position("", 0,0,0),
                                            	double maxVel = 0, double acc = 0);
    	virtual			            ~Move(){}

        string						getMotorName(){return mMotorName;}
        void						setMotorName(const string& n){mMotorName = n;}

		virtual mtk::XMLElement*    addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);
		virtual void	            assignUnit(ABObject* o);

        virtual bool	            start();
        virtual bool	            stop();
        virtual bool	            isBeingProcessed();
        bool 						isProcessed();
		bool						isMotorCommandPending();
        virtual	bool	            undo();

									//Check if we are at proper position
        bool 						isDone();
        virtual bool	            isMotorActive();

        virtual bool	            setMoveType(MoveType tp){mMoveType = tp; return true;}
        virtual MoveType            getMoveType(){return mMoveType;}

        bool 			            setPosition(const ab::Position& pos){mPosition = pos; return true;}
        ab::Position&	            getPosition(){return mPosition;}

        bool			            setMaxVelocity(double v){mMaxVelocity = v; return true;}
        double			            getMaxVelocity(){return mMaxVelocity;}

        bool			            setAcceleration(double a){mAcceleration = a; return true;}
        double			            getAcceleration(){return mAcceleration;}

        string			            getPositionName(){return mPosition.getLabel();}
        void			            setPositionName(const string& l){mPosition.setLabel(l);}

    protected:
        string						mMotorName;

        				            //!The exact meaning of the position attribute is
                                    //made clear in derived classes
        ab::Position                mPosition;
        double						mPositionResolution;

        				            //!An absolute move, moves the unit to a defined position in space
                                    //!A 'relative' move, moves the unit relative to current
                                    //position, using position as a 'delta'.
        MoveType 		            mMoveType;
        double			            mMaxVelocity;
        double			            mAcceleration;
};

}
#endif
