#ifndef TFFMPEGOutputFrameH
#define TFFMPEGOutputFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include "atVideoCompressorThread.h"
#include "TArrayBotBtn.h"

class TFFMPEGOutputFrame;

typedef void __fastcall (__closure *MyCallback)(TFFMPEGOutputFrame* f);
//---------------------------------------------------------------------------
class PACKAGE TFFMPEGOutputFrame : public TFrame
{
    __published:	// IDE-managed Components
        TProgressBar *ProgressBar1;
        TArrayBotButton *CompressBtn;
        TLabel *FileNameLbl;
	void __fastcall CompressBtnClick(TObject *Sender);

    private:
		VideoCompressorThread			mVCThread;
   	    void 				            onEnter(int i, int j);
	    void 				            onProgress(int i, int j);
	    void 				            onExit(int i, int j);

    public:
    			__fastcall 	            TFFMPEGOutputFrame(TComponent* Owner);
        void				            setInputFile(const string& fName);
        void				            setCompressionOptions(const string& o, bool deleteSourceFile, bool renameSourceFile);
        void				            startCompression();
	    MyCallback			            onDone;
        bool							isDone();
        string							getInputFileName();
        void							stopCompression();
};

extern PACKAGE TFFMPEGOutputFrame *FFMPEGOutputFrame;
#endif
