#ifndef abCombinedLinearMoveH
#define abCombinedLinearMoveH
#include "abProcess.h"
#include "abLinearMove.h"
#include <vector>
#include "mtkXMLUtils.h"
//---------------------------------------------------------------------------
using namespace std;

//TODO: Rename this one to MultiLinearMove
class AB_CORE CombinedLinearMove : public Process
{
    public:
        	   			            CombinedLinearMove(const string& lbl);
    	virtual			            ~CombinedLinearMove(){}
        virtual mtk::XMLElement*    addToXMLDocumentAsChildProcess(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);

        int							getNumberOfMoves(){return mMoves.size();}

		virtual void	            addMove(LinearMove& lm);
        LinearMove*					getMove(const string& lbl);
        LinearMove*					getMove(int i);

        bool 						removeMove(LinearMove* m);
        bool 						removeMove(const string& name);

        virtual bool				write(mtk::IniSection* sec);
        virtual bool				read(mtk::IniSection* sec);

        virtual bool	            start();
        virtual bool	            stop();
        virtual bool	            isBeingProcessed();
        bool 						isProcessed();
		bool						isCommandPending();
        virtual	bool	            undo();

									//Check if we are at proper position(s)
        bool 						isDone();
        virtual bool	            areMotorsActive();

    protected:
		vector<LinearMove>			mMoves;
};

#endif
