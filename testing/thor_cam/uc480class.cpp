//#include "stdafx.h"

#include "uc480class.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cuc480::Cuc480 () : Cuc480Dll()
{
  m_hu = NULL;

  Connect(DRIVER_DLL_NAME);
}


Cuc480::~Cuc480 ()
{
  Disconnect();
}


int Cuc480::InitCamera (int nId, HWND hwnd)
{
  int nRet = IS_CANT_OPEN_DEVICE;
  HCAM hu = (HCAM) nId;

  if((m_hu == NULL) && IsLoaded())
  {
    nRet = is_InitCamera (&hu, hwnd);

    if (nRet == IS_SUCCESS)
    {
      m_hu = hu;
      m_hwnd = hwnd;

      // Disable Autoexit
      is_EnableAutoExit( m_hu, IS_DISABLE_AUTO_EXIT );
    }
  }

  return nRet;
}


int Cuc480::ExitCamera ()
{
  int nRet = IS_CANT_CLOSE_DEVICE;

  if(m_hu != NULL)
  {
    nRet = is_ExitCamera (m_hu);
    m_hu = NULL;
  }

  return nRet;
}


int Cuc480::SetErrorReport (int lMode)
{
  return is_SetErrorReport (m_hu, lMode);
}


int Cuc480::GetNumberOfCameras (int* plNumCameras)
{
  return is_GetNumberOfCameras (plNumCameras);
}


int Cuc480::GetDllVersion (int* plDllVers)
{
  *plDllVers = is_GetDLLVersion();
  return IS_SUCCESS;
}


int Cuc480::GetColorDepth (int* plBpp, int* plColFormat)
{
  return is_GetColorDepth (m_hu, plBpp, plColFormat);
}


int Cuc480::CameraStatus (int lInfo, long lValue)
{
  return is_CameraStatus (m_hu, lInfo, (ULONG)lValue);
}


int Cuc480::GetCameraType ()
{
  return is_GetCameraType (m_hu);
}


int Cuc480::GetOsVersion ()
{
  return is_GetOsVersion ();
}


int Cuc480::SetBrightness (int lBright)
{
  return is_SetBrightness (m_hu, lBright);
}


int Cuc480::SetContrast (int lCont)
{
  return is_SetContrast (m_hu, lCont);
}


int Cuc480::SetGamma (int lGamma)
{
  return is_SetGamma (m_hu, lGamma);
}


int Cuc480::SetWhiteBalance( INT nMode )
{
  return is_SetWhiteBalance(m_hu, nMode);
}


int Cuc480::SetWhiteBalanceMultipliers(double dblRed, double dblGreen, double dblBlue )
{
  return is_SetWhiteBalanceMultipliers(m_hu, dblRed, dblGreen, dblBlue);
}


int Cuc480::SetColorMode (int lMode)
{
  return is_SetColorMode (m_hu, lMode);
}


int Cuc480::InitEvent (HANDLE hEv, int nWhich)
{
  return is_InitEvent (m_hu, hEv, nWhich);
}


int Cuc480::EnableEvent (int nWhich)
{
  return is_EnableEvent (m_hu, nWhich);
}


int Cuc480::DisableEvent (int nWhich)
{
  return is_DisableEvent (m_hu, nWhich);
}


int Cuc480::ExitEvent (int nWhich)
{
  return is_ExitEvent (m_hu, nWhich);
}


int Cuc480::EnableMessage (int nWhich, HWND hwnd)
{
  return is_EnableMessage(m_hu, nWhich, hwnd);
}


int Cuc480::EnableAutoExit (int nMode)
{
  return is_EnableAutoExit(m_hu, nMode);
}


int Cuc480::SetImageSize (int lWidth, int lHeight)
{
  return is_SetImageSize (m_hu, lWidth, lHeight);
}


int Cuc480::SetImagePos (int lPosX, int lPosY)
{
  return is_SetDisplayPos (m_hu, lPosX, lPosY);
}


int Cuc480::SetDisplayMode (int Mode)
{
  return is_SetDisplayMode (m_hu, Mode);
}


int Cuc480::SetDisplayWindow (HWND hWnd)
{
  return is_SetHwnd (m_hu, hWnd);
}


int Cuc480::SetDisplayKeyColor (int lKeyCol)
{
  return is_SetKeyColor (m_hu, (lKeyCol & 0x00FF0000) >> 16, (lKeyCol & 0x0000FF00) >> 8, lKeyCol & 0x000000FF);
}


int Cuc480::UpdateDisplay ()
{
  return is_UpdateDisplay (m_hu);
}


int Cuc480::CaptureVideo (int lWait)
{
  return is_CaptureVideo (m_hu, lWait);
}


int Cuc480::StopLiveVideo (int lWait)
{
  return is_StopLiveVideo (m_hu, lWait);
}


int Cuc480::FreezeVideo (int lWait)
{
  return is_FreezeVideo (m_hu, lWait);
}


int Cuc480::AllocImageMem (int lWidth, int lHeight, int lBpp, char** ppcImgMem, int* plID)
{
  return is_AllocImageMem (m_hu, lWidth, lHeight, lBpp, ppcImgMem, plID);
}


int Cuc480::FreeImageMem (char* pcMem, int lID)
{
  return is_FreeImageMem (m_hu, pcMem, lID);
}


int Cuc480::SetImageMem (char* pcMem, int lID)
{
  return is_SetImageMem (m_hu, pcMem, lID);
}


int Cuc480::GetActiveImageMem (char** ppcImgMem, int* plID)
{
  return is_GetActiveImageMem (m_hu, ppcImgMem, plID);
}


