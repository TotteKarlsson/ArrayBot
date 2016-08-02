//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
//###########################################################################//
//#                                                                         #//
//# Functions here will be wrapped automatically                            #//
//# in the Cuc480Dll class.                                                 #//
//#                                                                         #//
//#     (c) 2004 - 2014                                                     #//
//#                                                                         #//
//###########################################################################//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///

USB2CAMERA_MACRO_DO(SetVideoInput)
DECLARE((HCAM hf, INT Source))

USB2CAMERA_MACRO_DO(SetHue)
DECLARE((HCAM hf, INT Hue))

USB2CAMERA_MACRO_DO(SetVideoMode)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(SetAGC)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(SetSyncLevel)
DECLARE((HCAM hf, INT Level))

USB2CAMERA_MACRO_DO(ShowColorBars)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(SetScaler)
DECLARE((HCAM hf, float Scalex, float Scaley))

USB2CAMERA_MACRO_DO(SetCaptureMode)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(SetHorFilter)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(SetVertFilter)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(EnableDDOverlay)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(DisableDDOverlay)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(ShowDDOverlay)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(HideDDOverlay)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(ScaleDDOverlay)
DECLARE((HCAM hf, BOOL boScale))

USB2CAMERA_MACRO_DO(SetDDUpdateTime)
DECLARE((HCAM hf, INT ms))

USB2CAMERA_MACRO_DO(GetCurrentField)
DECLARE((HCAM hf, int* pField))

USB2CAMERA_MACRO_DO(SetVideoSize)
DECLARE((HCAM hf, INT xpos, INT ypos, INT xsize, INT ysize))

USB2CAMERA_MACRO_DO(SetKeyOffset)
DECLARE((HCAM hf, INT offX, INT offY))

USB2CAMERA_MACRO_DO(PrepareStealVideo)
DECLARE((HCAM hf, int Mode, ULONG StealColorMode))

USB2CAMERA_MACRO_DO(SetParentHwnd)
DECLARE((HCAM hf, HWND hwnd))

USB2CAMERA_MACRO_DO(SetUpdateMode)
DECLARE((HCAM hf, INT mode))

USB2CAMERA_MACRO_DO(OvlSurfaceOffWhileMove)
DECLARE((HCAM hf, BOOL boMode))

USB2CAMERA_MACRO_DO(GetPciSlot)
DECLARE((HCAM hf, INT* pnSlot))

USB2CAMERA_MACRO_DO(GetIRQ)
DECLARE((HCAM hf, INT* pnIRQ))

USB2CAMERA_MACRO_DO(SetToggleMode)
DECLARE((HCAM hf, int nInput1, int nInput2, int nInput3, int nInput4))

USB2CAMERA_MACRO_DO(SetSync)
DECLARE((HCAM hf, INT nSync))

USB2CAMERA_MACRO_DO(SetVideoCrossbar)
DECLARE((HCAM hf, INT In, INT Out))

USB2CAMERA_MACRO_DO(InitBoard)
DECLARE((HCAM* phf, HWND hWnd))

USB2CAMERA_MACRO_DO(ExitBoard)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(InitFalcon)
DECLARE((HCAM* phf, HWND hWnd))

USB2CAMERA_MACRO_DO(ExitFalcon)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(GetBoardType)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(GetBoardInfo)
DECLARE((HCAM hf, PBOARDINFO pInfo))

USB2CAMERA_MACRO_DO(BoardStatus)
DECLARE((HCAM hf, INT nInfo, ULONG ulValue))

USB2CAMERA_MACRO_DO(GetNumberOfDevices)
DECLARE((void))

USB2CAMERA_MACRO_DO(GetNumberOfBoards)
DECLARE((INT* pnNumBoards))

USB2CAMERA_MACRO_DO(StopLiveVideo)
DECLARE((HCAM hf, INT Wait))

USB2CAMERA_MACRO_DO(FreezeVideo)
DECLARE((HCAM hf, INT Wait))

