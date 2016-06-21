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

enum ProcessType {ptLinearMove = 0};

class AB_CORE Process : public ABObject
{
    public:
        							Process(const string& lbl, ABObject* o);
							        ~Process(){}

		virtual void	            assignUnit(ABObject* o){mUnit = o;}
		ABObject*					getUnit(){return mUnit;}
        string						getProcessName(){return mProcessName;}
        void						setProcessName(const string& l) {mProcessName = l;}

        double			            getDwellTime(){return mDwellTime;}
        bool			            setDwellTime(double dt){mDwellTime = dt; return true;}

        virtual bool	            isActive() 	= 0;
        virtual bool	            execute() 	= 0;
        virtual bool	            stop() 		= 0;
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

        							//!The Label identifies the process in a sequence
                                    //and in a ini file
        string						mProcessName;
        double			            mDwellTime;
};


#endif
