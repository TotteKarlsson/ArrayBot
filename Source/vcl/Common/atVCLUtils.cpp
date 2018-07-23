#pragma hdrstop
#include "atVCLUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;
using namespace Poco;

int getCurrentUserID(TComboBox* mUserCB)
{
	int i = mUserCB->ItemIndex;

    if(i > -1)
    {
    	return * ((int*) mUserCB->Items->Objects[i]);
    }

	return  -1;
}

int getImageWidth(TImage* imageCtrl)
{
    //First check if image is stretched or not
    if(imageCtrl->Stretch == false)
    {
        return imageCtrl->Picture->Width; //The original width
    }

    //if it is stretched, check aspect ratios..
    //Observe, this probably don't work.. need to check landscape or portrait
    if(getImageAspectRatio(imageCtrl) == getImageContainerAspectRatio(imageCtrl))
    {
        return imageCtrl->Picture->Width;
    }

    //As the image is being stretched, there are several "cases"
    if(imageCtrl->Width > imageCtrl->Height)
    {
        //Gotta check how the image is stretched, depends on original dimension
        if(imageCtrl->Picture->Width < imageCtrl->Picture->Height)
        {
            //Image Height == container height
            return getImageWidthFromHeight(imageCtrl);
        }
        else if(imageCtrl->Picture->Width > imageCtrl->Picture->Height)
        {
            //Image width == container width
            return imageCtrl->Width;
        }
    }
    else if(imageCtrl->Width < imageCtrl->Height)
    {
        if(imageCtrl->Picture->Width < imageCtrl->Picture->Height)
        {
            return imageCtrl->Width;
        }
        else if(imageCtrl->Picture->Width > imageCtrl->Picture->Height)
        {
            return getImageWidthFromHeight(imageCtrl);
        }
    }
    else if (imageCtrl->Width == imageCtrl->Height)
    {
        if(imageCtrl->Picture->Width < imageCtrl->Picture->Height)
        {
            return getImageWidthFromHeight(imageCtrl);
        }
        else if(imageCtrl->Picture->Width > imageCtrl->Picture->Height)
        {
            return imageCtrl->Width;
        }
    }
    return -1;
}

int getImageHeight(TImage* imageCtrl)
{
    //First check if image is stretched or not
    if(imageCtrl->Stretch == false)
    {
        return imageCtrl->Picture->Height; //The original height
    }

    //if it is stretched, check aspect ratios..
    //Observe, this probably don't work.. need to check landscape or portrait
    if(getImageAspectRatio(imageCtrl) == getImageContainerAspectRatio(imageCtrl))
    {
        return imageCtrl->Picture->Height;
    }

    //As the image is being stretched, there are several "cases"
    if(imageCtrl->Width > imageCtrl->Height)
    {
        //Gotta check how the image is stretched, depends on original dimension
        if(imageCtrl->Picture->Width < imageCtrl->Picture->Height)
        {
            //Image Height == container height
            return imageCtrl->Height;
        }
        else if(imageCtrl->Picture->Width > imageCtrl->Picture->Height)
        {
            //Image width == container width
            return getImageHeightFromWidth(imageCtrl);
        }
    }
    else if(imageCtrl->Width < imageCtrl->Height)
    {
        if(imageCtrl->Picture->Width < imageCtrl->Picture->Height)
        {
            return getImageHeightFromWidth(imageCtrl);;
        }
        else if(imageCtrl->Picture->Width > imageCtrl->Picture->Height)
        {
            return imageCtrl->Height;
        }
    }
    else if (imageCtrl->Width == imageCtrl->Height)
    {
        if(imageCtrl->Picture->Width < imageCtrl->Picture->Height)
        {
            return imageCtrl->Height;

        }
        else if(imageCtrl->Picture->Width > imageCtrl->Picture->Height)
        {
            return getImageHeightFromWidth(imageCtrl);
        }
    }
    return -1;
}

