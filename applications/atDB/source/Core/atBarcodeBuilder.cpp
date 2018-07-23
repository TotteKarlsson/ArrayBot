#pragma hdrstop
#include "atBarcodeBuilder.h"
#include "dslLogger.h"
#include "dslStringUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;

//---------------------------------------------------------------------------
BarCodeBuilder::BarCodeBuilder(const char& rDel)
 :
mRightDelimiter(rDel),
mIsBuilding(false),
mBarCode(""),
mHasBarCode(false)
{}

//---------------------------------------------------------------------------
void BarCodeBuilder::reset()
{
    mIsBuilding = false;
    mHasBarCode = false;
    mBarCode.clear();
}

bool BarCodeBuilder::isBuilding(){return mIsBuilding;}
bool BarCodeBuilder::hasBarCode(){return mHasBarCode;}
void BarCodeBuilder::setBarCode(const string& bc)
{
	mBarCode = bc;
    mHasBarCode = true;
    mIsBuilding = false;
}
//---------------------------------------------------------------------------
bool BarCodeBuilder::build(const char& ch)
{
    //If we are looking for end of lines, we are "always" building
    if(ch == mRightDelimiter)
    {
    	//Coverslip barcode

        if(mBarCode.size() == 8 && startsWith("C", mBarCode))
        {
            mHasBarCode = true;
            mIsBuilding = false;
            return true;
        }

		reset();
        return true;
    }

    //Initiate building
    if(!mIsBuilding)
    {
        reset();
        mIsBuilding = true;
    }

    //Insert the character, discard irrelevant ones
   	mBarCode += ch;
    return true;
}

int	BarCodeBuilder::getBarCodeValue()
{
	if(mBarCode.size() > 2)
    {
		//Parse barcode
	    string temp(mBarCode);
    	temp.erase(0,1);
        return toInt(temp);
    }
}

//---------------------------------------------------------------------------
string BarCodeBuilder::getBarCode()
{
    return mBarCode;
}


