#ifndef TImageItemFrameH
#define TImageItemFrameH
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
#include "atCreateImageThumbNailThread.h"
//---------------------------------------------------------------------------
using Poco::Path;
using Poco::File;

class PACKAGE TImageItemFrame : public TFrame
{
    __published:	// IDE-managed Components
    TLabel *MovieLbl;
	TImage *WarningImage;
	TPanel *Panel1;
	void __fastcall WarningImageClick(TObject *Sender);

    private:
    	File		                mItemFile;
	    File 		                mThumbNail;
        string		                mItemName;
		CreateImageThumbNailThread  mTNThread;
        void						populateTNImage(int, int);

    public:
			        __fastcall 		TImageItemFrame(const File& MovieFile, TComponent* Owner);
		void						setItemName(const string& name);
};

extern PACKAGE TImageItemFrame *ImageItemFrame;

#endif
