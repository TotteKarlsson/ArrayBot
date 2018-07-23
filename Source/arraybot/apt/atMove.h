#ifndef atMoveH
#define atMoveH
#include "atABExporter.h"
#include "atProcess.h"
#include "atPositionalTrigger.h"
//---------------------------------------------------------------------------

namespace at
{

//!The move baseclass contain the general logic for a 'move' of an APTMotor.
//!This should be subclassed - > MoveMotor
class AT_AB Move : public Process
{
    public:
        	   			                    Move(const string& lbl, APTMotor* mtr, double maxVel = 0, double acc = 0);
    	virtual			                    ~Move(){}

        string								getMotorName();
		virtual void		   		        init(ArrayBot& ab);

		virtual dsl::XMLElement*            addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot) = 0;
		virtual void	                    assignUnit(ATObject* o);
        virtual bool	                    stop();

        virtual bool	                    isBeingProcessed();
        bool 						        isProcessed();
		bool						        isMotorCommandPending();
        virtual	bool	                    undo();

									        //!Any subclass need to implement these
        virtual bool 				        isDone() 	= 0;
        virtual bool	                    start() 	= 0;
        virtual bool 				        resume() 	= 0;
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