USB2CAMERA_MACRO_DO(CaptureVideo)
DECLARE((HCAM hf, INT Wait))

USB2CAMERA_MACRO_DO(IsVideoFinish)
DECLARE((HCAM hf, BOOL* pbo))

USB2CAMERA_MACRO_DO(HasVideoStarted)
DECLARE((HCAM hf,  BOOL* pbo))

USB2CAMERA_MACRO_DO(SetSaturation)
DECLARE((HCAM hf, INT ChromU, INT ChromV))

USB2CAMERA_MACRO_DO(SetBrightness)
DECLARE((HCAM hf, INT Bright))

USB2CAMERA_MACRO_DO(SetContrast)
DECLARE((HCAM hf, INT Cont))

USB2CAMERA_MACRO_DO(SetGamma)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(AllocImageMem)
DECLARE((HCAM hf, INT width, INT height, INT bitspixel, char** ppcImgMem, int* pid))

USB2CAMERA_MACRO_DO(SetImageMem)
DECLARE((HCAM hf, char* pcMem, int id))

USB2CAMERA_MACRO_DO(FreeImageMem)
DECLARE((HCAM hf, char* pcMem, int id))

USB2CAMERA_MACRO_DO(GetImageMem)
DECLARE((HCAM hf, VOID** pMem))

USB2CAMERA_MACRO_DO(GetActiveImageMem)
DECLARE((HCAM hf, char** pccMem, int* pnID ))

USB2CAMERA_MACRO_DO(InquireImageMem)
DECLARE((HCAM hf, char* pcMem, int nID, int* pnX, int* pnY, int* pnBits, int* pnPitch))

USB2CAMERA_MACRO_DO(GetImageMemPitch)
DECLARE((HCAM hf, INT* pPitch))

USB2CAMERA_MACRO_DO(SetAllocatedImageMem)
DECLARE((HCAM hf, INT width, INT height, INT bitspixel, char* pcImgMem, int* pid))

USB2CAMERA_MACRO_DO(SaveImageMem)
DECLARE((HCAM hf, const IS_CHAR* File, char* pcMem, int nID))

USB2CAMERA_MACRO_DO(CopyImageMem)
DECLARE((HCAM hf, char* pcSource, int nID, char* pcDest))

USB2CAMERA_MACRO_DO(CopyImageMemLines)
DECLARE((HCAM hf, char* pcSource, int nID, int nLines, char* pcDest))

USB2CAMERA_MACRO_DO(AddToSequence)
DECLARE((HCAM hf, char* pcImgMem, int nId))

USB2CAMERA_MACRO_DO(ClearSequence)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(GetActSeqBuf)
DECLARE((HCAM hf, INT* pnNum, char** ppcMem, char** ppcMemLast))

USB2CAMERA_MACRO_DO(LockSeqBuf)
DECLARE((HCAM hf, INT nNum, char* pcMem))

USB2CAMERA_MACRO_DO(UnlockSeqBuf)
DECLARE((HCAM hf, INT nNum, char* pcMem))

USB2CAMERA_MACRO_DO(SetImageSize)
DECLARE((HCAM hf, INT x, INT y))

USB2CAMERA_MACRO_DO(SetImagePos)
DECLARE((HCAM hf, INT x, INT y))

USB2CAMERA_MACRO_DO(GetError)
DECLARE((HCAM hf, INT* pErr, IS_CHAR** ppcErr))

USB2CAMERA_MACRO_DO(SetErrorReport)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(ReadEEPROM)
DECLARE((HCAM hf, INT Adr, char* pcString, INT Count))

USB2CAMERA_MACRO_DO(WriteEEPROM)
DECLARE((HCAM hf, INT Adr, char* pcString, INT Count))

USB2CAMERA_MACRO_DO(SaveImage)
DECLARE((HCAM hf, const IS_CHAR* File))

