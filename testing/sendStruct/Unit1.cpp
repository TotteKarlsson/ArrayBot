//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{}

void __fastcall TForm1::UserStructHandler(TMyStruct &msg)
{
    MessageDlg("Struct received: " + IntToStr(msg.lparam->m_a) + " " + IntToStr(msg.lparam->m_b),
            mtInformation, TMsgDlgButtons() << mbOK, 0);
}

//void __fastcall TForm1::Button1Click(TObject *Sender)
//{
//    int wparam = 0;
//    int lparam = StrToIntDef(IntEdit->Text,0);
//    int lbase = lparam;
//
//    SendGetIntMessage(Handle,WM_INTMESSAGE,wparam,lparam);
//
//    if (lbase != lparam)
//    {
//        MessageDlg("Value modified by handler function: " +
//                    IntToStr(lparam),
//                    mtInformation, TMsgDlgButtons() << mbOK, 0);
//        IntEdit->Text = IntToStr(lparam);
//    }
//
//}

////---------------------------------------------------------------------------
//void __fastcall TForm1::Button2Click(TObject *Sender){
//    int wparam = 0;
//    String lparam = TextEdit->Text;
//
//    SendTextMessage(Handle,WM_TEXTMESSAGE,wparam,lparam);
//}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    int wparam = 0;
    MStruct lparam;

    lparam.m_a = 23;
    lparam.m_b = 42;

    PostMessage(Handle, WM_STRUCTMESSAGE, wparam, (long) &lparam);
}
//---------------------------------------------------------------------------
//void __fastcall TForm1::UserIntHandler(TMyIntMessage &msg)
//{
//    MessageDlg("Int message received: " + IntToStr(*msg.lparam),
//            mtInformation, TMsgDlgButtons() << mbOK, 0);
//
//    *msg.lparam = *msg.lparam + 50;
//}

//void __fastcall TForm1::UserGetStructHandler(TMyStruct &msg)
//{
//    MessageDlg("Struct received: " + IntToStr(msg.lparam->m_a) +
//            "" + IntToStr(msg.lparam->m_b),
//            mtInformation, TMsgDlgButtons() << mbOK, 0);
//    msg.lparam->m_a = msg.lparam->m_a + 50;
//    msg.lparam->m_b = msg.lparam->m_b + 50;
//}

//void __fastcall TForm1::UserTextHandler(TMyTextMessage &msg)
//{
//    MessageDlg("Text received: " + msg.lparam,
//            mtInformation, TMsgDlgButtons() << mbOK, 0);
//}

////---------------------------------------------------------------------------
//void __fastcall TForm1::Button4Click(TObject *Sender)
//{
//    int wparam = 0;
//    MStruct lparam, lbase;
//
//    lparam.m_a = StrToIntDef(GetStructEdit1->Text,0);
//    lparam.m_b = StrToIntDef(GetStructEdit2->Text,0);
//
//    lbase = lparam;
//
//    SendStructMessage(Handle, WM_GETSTRUCTMESSAGE, wparam, &lparam);
//
//    if (lbase.m_a != lparam.m_a) {
//        MessageDlg("Struct modified by handler function: " +
//                    IntToStr(lparam.m_a) + " " + IntToStr(lparam.m_b),
//                    mtInformation, TMsgDlgButtons() << mbOK, 0);
//        GetStructEdit1->Text = IntToStr(lparam.m_a);
//        GetStructEdit2->Text = IntToStr(lparam.m_b);
//    }
//}

//---------------------------------------------------------------------------



