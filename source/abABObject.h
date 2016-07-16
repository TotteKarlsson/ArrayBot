#ifndef abABObjectH
#define abABObjectH
#include "abExporter.h"
#include <string>
//---------------------------------------------------------------------------
using std::string;

class AB_CORE ABObject
{
	public:
    							ABObject();
		virtual					~ABObject();
        virtual const string 	getTypeName() const;

	protected:

	private:
};
#endif
