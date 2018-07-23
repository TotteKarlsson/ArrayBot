#ifndef atArrayBotProtocolH
#define atArrayBotProtocolH
#include "atCoreExporter.h"
#include <map>
#include <string>
//---------------------------------------------------------------------------
using std::map;
using std::string;

//Put this in a header to be shared between server/client
//!Valid requests/responses enums
//abr <==> arraybot request/response
//abm <==> miscellaneous server message that clients may handle as they wish

enum  ABMessageID
{

    abrSetJoyStickSpeed=0, 				//!The cmd needs one arguments: setting name, e.g. fast, medium  or slow
    abrUnknown
};

class AT_CORE ArrayBotProtocol
{
	public:
							        		ArrayBotProtocol();

		ABMessageID			        		idFromString(const string& msg);
		string 	   			        		operator[](ABMessageID r);
    	static map<ABMessageID, string>   	mIPCMessage;

	private:
	    map<ABMessageID, string>::iterator	mIter;
        static map<ABMessageID, string>     createProtocol();
};

#endif