USB2CAMERA_MACRO_DO(SetColorMode)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(GetColorDepth)
DECLARE((HCAM hf, INT* pnCol, INT* pnColMode))

USB2CAMERA_MACRO_DO(RenderBitmap)
DECLARE((HCAM hf, INT nMemID, HWND hwnd, INT nMode))

USB2CAMERA_MACRO_DO(SetDisplayMode)
DECLARE((HCAM hf, INT Mode))

USB2CAMERA_MACRO_DO(GetDC)
DECLARE((HCAM hf, HDC* phDC))

USB2CAMERA_MACRO_DO(ReleaseDC)
DECLARE((HCAM hf, HDC hDC))

USB2CAMERA_MACRO_DO(UpdateDisplay)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(SetDisplaySize)
DECLARE((HCAM hf, INT x, INT y))

USB2CAMERA_MACRO_DO(SetDisplayPos)
DECLARE((HCAM hf, INT x, INT y))

USB2CAMERA_MACRO_DO(LockDDOverlayMem)
DECLARE((HCAM hf, VOID** ppMem, INT* pPitch))

USB2CAMERA_MACRO_DO(UnlockDDOverlayMem)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(LockDDMem)
DECLARE((HCAM hf, VOID** ppMem, INT* pPitch))

USB2CAMERA_MACRO_DO(UnlockDDMem)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(GetDDOvlSurface)
DECLARE((HCAM hf, void** ppDDSurf))

USB2CAMERA_MACRO_DO(SetKeyColor)
DECLARE((HCAM hf, INT r, INT g, INT b ))

USB2CAMERA_MACRO_DO(StealVideo)
DECLARE((HCAM hf, int Wait))

USB2CAMERA_MACRO_DO(SetHwnd)
DECLARE((HCAM hf, HWND hwnd))

USB2CAMERA_MACRO_DO(GetVsyncCount)
DECLARE((HCAM hf, long* pIntr, long* pActIntr))

USB2CAMERA_MACRO_DO(GetOsVersion)
DECLARE((void))

USB2CAMERA_MACRO_DO(GetDLLVersion)
DECLARE((void))

USB2CAMERA_MACRO_DO(InitEvent)
DECLARE((HCAM hf, HANDLE hEv, INT which))

USB2CAMERA_MACRO_DO(ExitEvent)
DECLARE((HCAM hf, INT which))

USB2CAMERA_MACRO_DO(EnableEvent)
DECLARE((HCAM hf, INT which))

USB2CAMERA_MACRO_DO(DisableEvent)
DECLARE((HCAM hf, INT which))

USB2CAMERA_MACRO_DO(SetIO)
DECLARE((HCAM hf, INT nIO))

USB2CAMERA_MACRO_DO(SetFlashStrobe)
DECLARE((HCAM hf, INT nMode, INT nLine))

USB2CAMERA_MACRO_DO(SetExternalTrigger)
DECLARE((HCAM hf, INT nTriggerMode))

USB2CAMERA_MACRO_DO(SetRopEffect)
DECLARE((HCAM hf, INT effect, INT param, INT reserved))

USB2CAMERA_MACRO_DO(InitCamera)
DECLARE((HCAM* phf, HWND hWnd))

USB2CAMERA_MACRO_DO(ExitCamera)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(GetCameraInfo)
DECLARE((HCAM hf, PBOARDINFO pInfo))

USB2CAMERA_MACRO_DO(CameraStatus)
DECLARE((HCAM hf, INT nInfo, ULONG ulValue))

USB2CAMERA_MACRO_DO(GetCameraType)
DECLARE((HCAM hf))

USB2CAMERA_MACRO_DO(GetNumberOfCameras)
DECLARE((INT* pnNumCams))

USB2CAMERA_MACRO_DO(GetPixelClockRange)
DECLARE(( HCAM hf, INT *pnMIn, INT *pnMax ))

USB2CAMERA_MACRO_DO(SetPixelClock)
DECLARE((HCAM hf, INT nClock))

