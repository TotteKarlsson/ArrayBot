#ifndef abXYZUnitPositionsH
#define abXYZUnitPositionsH
#include "CoreExporter.h"
#include "abABObject.h"
#include <deque>
#include "abXYZUnitPosition.h"
//---------------------------------------------------------------------------
using std::deque;

typedef deque<XYZUnitPosition> UnitPositions;
class AB_CORE XYZUnitPositions : public ABObject
{
	public:
								XYZUnitPositions();
								~XYZUnitPositions();
		bool					add(const XYZUnitPosition& pos);
        bool					remove(const string& lbl);
        XYZUnitPosition*        getFirst() const;
        XYZUnitPosition*        getNext() const;
        XYZUnitPosition*        getPrevious() const;
        XYZUnitPosition*        getCurrent() const;


	protected:
    	mutable
        UnitPositions			mPositions;
    	mutable
        UnitPositions::iterator mPositionsIter;
};
#endif
