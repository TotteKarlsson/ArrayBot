#ifndef abMoveH
#define abMoveH
#include "abExporter.h"
#include "abProcess.h"
#include "abPosition.h"
#include "abPositionalTrigger.h"
//---------------------------------------------------------------------------

namespace ab
{

//!The move baseclass contain the general logic for a 'move' of an APTMotor
class AB_CORE Move : public Process
{
    public:
        	   			                    Move(const string& lbl, APTMotor* mtr, double maxVel = 0, double acc = 0);
    	virtual			                    ~Move(){}

        string								getMotorName();
		virtual void		   		        init(ArrayBot& ab);

		virtual mtk::XMLElement*            addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot) = 0;
		virtual void	                    assignUnit(ABObject* o);

        virtual bool	                    stop();
        virtual bool	                    isBeingProcessed();
        bool 						        isProcessed();
		bool						        isMotorCommandPending();
        virtual	bool	                    undo();

									        //!Any subclass need to implement these
        virtual bool 				        isDone() 	= 0;
        virtual bool	                    start() 	= 0;

        bool	            		        isMotorActive();

        							        //!MotorVelocity
        bool			                    setMaxVelocity(double v){mMaxVelocity = v; return true;}
        double			                    getMaxVelocity(){return mMaxVelocity;}

        							        //!Motor acceleration
        bool			                    setAcceleration(double a){mAcceleration = a; return true;}
        double			                    getAcceleration(){return mAcceleration;}

        Trigger*							getTrigger(){return mTrigger;}
        virtual void						addTrigger(Trigger* t);
        virtual void						deleteTrigger(Trigger* t = NULL);

    protected:
        double			                    mMaxVelocity;
        double			                    mAcceleration;

        									//!The trigger observes the location of the motor moving
                                            //!and can be setup to trigger another motor when a
                                            //!certain position is achieved
        Trigger*							mTrigger;
};

}
#endif
