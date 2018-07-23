#ifndef atPositionH
#define atPositionH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "Math/dslPoint.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;
using dsl::Point;

//! A Position is a point in XYZ space.
/*!
The position can be named using the Label attribute
*/
namespace ab
{

class AT_AB Position : public ATObject
{
	public:
								Position(const string& lbl, double x, double y, double z);
								~Position();
		string					getLabel();
		void					setLabel(const string& l) {mLabel = l;}
        double					x() const;
        double 					y() const;
        double 					z() const;

	protected:
    	dsl::Point				mPosition;
        string					mLabel;
        double					mResolution;
};

}
#endif
