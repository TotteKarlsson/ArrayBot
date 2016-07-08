#ifndef abABObjectH
#define abABObjectH
#include "abExporter.h"
//---------------------------------------------------------------------------

class AB_CORE ABObject
{
	public:
    							ABObject();
		virtual					~ABObject();
        virtual const char*	 	getTypeName() const;

	protected:

	private:
};
#endif
