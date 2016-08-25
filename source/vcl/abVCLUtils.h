#ifndef abVCLUtilsH
#define abVCLUtilsH
#include <vcl.h>
#include <string>
//---------------------------------------------------------------------------
using std::string;
PACKAGE int selectAndClickListBoxItem(TListBox* lb, TObject* p);
PACKAGE int selectAndClickListBoxItem(TListBox* lb, int itemIndex);
PACKAGE int selectAndClickListBoxItem(TListBox* lb, const string& name);

PACKAGE bool updateComboBoxItemCaption(int indx, const string& name, TComboBox* cb);

#endif