int Cuc480::InquireImageMem (char* pcMem, int lID, int* plX, int* plY, int* plBpp, int* plPitch)
{
  return is_InquireImageMem (m_hu, pcMem, lID, plX, plY, plBpp, plPitch);
}


int Cuc480::ReadTriggerPort (int* plIn)
{
  int nRet = IS_SUCCESS;

  if(plIn != NULL)
    *plIn = is_SetExternalTrigger (m_hu, IS_GET_TRIGGER_INPUTS);
  else
    nRet = IS_NULL_POINTER;

  return nRet;
}


int Cuc480::ReadDigitalPort (int* plIn)
{
  int nRet = IS_SUCCESS;

  if(plIn != NULL)
    *plIn = is_SetIO (m_hu, IS_GET_IO);
  else
    nRet = IS_NULL_POINTER;

  return nRet;
}


int Cuc480::WriteDigitalPort (int lOut)
{
  return is_SetIO (m_hu, lOut);
}


int Cuc480::SetExternalTrigger (int lMode)
{
  return is_SetExternalTrigger (m_hu, lMode);
}


int Cuc480::GetCameraInfo (CAMINFO* pInfo)
{
  int nRet = IS_SUCCESS;

  if(pInfo != NULL)
    nRet = is_GetCameraInfo (m_hu, pInfo);
  else
    nRet = IS_NULL_POINTER;

  return nRet;
}


int Cuc480::ReadEEPROM (int lAdr, char* pcBuf, int lCount)
{
  int nRet = IS_SUCCESS;

  if(pcBuf != NULL)
    nRet = is_ReadEEPROM (m_hu, lAdr, pcBuf, lCount);
  else
    nRet = IS_INVALID_PARAMETER;

  return nRet;
}


int Cuc480::WriteEEPROM (int lAdr, char* pcBuf, int lCount)
{
  int nRet = IS_SUCCESS;

  if(pcBuf != NULL)
    nRet = is_WriteEEPROM (m_hu, lAdr, pcBuf, lCount);
  else
    nRet = IS_INVALID_PARAMETER;

  return nRet;
}


int Cuc480::SaveImage (char* pcFile)
{
  return is_SaveImage (m_hu, pcFile);
}


int Cuc480::LoadImage (char* pcFile)
{
  return is_LoadImage (m_hu, pcFile);
}


int Cuc480::SaveImageMem (char* pcFile, char* pcMem, int lID)
{
  return is_SaveImageMem (m_hu, pcFile, pcMem, lID);
}


int Cuc480::RenderBitmap (int nMemID, HWND hwnd, int nMode)
{
  return is_RenderBitmap(m_hu, nMemID, hwnd, nMode);
}

int	Cuc480::GetPixelClockRange	( int *nMin, int *nMax )
{
	if( m_hu == NULL )
		return IS_NO_SUCCESS;
	else
		return is_GetPixelClockRange( m_hu, nMin, nMax );
}

int Cuc480::SetPixelClock(int nClock)
{
  return is_SetPixelClock(m_hu, nClock);
}

int Cuc480::SetFrameRate(double dFr, double* pdFrNew)
{
  return is_SetFrameRate(m_hu, dFr, pdFrNew);
}

int Cuc480::SetExposureTime(double EXP, double* newEXP )
{
  return is_SetExposureTime(m_hu, EXP, newEXP );
}


int Cuc480::EnableDeviceStateNotification(BOOL boEnable, HWND hwnd)
{
  int nRet;

  if(hwnd == NULL)
  {
    if(m_hwndNotify != NULL)
      hwnd = m_hwndNotify;
  }

  if(!boEnable)
    hwnd = NULL;

	nRet = is_EnableMessage( NULL, IS_NEW_DEVICE, hwnd );
  if(nRet == IS_SUCCESS)
  {
	  nRet = is_EnableMessage( NULL, IS_DEVICE_REMOVAL, hwnd );
    if(nRet == IS_SUCCESS)
      m_hwndNotify = hwnd;
  }

  return nRet;
}


int Cuc480::GetSensorInfo( PSENSORINFO pInfo )
{
  return is_GetSensorInfo( m_hu, pInfo );
}


int Cuc480::LoadParameters( char* pFilename)
{
    return is_LoadParameters( m_hu, pFilename );
}


int Cuc480::DirectRenderer(UINT nMode, void* pParam, UINT nSizeOfParam) 
{
    return is_DirectRenderer(m_hu, nMode, pParam, nSizeOfParam);
}


void Cuc480::GetMaxImageSize(INT *pnSizeX, INT *pnSizeY)
{
    // Check if the camera supports an arbitrary AOI
    INT nAOISupported = 0;
    BOOL bAOISupported = TRUE;
    if (is_ImageFormat(m_hu,
                       IMGFRMT_CMD_GET_ARBITRARY_AOI_SUPPORTED, 
                       (void*)&nAOISupported, 
                       sizeof(nAOISupported)) == IS_SUCCESS)
    {
        bAOISupported = (nAOISupported != 0);
    }

    if (bAOISupported)
    {
        // Get maximum image size
	    SENSORINFO sInfo;
	    is_GetSensorInfo (m_hu, &sInfo);
	    *pnSizeX = sInfo.nMaxWidth;
	    *pnSizeY = sInfo.nMaxHeight;
    }
    else
    {
        // Get image size of the current format
        *pnSizeX = is_SetImageSize(m_hu, IS_GET_IMAGE_SIZE_X, 0);
        *pnSizeY = is_SetImageSize(m_hu, IS_GET_IMAGE_SIZE_Y, 0);
    }
}