#ifndef atATObjectH
#define atATObjectH
#include <string>
#include "atCoreExporter.h"
//---------------------------------------------------------------------------

using std::string;

namespace at
{
class AT_CORE ATObject
{
	public:
    							 ATObject(){}
		virtual					~ATObject() = 0;
        virtual const string 	getTypeName() const;

	protected:
	private:
};
}
#endif
