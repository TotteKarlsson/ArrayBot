#include <vcl.h>
#pragma hdrstop
#include "abVCLUtils.h"
#include "mtkVCLUtils.h"
#include "mtkStringUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace mtk;


bool updateListBoxItemCaption(TListBox* lb, int indx, const string& name)
{
	if(indx > -1 && indx < lb->Count)
    {
		lb->Items->Strings[indx] = vclstr(name);
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

int selectAndClickListBoxItem(TListBox* lb, const string& item)
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

int selectAndClickComboBoxItem(TComboBox* cb, const string& name)
{
	if(!cb)
    {
    	return -1;
    }

	//find the item in the list box;
	for(int i = 0; i < cb->Items->Count; i++)
    {
    	if(compareStrings(stdstr(cb->Items->Strings[i]) , name))
        {
        	cb->ItemIndex = i;
            return i;
        }
    }
    return -1;
}

bool updateComboBoxItemCaption(TComboBox* cb, int indx, const string& name)
{
	if(indx > -1 && indx < cb->Items->Count)
    {
		cb->Items->Strings[indx] = vclstr(name);
        return true;
    }
    return false;
}