double getImageAspectRatio(TImage* imageCtrl)
{
    double w = imageCtrl->Picture->Width;
	double h = imageCtrl->Picture->Height;

    if(w == 0 || h == 0)
    {
        Log(lError) << "Can't calculate aspect ratio for image!";
        return -1;
    }

    if( w > h)
    {
        return w / h;
    }
    else if (h > w)
    {
        return h/w;
    }
    else
    {
        return 1.0;
    }
}

double getImageContainerAspectRatio(TImage* imageCtrl)
{
    double w = imageCtrl->Width;
	double h = imageCtrl->Height;

    if(w == 0 || h == 0)
    {
        Log(lError) << "Can't calculate aspect ratio for image container!";
        return -1;
    }

    if( w > h)
    {
        return w / h;
    }
    else if (h > w)
    {
        return h/w;
    }
    else
    {
        return 1.0;
    }
}

int getImageWidthFromHeight(TImage* imageCtrl)
{
    //This apply to as scaled, proprtional image, assuming its height is the same as
    //its container
    double originalWidth(imageCtrl->Picture->Width);
    double originalHeight(imageCtrl->Picture->Height);

    double currentHeight = imageCtrl->Height;
    double currentWidth = currentHeight / ( originalHeight / originalWidth);

    return currentWidth;
}

int getImageHeightFromWidth(TImage* imageCtrl)
{
    //This apply to as scaled, proprtional image, assuming its height is the same as
    //its container
    double originalWidth(imageCtrl->Picture->Width);
    double originalHeight(imageCtrl->Picture->Height);

    double currentWidth = imageCtrl->Width;
    double currentHeight = currentWidth * ( originalHeight / originalWidth);

    return currentHeight;
}


//void populateUsersCB(TComboBox* mUserCB, ATDBServerSession& ses)
//{
//    //Fetch data
//    mUserCB->Clear();
//    RecordSet *rs =  ses.getUsers();
//    if(!rs->rowCount())
//    {
//        Log(lInfo) << "There are no users...";
//    }
//    else
//    {
//        int cols = rs->columnCount();
//        int rows = rs->rowCount();
//
//        using Poco::Data::RowIterator;
//        // iterate over all rows and columns
//        for (RowIterator it = rs->begin(); it != rs->end(); ++it)
//        {
//            Poco::Data::Row& row = *it;
//            string user(row[1].convert<std::string>());
//            int *userId = new int(row[0].convert<int>());
//            mUserCB->Items->AddObject(user.c_str(), (TObject*) userId );
//            Log(lInfo) <<user;
//        }
//        mUserCB->ItemIndex = 0;
//    }
//}
//
//void populateUsersCB(TComboBox* mUserCB, ATDBClientDBSession& ses)
//{
//    //Fetch data
//    mUserCB->Clear();
//    RecordSet *rs =  ses.getUsers();
//    if(!rs->rowCount())
//    {
//        Log(lInfo) << "There are no users...";
//    }
//    else
//    {
//        int cols = rs->columnCount();
//        int rows = rs->rowCount();
//
//        // iterate over all rows and columns
//        for (RecordSet::Iterator it = rs->begin(); it != rs->end(); ++it)
//        {
//            Poco::Data::Row& row = *it;
//            string user(row[1].convert<std::string>());
//            int *userId = new int(row[0].convert<int>());
//            mUserCB->Items->AddObject(user.c_str(), (TObject*) userId );
//            Log(lInfo) <<user;
//        }
//        mUserCB->ItemIndex = 0;
//    }
//}

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

string getSelectedItem(TComboBox* cb)
{
	if(!cb || cb->ItemIndex == -1)
    {
    	return gEmptyString;
    }
	return stdstr(cb->Items->Strings[cb->ItemIndex]);
}

int selectItem(TComboBox* cb, const string& name, bool addItem)
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

    //Seem the item did not exist.
    if(addItem)
    {
    	cb->AddItem(vclstr(name), NULL);
	    return selectItem(cb, name, addItem);
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

}
