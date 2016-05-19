#ifndef abXYZUnitPositionH
#define abXYZUnitPositionH
#include "abExporter.h"
#include "abABObject.h"
#include "Math/mtkPoint.h"
#include <string>

using std::string;
using mtk::Point;

//---------------------------------------------------------------------------
class AB_CORE XYZUnitPosition : public ABObject
{
	public:
								XYZUnitPosition(const string& lbl, double x, double y, double z);
								~XYZUnitPosition();
		string					getLabel();
        double					x() const;
        double 					y() const;
        double 					z() const;

	protected:
    	Point					mPosition;
        string					mLabel;
};

#endif
