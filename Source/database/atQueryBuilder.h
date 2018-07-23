#ifndef atQueryBuilderH
#define atQueryBuilderH
#include <sstream>
#include "atDBExporter.h"
#include "atATObject.h"
//---------------------------------------------------------------------------

namespace at
{

    class AT_DB QueryBuilder : public std::stringstream, public ATObject
    {
    	public:
    		std::string				asString();
            const char* 			asCString();
            void					clear();

        protected:
    };

}

#endif