USB2CAMERA_MACRO_DO(GetUsedBandwidth)
DECLARE(( HCAM hf ))

USB2CAMERA_MACRO_DO(GetFrameTimeRange)
DECLARE(( HCAM hf, double *min, double *max, double *intervall ))

USB2CAMERA_MACRO_DO(SetFrameRate)
DECLARE(( HCAM hf, double FPS, double* newFPS ))

USB2CAMERA_MACRO_DO(GetExposureRange)
DECLARE(( HCAM hf, double *min, double *max, double *intervall ))

USB2CAMERA_MACRO_DO(SetExposureTime)
DECLARE(( HCAM hf, double EXP, double* newEXP ))

USB2CAMERA_MACRO_DO(GetFramesPerSecond)
DECLARE(( HCAM hf, double *dblFPS ))

USB2CAMERA_MACRO_DO(SetIOMask)
DECLARE((HCAM hf, INT nMask))

USB2CAMERA_MACRO_DO(GetSensorInfo)
DECLARE((HCAM hf, PSENSORINFO pInfo ))

USB2CAMERA_MACRO_DO(GetRevisionInfo)
DECLARE(( HCAM hf, PREVISIONINFO prevInfo ))

USB2CAMERA_MACRO_DO(EnableAutoExit)
DECLARE(( HCAM hf, INT nMode ))

USB2CAMERA_MACRO_DO(EnableMessage)
DECLARE((HCAM hf, INT which, HWND hWnd))

USB2CAMERA_MACRO_DO(SetHardwareGain)
DECLARE((HCAM hf, INT nMaster, INT nRed, INT nGreen, INT nBlue ))

USB2CAMERA_MACRO_DO(SetRenderMode)
DECLARE(( HCAM hf, INT Mode ))

USB2CAMERA_MACRO_DO(SetWhiteBalance)
DECLARE(( HCAM hf, INT nMode ))

USB2CAMERA_MACRO_DO(SetWhiteBalanceMultipliers)
DECLARE(( HCAM hf, double dblRed, double dblGreen, double dblBlue ))

USB2CAMERA_MACRO_DO(GetWhiteBalanceMultipliers)
DECLARE(( HCAM hf, double *pdblRed, double *pdblGreen, double *pdblBlue ))

USB2CAMERA_MACRO_DO(SetEdgeEnhancement)
DECLARE(( HCAM hf, INT nEnable ))

USB2CAMERA_MACRO_DO(SetColorCorrection)
DECLARE(( HCAM hf, INT nEnable, double *factors ))

USB2CAMERA_MACRO_DO(SetBlCompensation)
DECLARE(( HCAM hf, INT nEnable, INT offset, INT reserved ))

USB2CAMERA_MACRO_DO(SetBadPixelCorrection)
DECLARE(( HCAM hf, INT nEnable, INT threshold ))

USB2CAMERA_MACRO_DO(LoadBadPixelCorrectionTable)
DECLARE(( HCAM hf, const IS_CHAR *File ))

USB2CAMERA_MACRO_DO(SaveBadPixelCorrectionTable)
DECLARE(( HCAM hf, const IS_CHAR *File ))

USB2CAMERA_MACRO_DO(SetBadPixelCorrectionTable)
DECLARE(( HCAM hf, INT nMode, WORD *pList ))

USB2CAMERA_MACRO_DO(SetMemoryMode)
DECLARE((HCAM hf, INT nCount, INT nDelay ))

USB2CAMERA_MACRO_DO(TransferImage)
DECLARE((  HCAM hf, INT nMemID, INT seqID, INT imageNr, INT reserved ))

USB2CAMERA_MACRO_DO(TransferMemorySequence)
DECLARE(( HCAM hf, INT seqID, INT StartNr, INT nCount, INT nSeqPos ))

USB2CAMERA_MACRO_DO(MemoryFreezeVideo)
DECLARE(( HCAM hf, INT nMemID, INT Wait ))

