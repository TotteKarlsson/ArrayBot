#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslRestartApplicationUtils.h"
#include "dslVCLUtils.h"

using namespace dsl;
extern string gRestartMutexName ;
extern string gDefaultAppTheme;
extern string gApplicationStyle;


void __fastcall TMainForm::ThemesMenuClick(TObject *Sender)
{
    TMenuItem* menuItem = dynamic_cast<TMenuItem*>(Sender);
    if(!menuItem)
    {
        return;
    }

	//Uncheck any checked items
	for(int i = 0; i < ThemesMenu->Count; i++)
	{
		TMenuItem* menuItem = ThemesMenu->Items[i];
		if(menuItem && menuItem->Checked)
		{
			menuItem->Checked = false;
		}
	}

	TRegistryForm::writeToRegistry();

	TReplaceFlags rFlags(rfIgnoreCase|rfReplaceAll);
	String styleName = StringReplace(menuItem->Caption, "&", "", rFlags);
	TStyleManager::SetStyle(styleName);

	//Check the menu item
	menuItem->Checked = (TStyleManager::ActiveStyle->Name == styleName) ? true : false;

	//Write to registry
	gApplicationStyle = stdstr(styleName);
	writeStringToRegistry(gApplicationRegistryRoot, "", "Theme", gApplicationStyle);
}

