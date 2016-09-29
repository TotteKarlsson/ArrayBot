#ifndef TArrayBotBtnH
#define TArrayBotBtnH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include "sound/abDirectSound.h"

//---------------------------------------------------------------------------
class PACKAGE TArrayBotButton : public TBitBtn
{
    private:
		virtual void __fastcall			CreateWnd();
		virtual void __fastcall			DestroyWnd();

    protected:
    	virtual void __fastcall 		WndProc(TMessage& msg);

        DirectSound						mSound;
        String                          FSoundID;

  //      void                __fastcall  setSoundID(const String& snd);
//        String              __fastcall  getSoundID();


    public:
        					__fastcall 	TArrayBotButton(TComponent* Owner);
		bool	   						init(HWND wnd);
    __published:
        __property String     SoundID   = {read=FSoundID, write=FSoundID, default=true};

};
//---------------------------------------------------------------------------
#endif