USB2CAMERA_MACRO_DO(GetLastMemorySequence)
DECLARE(( HCAM hf, INT *pID ))

USB2CAMERA_MACRO_DO(GetNumberOfMemoryImages)
DECLARE(( HCAM hf, INT pID, INT *pnCount ))

USB2CAMERA_MACRO_DO(GetMemorySequenceWindow)
DECLARE(( HCAM hf, INT nID, INT *left, INT *top, INT *right, INT *bottom ))

USB2CAMERA_MACRO_DO(IsMemoryBoardConnected)
DECLARE(( HCAM hf, BOOL* pConnected  ))

USB2CAMERA_MACRO_DO(ResetMemory)
DECLARE(( HCAM hf, INT nReserved ))

USB2CAMERA_MACRO_DO(SetSubSampling)
DECLARE(( HCAM hf, INT mode ))

USB2CAMERA_MACRO_DO(ForceTrigger)
DECLARE(( HCAM hf ))

USB2CAMERA_MACRO_DO(GetBusSpeed)
DECLARE(( HCAM hf  ))

USB2CAMERA_MACRO_DO(SetBinning)
DECLARE(( HCAM hf, INT mode ))

USB2CAMERA_MACRO_DO(ResetToDefault)
DECLARE(( HCAM hf ))

USB2CAMERA_MACRO_DO(LoadParameters)
DECLARE(( HCAM hf, const IS_CHAR* pFilename ))

USB2CAMERA_MACRO_DO(SaveParameters)
DECLARE(( HCAM hf, const IS_CHAR* pFilename ))

USB2CAMERA_MACRO_DO(GetGlobalFlashDelays)
DECLARE(( HCAM hf, ULONG *pulDelay, ULONG *pulDuration ))

USB2CAMERA_MACRO_DO(SetFlashDelay)
DECLARE(( HCAM hf, ULONG ulDelay, ULONG ulDuration  ))

USB2CAMERA_MACRO_DO(LoadImage)
DECLARE((HCAM hf, const IS_CHAR* File))

USB2CAMERA_MACRO_DO(SetImageAOI)
DECLARE(( HCAM hf, INT xPos, INT yPos, INT width, INT height  ))

USB2CAMERA_MACRO_DO(SetCameraID)
DECLARE(( HCAM hf, INT nID  ))

USB2CAMERA_MACRO_DO(SetBayerConversion)
DECLARE(( HCAM hf, INT nMode  ))

USB2CAMERA_MACRO_DO(SetTestImage)
DECLARE(( HCAM hf, INT nMode  ))

USB2CAMERA_MACRO_DO(SetHardwareGamma)
DECLARE(( HCAM hf, INT nMode  ))

USB2CAMERA_MACRO_DO(GetCameraList)
DECLARE(( PUC480_CAMERA_LIST pucl  ))

USB2CAMERA_MACRO_DO(SetAOI)
DECLARE(( HCAM hf, INT type, INT *pXPos, INT *pYPos, INT *pWidth, INT *pHeight ))

USB2CAMERA_MACRO_DO(SetAutoParameter)
DECLARE(( HCAM hf, INT param, double *pval1, double *pval2 ))

USB2CAMERA_MACRO_DO(GetAutoInfo)
DECLARE(( HCAM hf, UC480_AUTO_INFO *pInfo ))

USB2CAMERA_MACRO_DO(ConvertImage)
DECLARE((HCAM hf, char* pcSource, INT nIDSource, char** pcDest, INT *nIDDest, INT * reserve))

USB2CAMERA_MACRO_DO(SetConvertParam)
DECLARE((HCAM hf, BOOL ColorCorrection, INT BayerConversionMode, INT ColorMode, INT Gamma, double *WhiteBalanceMultipliers))

USB2CAMERA_MACRO_DO(SaveImageEx)
DECLARE((HCAM hf, const IS_CHAR* File, INT fileFormat, INT Param))

