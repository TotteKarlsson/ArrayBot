#pragma hdrstop
#include "abVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


int selectAndClickListBoxItem(TObject* p, TListBox* lb)
{
	//find the item in the list box;
	for(int i = 0; i < lb->Count; i++)
    {
    	if(lb->Items->Objects[i] == p)
        {
        	lb->Selected[i] = true;
            lb->OnClick(NULL);
            return i;
        }
    }
    return -1;
}

