#ifndef abVCLUtilsH
#define abVCLUtilsH
#include <vcl.h>
#include <string>
#include "database/abATDBServerSession.h"
#include "database/abATDBClientDBSession.h"
//---------------------------------------------------------------------------
using std::string;

//List boxes
PACKAGE bool 	updateListBoxItemCaption(TListBox* cb, int indx, const string& name);
PACKAGE int     selectAndClickListBoxItem(TListBox* lb, TObject* p);
PACKAGE int     selectAndClickListBoxItem(TListBox* lb, int itemIndex);
PACKAGE int     selectAndClickListBoxItem(TListBox* lb, const string& name);

//Combo boxes
PACKAGE bool 	updateComboBoxItemCaption(TComboBox* cb, int indx, const string& name);
PACKAGE int 	selectAndClickComboBoxItem(TComboBox* lb, const string& name);

PACKAGE void 	populateUsersCB(TComboBox* mUsersCB, ATDBServerSession& ses);
PACKAGE void 	populateUsersCB(TComboBox* mUsersCB, ATDBClientDBSession& ses);
PACKAGE int 	getCurrentUserID(TComboBox* mUserCB);

#endif