USB2CAMERA_MACRO_DO(SaveImageMemEx)
DECLARE((HCAM hf, const IS_CHAR* File, char* pcMem, INT nID, INT FileFormat, INT Param))

USB2CAMERA_MACRO_DO(LoadImageMem)
DECLARE((HCAM hf, const IS_CHAR* File, char** ppcImgMem, INT* pid))

USB2CAMERA_MACRO_DO(SetTriggerDelay)
DECLARE((HCAM hf, INT nTriggerDelay ))

USB2CAMERA_MACRO_DO(SetGainBoost)
DECLARE((HCAM hf, INT mode ))

USB2CAMERA_MACRO_DO(SetLED)
DECLARE(( HCAM hf, INT nValue  ))

USB2CAMERA_MACRO_DO(SetGlobalShutter)
DECLARE(( HCAM hf, INT mode  ))

USB2CAMERA_MACRO_DO(SetExtendedRegister)
DECLARE(( HCAM hf, INT index,WORD value))

USB2CAMERA_MACRO_DO(SetHWGainFactor)
DECLARE((HCAM hf, INT nMode, INT nFactor))

USB2CAMERA_MACRO_DO(Renumerate)
DECLARE(( HCAM hf, INT nMode ))

USB2CAMERA_MACRO_DO(GetExtendedRegister)
DECLARE((HCAM hf, INT index, WORD *pwValue))

USB2CAMERA_MACRO_DO(WriteI2C)
DECLARE((HCAM hf, INT nDeviceAddr, INT nRegisterAddr, BYTE* pbData, INT nLen ))

USB2CAMERA_MACRO_DO(ReadI2C)
DECLARE((HCAM hf, INT nDeviceAddr, INT nRegisterAddr, BYTE* pbData, INT nLen ))

USB2CAMERA_MACRO_DO(GetImageHistogram)
DECLARE((HCAM hf, int nID, INT ColorMode, DWORD* pHistoMem))

USB2CAMERA_MACRO_DO(WaitForNextImage)
DECLARE(( HCAM hf, UINT timeout, char **ppcMem, INT *imageID ))

USB2CAMERA_MACRO_DO(InitImageQueue)
DECLARE(( HCAM hf, INT nMode ))

USB2CAMERA_MACRO_DO(ExitImageQueue)
DECLARE(( HCAM hf ))

USB2CAMERA_MACRO_DO(GetEthDeviceInfo)
DECLARE((HCAM hf, UC480_ETH_DEVICE_INFO* pDeviceInfo, UINT uStructSize))

USB2CAMERA_MACRO_DO(SetPersistentIpCfg)
DECLARE((HCAM hf, UC480_ETH_IP_CONFIGURATION* pIpCfg, UINT uStructSize))

USB2CAMERA_MACRO_DO(SetStarterFirmware)
DECLARE((HCAM hf, const CHAR* pcFilepath, UINT uFilepathLen))

USB2CAMERA_MACRO_DO(SetAutoCfgIpSetup)
DECLARE((INT iAdapterID, const UC480_ETH_AUTOCFG_IP_SETUP* pSetup, UINT uStructSize))

USB2CAMERA_MACRO_DO(SetPacketFilter)
DECLARE((INT iAdapterID, UINT uFilterSetting))

USB2CAMERA_MACRO_DO(GetHdrMode)
DECLARE(( HCAM hf, INT *Mode ))

USB2CAMERA_MACRO_DO(EnableHdr)
DECLARE(( HCAM hf, INT Enable ))

USB2CAMERA_MACRO_DO(SetHdrKneepoints)
DECLARE(( HCAM hf, KNEEPOINTARRAY *KneepointArray, INT KneepointArraySize ))

USB2CAMERA_MACRO_DO(GetHdrKneepoints)
DECLARE(( HCAM hf, KNEEPOINTARRAY *KneepointArray, INT KneepointArraySize ))

USB2CAMERA_MACRO_DO(GetHdrKneepointInfo)
DECLARE(( HCAM hf, KNEEPOINTINFO *KneepointInfo, INT KneepointInfoSize ))

