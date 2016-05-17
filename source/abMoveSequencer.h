#ifndef abMoveSequencerH
#define abMoveSequencerH
#include "abExporter.h"
#include "abABObject.h"
#include <list>

using std::list;
//---------------------------------------------------------------------------

class Move
{};


class MoveSequencer : public ABObject
{
	public:

	private:
    	list<Move>				mMoves;
};
#endif
