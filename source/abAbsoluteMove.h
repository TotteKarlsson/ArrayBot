#ifndef abAbsoluteMoveH
#define abAbsoluteMoveH
#include "abMove.h"
//---------------------------------------------------------------------------

class AB_CORE AbsoluteMove : public ab::Move
{
    public:
			        				AbsoluteMove( const string& lbl, APTMotor* mtr = NULL, double pos = -1, double maxVel = 0, double acc = 0);
				        			~AbsoluteMove(){}
		const string 				getTypeName() const;


        bool 			            setPosition(double pos){mPosition = pos; return true;}
        double			            getPosition(){return mPosition;}

        bool						isDone();
		bool 						start();
		virtual mtk::XMLElement*    addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);

    protected:
           				            //!The position is the location which to achieve by the move
        double		                mPosition;
        double						mPositionResolution;

    private:

};
#endif
