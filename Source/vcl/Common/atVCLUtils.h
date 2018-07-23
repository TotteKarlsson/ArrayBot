#ifndef atVCLUtilsH
#define atVCLUtilsH
#include <VCL.ExtCtrls.hpp>
#include "atVCLCommonExporter.h"
#include <string>
//---------------------------------------------------------------------------
namespace at
{

using std::string;

class AT_VCLCOMMON ATWindowStructMessage
{
	public:
        Cardinal            Msg;
                            //
        int                 wparam;

                            //This is our data
        void*				lparam;
        LRESULT             Result;
};


//TImage utilities
AT_VCLCOMMON int 				getImageWidth(TImage* imageCtrl);
AT_VCLCOMMON int 				getImageHeight(TImage* imageCtrl);

AT_VCLCOMMON double				getImageAspectRatio(TImage* imageCtrl);
AT_VCLCOMMON double				getImageContainerAspectRatio(TImage* imageCtrl);
AT_VCLCOMMON int                getImageWidthFromHeight(TImage* imageCtrl);
AT_VCLCOMMON int                getImageHeightFromWidth(TImage* imageCtrl);

//List boxes
AT_VCLCOMMON bool 	            updateListBoxItemCaption(TListBox* cb, int indx, const string& name);
AT_VCLCOMMON int                selectAndClickListBoxItem(TListBox* lb, TObject* p);
AT_VCLCOMMON int                selectAndClickListBoxItem(TListBox* lb, int itemIndex);
AT_VCLCOMMON int                selectAndClickListBoxItem(TListBox* lb, const string& name);

//Combo boxes
AT_VCLCOMMON bool 	            updateComboBoxItemCaption(TComboBox* cb, int indx, const string& name);
AT_VCLCOMMON string             getSelectedItem(TComboBox* lb);
AT_VCLCOMMON int 	            selectItem(TComboBox* lb, const string& name, bool addItem = false);
AT_VCLCOMMON int 	            selectAndClickComboBoxItem(TComboBox* lb, const string& name);

AT_VCLCOMMON int 	            getCurrentUserID(TComboBox* mUserCB);

}
#endif
