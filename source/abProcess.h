#ifndef abProcessH
#define abProcessH
#include "abExporter.h"
#include "abABObject.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;
namespace mtk
{
	class IniSection;
}

enum ProcessType {ptSpatialMove = 0};

class AB_CORE Process : public ABObject
{
    public:
        							Process(const string& lbl, ABObject* o);
							        ~Process(){}

		void			            assignUnit(ABObject* o){mUnit = o;}
        string						getLabel(){return mLabel;}

        double			            getDwellTime(){return mDwellTime;}
        bool			            setDwellTime(double dt){mDwellTime = dt; return true;}

        virtual bool	            isActive() 	= 0;
        virtual bool	            execute() 	= 0;
        virtual	bool 			 	isDone()    = 0;
        virtual	bool	            undo() 		= 0;

        virtual bool				read(mtk::IniSection* sec) = 0;
        virtual bool				write(mtk::IniSection* sec) = 0;

    protected:
        					        //!Making object for moving abstract allow us
                                    //to process 'any' object. Just specialize in the
                                    //execute function..
    	ABObject* 		            mUnit;

        							//!The process type help us construct
                                    //a new process object from a file
        ProcessType					mProcessType;

        							//!A process parameters are saved
                                    //to its own INI section in a INI file
        mtk::IniSection*	   		mIniSection;

        string						mLabel;
        double			            mDwellTime;
};


#endif
