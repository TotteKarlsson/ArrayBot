#include <vcl.h>
#pragma hdrstop
#include "TWatchDogSensorFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TWatchDogSensorFrame *WatchDogSensorFrame;

int frameNr = 0;
//---------------------------------------------------------------------------
__fastcall TWatchDogSensorFrame::TWatchDogSensorFrame(TComponent* Owner)
	: TFrame(Owner)
{
	this->Name = this->Name + IntToStr(frameNr++);
}

void TWatchDogSensorFrame::populate(WatchDogSensor* s)
{
	mSensor = s;
    DeviceID->setValue(s->getDeviceID());
 	DeviceAlias->setValue(s->getAlias());

    TemperatureE->setValue(s->getTemperature());
    HumidityE->setValue(s->getHumidity());
    DewPointE->setValue(s->getDewPoint());
    IsConnectedLbl->Caption = s->isPresent() ? "true" : "false";
}

