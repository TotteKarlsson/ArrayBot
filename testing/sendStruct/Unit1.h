//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>


  const int WM_INTMESSAGE 		= WM_USER + 100;
  const int WM_STRUCTMESSAGE 	= WM_USER + 101;
  const int WM_GETSTRUCTMESSAGE = WM_USER + 102;
  const int WM_TEXTMESSAGE 		= WM_USER + 103;


//This example uses three custom message structures defined in the header:
//struct TMyIntMessage
//{
//    Cardinal Msg;
//    int* wparam;
//    int* lparam;
//    LRESULT Result;
//};
//
//struct TMyTextMessage
//{
//    Cardinal Msg;
//    int wparam;
//    String lparam;
//    LRESULT Result;
//};
//
struct MStruct
{
    int m_a;
    int m_b;
};

struct TMyStruct
{
    Cardinal Msg;
    int wparam;
    MStruct* lparam;
    LRESULT Result;
};

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button3;
	TButton *Button4;
	TButton *Button2;
	TEdit *IntEdit;
	TEdit *StructEdit2;
	TEdit *StructEdit1;
	TEdit *GetStructEdit2;
	TEdit *GetStructEdit1;
	TEdit *TextEdit;
//	void __fastcall Button1Click(TObject *Sender);
//	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
//	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations


public:		// User declarations
	__fastcall TForm1(TComponent* Owner);


//    Furthermore it uses 4 message handling functions described in the
//    header along with a message map:

//    MESSAGE void __fastcall UserIntHandler(TMyIntMessage &msg);
    MESSAGE void __fastcall UserStructHandler(TMyStruct &msg);
//    MESSAGE void __fastcall UserGetStructHandler(TMyStruct &msg);
//    MESSAGE void __fastcall UserTextHandler(TMyTextMessage &msg);

    BEGIN_MESSAGE_MAP
 //       MESSAGE_HANDLER(WM_INTMESSAGE, 			TMyIntMessage, 	UserIntHandler);
//        MESSAGE_HANDLER(WM_GETSTRUCTMESSAGE, 	TMyStruct, 		UserGetStructHandler);
        MESSAGE_HANDLER(WM_STRUCTMESSAGE, 		TMyStruct, 		UserStructHandler);
//        MESSAGE_HANDLER(WM_TEXTMESSAGE, 		TMyTextMessage, UserTextHandler);
    END_MESSAGE_MAP(TComponent)






};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
