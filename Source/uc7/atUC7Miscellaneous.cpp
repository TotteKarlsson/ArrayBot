#pragma hdrstop
#include "atUC7Miscellaneous.h"
//---------------------------------------------------------------------------

string	toText(UC7StrokeState state)
{
	switch(state)
    {
    	case ssBeforeCutting:	return "Before Cutting";
    	case ssCutting:			return "Cutting";
    	case ssAfterCutting:	return "After Cutting";
    	case ssRetracting:		return "Retracting";
    	default:				return "State Unknonw";
    }
}

