#include <vcl.h>
#pragma hdrstop
#include "abVCLUtils.h"
#include "mtkVCLUtils.h"
#include "mtkStringUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace mtk;

bool updateComboBoxItemCaption(int indx, const string& name, TComboBox* cb)
{
	if(indx > -1 && indx < cb->Items->Count)
    {
		cb->Items->Strings[indx] = vclstr(name);
        return true;
    }
    return false;
}

int selectAndClickListBoxItem(TListBox* lb, TObject* p)
{
	if(!lb)
    {
    	return -1;
    }

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

int selectAndClickListBoxItem(TListBox* lb, int itemIndex)
{
	if(!lb)
    {
    	return -1;
    }

	if(itemIndex < lb->Count && itemIndex > -1)
    {
    	lb->Selected[itemIndex] = true;
        lb->OnClick(NULL);
    }

    return itemIndex;
}

int selectAndClickListBoxItem(TListBox* lb, const string&  item)
{
	if(!lb)
    {
    	return -1;
    }

	//find the item in the list box;
	for(int i = 0; i < lb->Count; i++)
    {
    	if(compareStrings(stdstr(lb->Items->Strings[i]) ,item))
        {
        	lb->Selected[i] = true;
            lb->OnClick(NULL);
            return i;
        }
    }
    return -1;
}

