// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// $Rev: 52393 $
// File generated on 1/16/2018 10:34:38 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files (x86)\VideoLAN\VLC\axvlc.dll (1)
// LIBID: {DF2BBE39-40A8-433B-A279-073F48DA94B6}
// LCID: 0
// Helpfile: 
// HelpString: VideoLAN VLC ActiveX Plugin
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\SysWOW64\stdole2.tlb)
// SYS_KIND: SYS_WIN32
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#pragma option -w-8122
#include "AXVLC_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Axvlc_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TVLCPlugin2 which
// allows "VLC control" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TVLCPlugin2::EventDispIDs[17] = {
    0x000000C8, 0x000000C9, 0x000000CA, 0x000000CB, 0x000000CC, 0x000000CD,
    0x000000CE, 0x000000CF, 0x000000D0, 0x000000D1, 0x000000D2, 0x000000D3,
    0x000000D4, 0x000000D5, 0x000000D6, 0x000000D7, 0x000000D8};

Vcl::Olectrls::TControlData2 TVLCPlugin2::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x9BE31822, 0xFDAD, 0x461B,{ 0xAD, 0x51, 0xBE,0x1D, 0x1C, 0x15,0x99, 0x21} }, // CoClass
  {0xDF48072F, 0x5EF8, 0x434E,{ 0x9B, 0x40, 0xE2,0xF3, 0xAE, 0x75,0x9B, 0x5F} }, // Events

  // Count of Events and array of their DISPIDs
  17, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x80004002)

  // Flags for OnChanged PropertyNotification
  0x00000000,
  401,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  0, Winapi::Activex::PDispIDList(NULL),

  // Count of Pict Prop and array of their DISPIDs
  0, Winapi::Activex::PDispIDList(NULL),
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TVLCPlugin2::DEF_CTL_INTF = {0x2D719729, 0x5333, 0x406C,{ 0xBF, 0x12, 0x8D,0xE7, 0x87, 0xFD,0x65, 0xE3} };
TNoParam TVLCPlugin2::OptParam;

static inline void ValidCtrCheck(TVLCPlugin2 *)
{
   delete new TVLCPlugin2((System::Classes::TComponent*)(0));
};

void __fastcall TVLCPlugin2::InitControlData()
{
  ControlData = (Vcl::Olectrls::TControlData*)&CControlData;
  CControlData.FirstEventOfs = System::PByte(&FOnMediaPlayerNothingSpecial) - System::PByte(this);
};

void __fastcall TVLCPlugin2::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

TCOMIVLCControl2 __fastcall TVLCPlugin2::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

BSTR __fastcall TVLCPlugin2::getVersionInfo(void)
{
  BSTR version = 0;
  OLECHECK(GetDefaultInterface()->getVersionInfo((BSTR*)&version));
  return version;
}

Axvlc_tlb::IVLCAudioPtr __fastcall TVLCPlugin2::get_audio(void)
{
  Axvlc_tlb::IVLCAudioPtr obj;
  OLECHECK(GetDefaultInterface()->get_audio(&obj));
  return obj;
}

Axvlc_tlb::IVLCInputPtr __fastcall TVLCPlugin2::get_input(void)
{
  Axvlc_tlb::IVLCInputPtr obj;
  OLECHECK(GetDefaultInterface()->get_input(&obj));
  return obj;
}

Axvlc_tlb::IVLCPlaylistPtr __fastcall TVLCPlugin2::get_playlist(void)
{
  Axvlc_tlb::IVLCPlaylistPtr obj;
  OLECHECK(GetDefaultInterface()->get_playlist(&obj));
  return obj;
}

Axvlc_tlb::IVLCSubtitlePtr __fastcall TVLCPlugin2::get_subtitle(void)
{
  Axvlc_tlb::IVLCSubtitlePtr obj;
  OLECHECK(GetDefaultInterface()->get_subtitle(&obj));
  return obj;
}

Axvlc_tlb::IVLCVideoPtr __fastcall TVLCPlugin2::get_video(void)
{
  Axvlc_tlb::IVLCVideoPtr obj;
  OLECHECK(GetDefaultInterface()->get_video(&obj));
  return obj;
}

Axvlc_tlb::IVLCMediaDescriptionPtr __fastcall TVLCPlugin2::get_mediaDescription(void)
{
  Axvlc_tlb::IVLCMediaDescriptionPtr obj;
  OLECHECK(GetDefaultInterface()->get_mediaDescription(&obj));
  return obj;
}


};     // namespace Axvlc_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Axvlc_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  System::Classes::TComponentClass cls_ocx[] = {
                              __classid(Axvlc_tlb::TVLCPlugin2)
                           };
  System::Classes::RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Axvlc_ocx
