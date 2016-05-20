#ifndef abPositionH
#define abPositionH
#include "abExporter.h"
#include "abABObject.h"
#include "Math/mtkPoint.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;
using mtk::Point;

//! A Position is a point in XYZ space.
/*!
The position can be named using the Label attribute
*/
namespace ab
{

class AB_CORE Position : public ABObject
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
    	mtk::Point				mPosition;
        string					mLabel;
        double					mResolution;
};

}
#endif
