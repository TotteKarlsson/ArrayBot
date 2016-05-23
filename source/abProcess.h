#ifndef abProcessH
#define abProcessH
#include "abExporter.h"
#include "abABObject.h"
//---------------------------------------------------------------------------

class AB_CORE Process : public ABObject
{
    public:
        							Process(ABObject* o);
							        ~Process(){}

		void			            assignUnit(ABObject* o){mUnit = o;}
        virtual bool	            isActive() 	= 0;
        virtual bool	            execute() 	= 0;
        virtual	bool	            undo() 		= 0;

    protected:
        					        //!Making object for moving abstract allow us
                                    //to process 'any' object. Just specialize in the
                                    //execute function..
    	ABObject* 		            mUnit;
};


#endif
