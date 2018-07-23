#ifndef atUC7MessageH
#define atUC7MessageH
#include "atATObject.h"
#include "atUC7Exporter.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------

namespace at
{
    const int gStepperControllerAddress             = 4;
    const int gMotorControllerAddress               = 5;
    const int gSystemCommands  			            = 8;


    //"Commands"
    const string gFeedRateMotorControl 	            = "20";
    const string gSendPositionAtMotionFeedRate      = "21";
    const string gFeed 					            = "23";
    const string gNorthSouthMotorMovement 	 		= "30";
    const string gSendPositionAtMotionNorthSouth    = "31";
    const string gEastWestMovement    				= "40";
    const string gSendPositionAtMotionEastWest      = "41";
    const string gCuttingMotorControl			    = "20";
    const string gCuttingSpeed					    = "30";
    const string gReturnSpeed					    = "31";
    const string gHandWheelPosition				    = "40";


    //!Simple enum to hold commands
    enum UC7MessageEnum
    {
        SOFTWARE_RESET                             = 0,
    	GET_PART_ID 	                           ,
        LOGIN			                           ,
        COMMAND_TRANSMISSION_ERROR                 ,
        GET_VERSION	                               ,

        FEEDRATE_MOTOR_CONTROL					   ,
        SEND_POSITION_AT_MOTION                    ,
        FEED                                       ,

        NORTH_SOUTH_MOTOR_MOVEMENT                 ,
        SEND_POSITION_AT_MOVEMENT_NORTH_SOUTH      ,

        EAST_WEST_MOTOR_MOVEMENT                   ,
        SEND_POSITION_AT_MOVEMENT_EAST_WEST        ,

        CUTTING_MOTOR_CONTROL                      ,
        CUTTING_SPEED                              ,
        RETURN_SPEED                               ,
        HANDWHEEL_POSITION						   ,
        UNKNOWN
    };

    UC7MessageEnum toCommandName(const string& cmd, int controllerAddress);
    string toShortString(UC7MessageEnum cmd);
    string toLongString(UC7MessageEnum cmd);

    class AT_UC7 UC7Message : public ATObject
    {
    	public:
    					            UC7Message(const string& cmd = dsl::gEmptyString, bool hasCS = false, bool isResponse = false);
    		bool					init(const string& cmd, bool hasCS = false);
            string		            getReceiver() const;
            string		            getSender() const;
    		string		            getCommand() const;
    		string					getData() const;

    		string		            getMessage() const;
    		string		            getFullMessage() const;

            string					getCheckSum() const;
            string					getMessageNameAsString() const;
            string					getXX() const;

            bool					calculateCheckSum();
            bool		            check() const;

    	private:
        	string 					mReceiver;
            string 					mSender;
            string					mData;
            string					mCheckSum;
            string 					mCommandString;
            bool					mIsResponse;

            UC7MessageEnum			mCommandNameEnum;
            bool					parse(const string& cmd, bool isResponse = false);
    };


}
#endif
