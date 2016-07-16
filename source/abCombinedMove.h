#ifndef abCombinedMoveH
#define abCombinedMoveH
#include "abProcess.h"
#include <vector>
#include "mtkXMLUtils.h"
//---------------------------------------------------------------------------
using namespace std;

namespace ab
{
class Move;
}

class AB_CORE CombinedMove : public Process
{
    public:
        	   			            CombinedMove(const string& lbl);
    	virtual			            ~CombinedMove(){}
		virtual void		   		init(ArrayBot& ab);
		const string 				getTypeName() const;
        void						clear();

        virtual mtk::XMLElement*    addToXMLDocumentAsChildProcess(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);
        int							getNumberOfMoves(){return mMoves.size();}

		virtual void	            addMove(ab::Move* lm);
        ab::Move*					getMove(const string& lbl);
        ab::Move*					getMove(int i);

        bool 						removeMove(ab::Move* m);
        bool 						removeMove(const string& name);

        							//!All moves starts at the same time
        virtual bool	            start();
        virtual bool	            stop();
        virtual bool	            isBeingProcessed();
        bool 						isProcessed();
		bool						isCommandPending();
        virtual	bool	            undo();

									//Check if we are at proper position(s)
        bool 						isDone();
        virtual bool	            areMotorsActive();

    protected:                      //!The Moves container contain all moves
		vector<ab::Move*>			mMoves;
};

#endif
