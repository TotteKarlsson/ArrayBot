#include <vcl.h>
#pragma hdrstop
#include "abVCLUtils.h"
#include "mtkVCLUtils.h"
#include "mtkStringUtils.h"
#include "mtkLogger.h"
#include "Poco/Data/RecordSet.h"
using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace mtk;

int getCurrentUserID(TComboBox* mUserCB)
{
	int i = mUserCB->ItemIndex;

    if(i > -1)
    {
    	return * ((int*) mUserCB->Items->Objects[i]);
    }

	return  -1;
}

void populateUsersCB(TComboBox* mUserCB, ATDBServerSession& ses)
{
    //Fetch data
    mUserCB->Clear();
    RecordSet *rs =  ses.getUsers();
    if(!rs->rowCount())
    {
        Log(lInfo) << "There are no users...";
    }
    else
    {
        int cols = rs->columnCount();
        int rows = rs->rowCount();

        // iterate over all rows and columns
        for (RecordSet::Iterator it = rs->begin(); it != rs->end(); ++it)
        {
            Poco::Data::Row& row = *it;
            string user(row[1].convert<std::string>());
            int *userId = new int(row[0].convert<int>());
            mUserCB->Items->AddObject(user.c_str(), (TObject*) userId );
            Log(lInfo) <<user;
        }
        mUserCB->ItemIndex = 0;
    }
}

void populateUsersCB(TComboBox* mUserCB, ATDBClientDBSession& ses)
{
    //Fetch data
    mUserCB->Clear();
    RecordSet *rs =  ses.getUsers();
    if(!rs->rowCount())
    {
        Log(lInfo) << "There are no users...";
    }
    else
    {
        int cols = rs->columnCount();
        int rows = rs->rowCount();

        // iterate over all rows and columns
        for (RecordSet::Iterator it = rs->begin(); it != rs->end(); ++it)
        {
            Poco::Data::Row& row = *it;
            string user(row[1].convert<std::string>());
            int *userId = new int(row[0].convert<int>());
            mUserCB->Items->AddObject(user.c_str(), (TObject*) userId );
            Log(lInfo) <<user;
        }
        mUserCB->ItemIndex = 0;
    }
}

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

