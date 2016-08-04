#ifndef TSensorAndLightArduinoFrameH
#define TSensorAndLightArduinoFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArduinoBoardFrame.h"
#include "TIntegerLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class PACKAGE TSensorAndLightArduinoFrame : public TArduinoBoardFrame
{
	__published:	// IDE-managed Components
		private:	// User declarations
		public:		// User declarations

							__fastcall 	TSensorAndLightArduinoFrame(ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
							__fastcall 	~TSensorAndLightArduinoFrame();

		void 							init();

};

//---------------------------------------------------------------------------
extern PACKAGE TSensorAndLightArduinoFrame *SensorAndLightArduinoFrame;
//---------------------------------------------------------------------------
#endif
