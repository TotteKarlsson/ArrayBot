#ifndef atContinousMoveH
#define atContinousMoveH
#include "atMove.h"
//---------------------------------------------------------------------------

class AT_AB ContinousMove : public at::Move
{
    public:
        							ContinousMove::ContinousMove(const string& lbl, double v, double acc);
							        ~ContinousMove(){}
        virtual const string 		getTypeName() const {return "continousMove";}

        bool						isDone();
		bool 						start();
		virtual dsl::XMLElement*    addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);


    protected:

    private:

};
#endif
