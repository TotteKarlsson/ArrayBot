#ifndef abAbsoluteMoveH
#define abAbsoluteMoveH
#include "abMove.h"
//---------------------------------------------------------------------------

class AB_CORE AbsoluteMove : public ab::Move
{
    public:
			        				AbsoluteMove(const string& lbl, const ab::Position& p = ab::Position("", -1,-1,-1), double maxVel = 0, double acc = 0);
				        			~AbsoluteMove(){}
		const char* 				getTypeName() const;


        bool 			            setPosition(const ab::Position& pos){mPosition = pos; return true;}
        ab::Position&	            getPosition(){return mPosition;}

        string			            getPositionName(){return mPosition.getLabel();}
        void			            setPositionName(const string& l){mPosition.setLabel(l);}

        bool						isDone();
		bool 						start();
		virtual mtk::XMLElement*    addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);

    protected:
           				            //!The position is the location which to achieve by the move
        ab::Position                mPosition;
        double						mPositionResolution;

    private:

};
#endif