USB2CAMERA_MACRO_DO(SetOptimalCameraTiming)
DECLARE(( HCAM hf, INT Mode, INT Timeout, INT *pMaxPxlClk, double *pMaxFrameRate))

USB2CAMERA_MACRO_DO(GetComportNumber)
DECLARE((HCAM hf, UINT *ComportNumber))

USB2CAMERA_MACRO_DO(SetColorConverter)
DECLARE((HCAM hf, INT ColorMode, INT ConvertMode))

USB2CAMERA_MACRO_DO(GetColorConverter)
DECLARE((HCAM hf, INT ColorMode, INT *pCurrentConvertMode, INT *pDefaultConvertMode, INT *pSupportedConvertModes))

USB2CAMERA_MACRO_DO(SetCameraLUT)
DECLARE((HCAM hf, UINT Mode, UINT NumberOfEntries, double *pRed_Grey, double *pGreen, double *pBlue))

USB2CAMERA_MACRO_DO(GetCameraLUT)
DECLARE((HCAM hf, UINT Mode, UINT NumberOfEntries, double *pRed_Grey, double *pGreen, double *pBlue))

USB2CAMERA_MACRO_DO(GetSupportedTestImages)
DECLARE((HCAM hf, INT *SupportedTestImages))

USB2CAMERA_MACRO_DO(GetTestImageValueRange)
DECLARE((HCAM hf, INT TestImage, INT *TestImageValueMin, INT *TestImageValueMax))

USB2CAMERA_MACRO_DO(SetSensorTestImage)
DECLARE((HCAM hf, INT Param1, INT Param2))

USB2CAMERA_MACRO_DO(SetTimeout)
DECLARE(( HCAM hf, UINT nMode, UINT Timeout ))

USB2CAMERA_MACRO_DO(GetTimeout)
DECLARE(( HCAM hf, UINT nMode, UINT *pTimeout ))

USB2CAMERA_MACRO_DO(GetImageInfo)
DECLARE(( HCAM hf, INT nID, UC480IMAGEINFO *pImageInfo, INT ImageInfoSize ))

USB2CAMERA_MACRO_DO(GetDuration)
DECLARE(( HCAM hf, UINT nMode, INT *pnTime ))

USB2CAMERA_MACRO_DO(GetSensorScalerInfo)
DECLARE(( HCAM hf, SENSORSCALERINFO *pSensorScalerInfo, INT nSensorScalerInfoSize ))

USB2CAMERA_MACRO_DO(SetSensorScaler)
DECLARE(( HCAM hf, UINT nMode, double dblFactor ))

USB2CAMERA_MACRO_DO(DirectRenderer)
DECLARE(( HCAM hf, UINT nMode, void *pParam, UINT SizeOfParam ))

USB2CAMERA_MACRO_DO(ImageFormat)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(FaceDetection)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Focus)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(ImageStabilization)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(ScenePreset)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Zoom)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Sharpness)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Saturation)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(TriggerDebounce)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(ColorTemperature)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(HotPixel)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(AOI)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Transfer)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(IpConfig)
DECLARE(( INT iID, UC480_ETH_ADDR_MAC mac, UINT nCommand, void* pParam, UINT cbSizeOfParam ))

USB2CAMERA_MACRO_DO(DeviceFeature)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Exposure)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Configuration)
DECLARE(( UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Trigger)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(IO)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(CaptureStatus)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(BootBoost)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(PixelClock)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(DeviceInfo)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(ImageFile)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(ParameterSet)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(EdgeEnhancement)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(AutoParameter)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Convert)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Blacklevel)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Measure)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(ImageBuffer)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(OptimalCameraTiming)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(LUT)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Gamma)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

USB2CAMERA_MACRO_DO(Memory)
DECLARE(( HCAM hf, UINT nCommand, void *pParam, UINT nSizeOfParam ))

