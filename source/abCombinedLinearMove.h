#ifndef abCombinedLinearMoveH
#define abCombinedLinearMoveH
#include "abExporter.h"
#include "abProcess.h"
#include "abPosition.h"
#include "abLinearMove.h"
#include <vector>
//---------------------------------------------------------------------------
using namespace std;

//!The move baseclass contain the general logic for a 'move' of
//any type of object
class AB_CORE CombinedLinearMove : public Process
{
    public:
        	   			            CombinedLinearMove(const string& lbl);
    	virtual			            ~CombinedLinearMove(){}

		virtual void	            addMove(LinearMove& lm);

        virtual bool				write(mtk::IniSection* sec);
        virtual bool				read(mtk::IniSection* sec);

        virtual bool	            start();
        virtual bool	            stop();
        virtual bool	            isBeingProcessed();
        bool 						isProcessed();
		bool						isCommandPending();
        virtual	bool	            undo();

									//Check if we are at proper position
        bool 						isDone();
        virtual bool	            areMotorsActive();

    protected:
		vector<LinearMove>			mLinearMoves;
};

#endif
