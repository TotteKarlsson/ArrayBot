#ifndef TSoundsFrameH
#define TSoundsFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sound/atDirectSound.h"
#include <Vcl.ComCtrls.hpp>

//---------------------------------------------------------------------------
class PACKAGE TSoundsFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
		TListBox *SoundsLB;
		TButton *PlayBtn;
		TTrackBar *TrackBar1;
		TButton *StopBtn;
		TCheckBox *RepeatSoundCB;
		void __fastcall PlayBtnClick(TObject *Sender);
		void __fastcall TrackBar1Change(TObject *Sender);
		void __fastcall SoundsLBClick(TObject *Sender);

    private:
        DirectSound						mSound;
        string							mSelectedSound;

    public:
			        		__fastcall 	TSoundsFrame(TComponent* Owner);
        void							populate();
};

extern PACKAGE TSoundsFrame *SoundsFrame;
#endif
