#ifndef TMovieItemFrameH
#define TMovieItemFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.MPlayer.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include "Poco/Path.h"
#include "Poco/File.h"
#include <Vcl.Imaging.pngimage.hpp>
#include "atCreateMovieThumbNailThread.h"
//---------------------------------------------------------------------------
using Poco::Path;
using Poco::File;

class PACKAGE TMovieItemFrame : public TFrame
{
    __published:	// IDE-managed Components
        TLabel *MovieLbl;
	TArrayBotButton *PlayBtn;
	TImage *WarningImage;
	TPanel *Panel1;
	void __fastcall PlayBtnClick(TObject *Sender);
	void __fastcall WarningImageClick(TObject *Sender);

    private:
    	File		                mMovieFile;
	    File 		                mThumbNail;
        string		                mItemName;
		CreateMovieThumbNailThread  mTNThread;
        void						populateTNImage(int, int);

    public:
			        __fastcall 		TMovieItemFrame(const File& MovieFile, TComponent* Owner);
		void						setItemName(const string& name);
};

extern PACKAGE TMovieItemFrame *MovieItemFrame;

#endif
