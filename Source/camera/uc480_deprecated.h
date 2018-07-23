/*****************************************************************************/
/*! \file    uc480_deprecated.h

*   \date    Date: 2014/01/29
*   \version PRODUCTVERSION: 4.40
*
*   \brief   Library interface for uc480 - camera family.
*            definition of deprecated API functions and constants
*//***************************************************************************/

#ifndef __UC480_HEADER_DEPRECATED__
#define __UC480_HEADER_DEPRECATED__

#pragma pack(push, 8)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/* make sure __LINUX__ is defined */
#if defined __linux__
#   if !defined __LINUX__
#       define __LINUX__
#   endif /* ! __LINUX__ */
#endif /* __linux__ */


/* Render modes */
#define IS_RENDER_DOUBLE_HEIGHT               0x0020    
#define IS_RENDER_HALF_HEIGHT                 0x0040    


/* Old trigger defines */
#define IS_SET_TRIG_OFF                       0x0000    
#define IS_SET_TRIG_HI_LO                     0x0001    
#define IS_SET_TRIG_LO_HI                     0x0002    
#define IS_SET_TRIG_SOFTWARE                  0x0008    
#define IS_SET_TRIG_HI_LO_SYNC                0x0010    
#define IS_SET_TRIG_LO_HI_SYNC                0x0020    
#define IS_SET_TRIG_MASK                      0x0100    


/* Old defines for flash */
#define IS_GET_FLASHSTROBE_MODE               0x8000    
#define IS_GET_FLASHSTROBE_LINE               0x8001    
#define IS_GET_SUPPORTED_FLASH_IO_PORTS       0x8002    

#define IS_SET_FLASH_OFF                           0    
#define IS_SET_FLASH_ON                            1    
#define IS_SET_FLASH_LO_ACTIVE              IS_SET_FLASH_ON
#define IS_SET_FLASH_HI_ACTIVE                     2    
#define IS_SET_FLASH_HIGH                          3    
#define IS_SET_FLASH_LOW                           4    
#define IS_SET_FLASH_LO_ACTIVE_FREERUN             5    
#define IS_SET_FLASH_HI_ACTIVE_FREERUN             6    
#define IS_SET_FLASH_IO_1                     0x0010    
#define IS_SET_FLASH_IO_2                     0x0020    
#define IS_SET_FLASH_IO_3                     0x0040    
#define IS_SET_FLASH_IO_4                     0x0080    
#define IS_SET_FLASH_IO_5                     0x0100    
#define IS_SET_FLASH_IO_6                     0x0200    
#define IS_FLASH_IO_PORT_MASK               (IS_SET_FLASH_IO_1 | IS_SET_FLASH_IO_2 | IS_SET_FLASH_IO_3 | IS_SET_FLASH_IO_4 | IS_SET_FLASH_IO_5 | IS_SET_FLASH_IO_6)


#define IS_GET_FLASH_DELAY                        -1    
#define IS_GET_FLASH_DURATION                     -2    
#define IS_GET_MAX_FLASH_DELAY                    -3    
#define IS_GET_MAX_FLASH_DURATION                 -4    
#define IS_GET_MIN_FLASH_DELAY                    -5    
#define IS_GET_MIN_FLASH_DURATION                 -6    
#define IS_GET_FLASH_DELAY_GRANULARITY            -7    
#define IS_GET_FLASH_DURATION_GRANULARITY         -8    


/* Old defines for IO */
#define IS_GET_IO                             0x8000    
#define IS_GET_IO_MASK                        0x8000    
#define IS_GET_INPUT_MASK                     0x8001    
#define IS_GET_OUTPUT_MASK                    0x8002    
#define IS_GET_SUPPORTED_IO_PORTS             0x8004    


/* Led settings */
#define IS_SET_LED_OFF                             0    
#define IS_SET_LED_ON                              1    
#define IS_SET_LED_TOGGLE                          2    
#define IS_GET_LED                            0x8000    


/* Exposure */
#define IS_GET_EXPOSURE_TIME                  0x8000    
#define IS_GET_DEFAULT_EXPOSURE               0x8001    
#define IS_GET_EXPOSURE_MIN_VALUE             0x8002    
#define IS_GET_EXPOSURE_MAX_VALUE             0x8003    
#define IS_GET_EXPOSURE_INCREMENT             0x8004    
#define IS_GET_EXPOSURE_FINE_INCREMENT        0x8005    


/* Brightness */
#define IS_GET_BRIGHTNESS                     0x8000    
#define IS_MIN_BRIGHTNESS                          0    
#define IS_MAX_BRIGHTNESS                        255    
#define IS_DEFAULT_BRIGHTNESS                     -1    


/* Contrast */
#define IS_GET_CONTRAST                       0x8000    
#define IS_MIN_CONTRAST                            0    
#define IS_MAX_CONTRAST                          511    
#define IS_DEFAULT_CONTRAST                       -1    


/* Pixel formats */
#define IS_CM_FORMAT_PACKED                   0x0000    

#define IS_SET_CM_BAYER                           11    
#define IS_SET_CM_BAYER12                         27    
#define IS_SET_CM_BAYER16                         29    

#define IS_SET_CM_Y8                               6    
#define IS_SET_CM_Y12                             26    
#define IS_SET_CM_Y16                             28    

#define IS_SET_CM_RGB32                            0    
#define IS_SET_CM_RGB24                            1    
#define IS_SET_CM_RGB16                            2    
#define IS_SET_CM_RGB15                            3    
#define IS_SET_CM_RGB8                             7    

#define IS_SET_CM_UYVY                            12    
#define IS_SET_CM_UYVY_MONO                       13    
#define IS_SET_CM_UYVY_BAYER                      14    
#define IS_SET_CM_CBYCRY                          23    

#define IS_SET_CM_RGBY                            24    
#define IS_SET_CM_RGB30                           25    

#define IS_CM_BAYER_RG8                     IS_SET_CM_BAYER     // occupies 8 Bit
#define IS_CM_BAYER_RG12                    IS_SET_CM_BAYER12   // occupies 16 Bit
#define IS_CM_BAYER_RG16                    IS_SET_CM_BAYER16   // occupies 16 Bit

#define IS_CM_RGB10V2_PACKED                     153    // occupies 32 Bit
#define IS_CM_BGR10V2_PACKED                      25    // occupies 32 Bit

#define IS_CM_BGR555_PACKED                        3    // occupies 16 Bit

#define IS_CM_YUV422_PACKED                 //no compliant version

#define IS_CM_RGB12_PACKED                       158    
#define IS_CM_BGR12_PACKED                        30    
#define IS_CM_RGBA12_PACKED                      159    
#define IS_CM_BGRA12_PACKED                       31    


/* Hue  (Falcon) */
#define IS_GET_HUE                            0x8000    
#define IS_MIN_HUE                                 0    
#define IS_MAX_HUE                               255    
#define IS_DEFAULT_HUE                           128    


/* Image size and pos */
#define IS_GET_IMAGE_SIZE_X                   0x8000    
#define IS_GET_IMAGE_SIZE_Y                   0x8001    
#define IS_GET_IMAGE_SIZE_X_INC               0x8002    
#define IS_GET_IMAGE_SIZE_Y_INC               0x8003    
#define IS_GET_IMAGE_SIZE_X_MIN               0x8004    
#define IS_GET_IMAGE_SIZE_Y_MIN               0x8005    
#define IS_GET_IMAGE_SIZE_X_MAX               0x8006    
#define IS_GET_IMAGE_SIZE_Y_MAX               0x8007    
#define IS_GET_IMAGE_POS_X                    0x8001    
#define IS_GET_IMAGE_POS_Y                    0x8002    
#define IS_GET_IMAGE_POS_X_ABS                0xC001    
#define IS_GET_IMAGE_POS_Y_ABS                0xC002    
#define IS_GET_IMAGE_POS_X_INC                0xC003    
#define IS_GET_IMAGE_POS_Y_INC                0xC004    
#define IS_GET_IMAGE_POS_X_MIN                0xC005    
#define IS_GET_IMAGE_POS_Y_MIN                0xC006    
#define IS_GET_IMAGE_POS_X_MAX                0xC007    
#define IS_GET_IMAGE_POS_Y_MAX                0xC008    
#define IS_SET_IMAGEPOS_X_ABS                 0x8000    
#define IS_SET_IMAGEPOS_Y_ABS                 0x8000    
#define IS_SET_IMAGE_POS_X_ABS            0x00010000    
#define IS_SET_IMAGE_POS_Y_ABS            0x00010000    


/* Multi AOI */
#define IS_AOI_MULTI_MODE_AXES                0x0001    


/* Subsampling */
#define IS_SUBSAMPLING_VERT                   0x0001    
#define IS_SUBSAMPLING_HOR                    0x0002    


/* Binning */
#define IS_BINNING_VERT                       0x0001    
#define IS_BINNING_HOR                        0x0002    


/* Hotpixel correction */
#define IS_GET_BPC_MODE                       0x8000    
#define IS_GET_BPC_THRESHOLD                  0x8001    
#define IS_GET_BPC_SUPPORTED_MODE             0x8002    

#define IS_BPC_DISABLE                             0    
#define IS_BPC_ENABLE_LEVEL_1                      1    
#define IS_BPC_ENABLE_LEVEL_2                      2    
#define IS_BPC_ENABLE_USER                         4    
#define IS_BPC_ENABLE_SOFTWARE              IS_BPC_ENABLE_LEVEL_2
#define IS_BPC_ENABLE_HARDWARE              IS_BPC_ENABLE_LEVEL_1

#define IS_SET_BADPIXEL_LIST                    0x01    
#define IS_GET_BADPIXEL_LIST                    0x02    
#define IS_GET_LIST_SIZE                        0x03    


/* Display */
#define IS_GET_DISPLAY_SIZE_X                 0x8000    
#define IS_GET_DISPLAY_SIZE_Y                 0x8001    
#define IS_GET_DISPLAY_POS_X                  0x8000    
#define IS_GET_DISPLAY_POS_Y                  0x8001    

#define IS_SET_DM_DIRECTDRAW                       2    
#define IS_SET_DM_ALLOW_SYSMEM                  0x40    
#define IS_SET_DM_ALLOW_PRIMARY                 0x80    
#define IS_GET_DD_OVERLAY_SCALE               0x8000    
#define IS_SET_DM_ALLOW_OVERLAY                0x100    
#define IS_SET_DM_ALLOW_SCALING                0x200    
#define IS_SET_DM_ALLOW_FIELDSKIP              0x400    
#define IS_SET_DM_BACKBUFFER                  0x2000    


/* DirectDraw keying color constants */
#define IS_GET_KC_RED                         0x8000    
#define IS_GET_KC_GREEN                       0x8001    
#define IS_GET_KC_BLUE                        0x8002    
#define IS_GET_KC_RGB                         0x8003    
#define IS_GET_KC_INDEX                       0x8004    
#define IS_GET_KEYOFFSET_X                    0x8000    
#define IS_GET_KEYOFFSET_Y                    0x8001    


/* DirectDraw steal video constants */
#define IS_INIT_STEAL_VIDEO                        1    
#define IS_EXIT_STEAL_VIDEO                        2    
#define IS_INIT_STEAL_VIDEO_MANUAL                 3    
#define IS_INIT_STEAL_VIDEO_AUTO                   4    
#define IS_SET_STEAL_RATIO                        64    
#define IS_USE_MEM_IMAGE_SIZE                    128    
#define IS_STEAL_MODES_MASK                        7    
#define IS_SET_STEAL_COPY                     0x1000    
#define IS_SET_STEAL_NORMAL                   0x2000    


/* RGB-triple for default key-color in 15,16,24,32 bit mode */
#define IS_SET_KC_DEFAULT                   0xFF00FF    // 0xbbggrr


/* color index for default key-color in 8bit palette mode */
#define IS_SET_KC_DEFAULT_8                      253    


/* Memoryboard */
#define IS_MEMORY_GET_COUNT                   0x8000    
#define IS_MEMORY_GET_DELAY                   0x8001    
#define IS_MEMORY_MODE_DISABLE                0x0000    
#define IS_MEMORY_USE_TRIGGER                 0xFFFF    


/* Test image modes */
#define IS_GET_TEST_IMAGE                     0x8000    
#define IS_SET_TEST_IMAGE_DISABLED            0x0000    
#define IS_SET_TEST_IMAGE_MEMORY_1            0x0001    
#define IS_SET_TEST_IMAGE_MEMORY_2            0x0002    
#define IS_SET_TEST_IMAGE_MEMORY_3            0x0003    


/* Board types */
#define IS_BOARD_TYPE_FALCON                       1    
#define IS_BOARD_TYPE_EAGLE                        2    
#define IS_BOARD_TYPE_FALCON2                      3    
#define IS_BOARD_TYPE_FALCON_PLUS                  7    
#define IS_BOARD_TYPE_FALCON_QUATTRO               9    
#define IS_BOARD_TYPE_FALCON_DUO                  10    
#define IS_BOARD_TYPE_EAGLE_QUATTRO               11    
#define IS_BOARD_TYPE_EAGLE_DUO                   12    


/* AGC modes   (Falcon) */
#define IS_GET_AGC_MODE                       0x8000    
#define IS_SET_AGC_OFF                             0    
#define IS_SET_AGC_ON                              1    


/* sync levels   (Falcon) */
#define IS_GET_SYNC_LEVEL                     0x8000    
#define IS_SET_SYNC_75                             0    
#define IS_SET_SYNC_125                            1    


/* color bar modes   (Falcon) */
#define IS_GET_CBARS_MODE                     0x8000    
#define IS_SET_CBARS_OFF                           0    
#define IS_SET_CBARS_ON                            1    


/* Horizontal filter defines   (Falcon) */
#define IS_GET_HOR_FILTER_MODE                0x8000    
#define IS_GET_HOR_FILTER_STEP                0x8001    

#define IS_DISABLE_HOR_FILTER                      0    
#define IS_ENABLE_HOR_FILTER                       1    
#define IS_HOR_FILTER_STEP(_s_)             ((_s_ + 1) << 1)
#define IS_HOR_FILTER_STEP1                        2    
#define IS_HOR_FILTER_STEP2                        4    
#define IS_HOR_FILTER_STEP3                        6    


/* vertical filter defines   (Falcon) */
#define IS_GET_VERT_FILTER_MODE               0x8000    
#define IS_GET_VERT_FILTER_STEP               0x8001    

#define IS_DISABLE_VERT_FILTER                     0    
#define IS_ENABLE_VERT_FILTER                      1    
#define IS_VERT_FILTER_STEP(_s_)            ((_s_ + 1) << 1)
#define IS_VERT_FILTER_STEP1                       2    
#define IS_VERT_FILTER_STEP2                       4    
#define IS_VERT_FILTER_STEP3                       6    


/* scaler modes   (Falcon) */
#define IS_GET_SCALER_MODE                  (float) 1000
#define IS_SET_SCALER_OFF                   (float) 0
#define IS_SET_SCALER_ON                    (float) 1

#define IS_MIN_SCALE_X                      (float)   6.25
#define IS_MAX_SCALE_X                      (float) 100.00
#define IS_MIN_SCALE_Y                      (float)   6.25
#define IS_MAX_SCALE_Y                      (float) 100.00


/* video source selectors   (Falcon) */
#define IS_GET_VIDEO_IN                       0x8000    
#define IS_GET_VIDEO_PASSTHROUGH              0x8000    
#define IS_GET_VIDEO_IN_TOGGLE                0x8001    
#define IS_GET_TOGGLE_INPUT_1                 0x8000    
#define IS_GET_TOGGLE_INPUT_2                 0x8001    
#define IS_GET_TOGGLE_INPUT_3                 0x8002    
#define IS_GET_TOGGLE_INPUT_4                 0x8003    

#define IS_SET_VIDEO_IN_1                       0x00    
#define IS_SET_VIDEO_IN_2                       0x01    
#define IS_SET_VIDEO_IN_S                       0x02    
#define IS_SET_VIDEO_IN_3                       0x03    
#define IS_SET_VIDEO_IN_4                       0x04    
#define IS_SET_VIDEO_IN_1S                      0x10    
#define IS_SET_VIDEO_IN_2S                      0x11    
#define IS_SET_VIDEO_IN_3S                      0x13    
#define IS_SET_VIDEO_IN_4S                      0x14    
#define IS_SET_VIDEO_IN_EXT                     0x40    
#define IS_SET_TOGGLE_OFF                       0xFF    
#define IS_SET_VIDEO_IN_SYNC                  0x4000    


/* video crossbar selectors   (Falcon) */
#define IS_GET_CROSSBAR                       0x8000    

#define IS_CROSSBAR_1                              0    
#define IS_CROSSBAR_2                              1    
#define IS_CROSSBAR_3                              2    
#define IS_CROSSBAR_4                              3    
#define IS_CROSSBAR_5                              4    
#define IS_CROSSBAR_6                              5    
#define IS_CROSSBAR_7                              6    
#define IS_CROSSBAR_8                              7    
#define IS_CROSSBAR_9                              8    
#define IS_CROSSBAR_10                             9    
#define IS_CROSSBAR_11                            10    
#define IS_CROSSBAR_12                            11    
#define IS_CROSSBAR_13                            12    
#define IS_CROSSBAR_14                            13    
#define IS_CROSSBAR_15                            14    
#define IS_CROSSBAR_16                            15    
#define IS_SELECT_AS_INPUT                       128    


/* Video format selectors   (Falcon) */
#define IS_GET_VIDEO_MODE                     0x8000    

#define IS_SET_VM_PAL                              0    
#define IS_SET_VM_NTSC                             1    
#define IS_SET_VM_SECAM                            2    
#define IS_SET_VM_AUTO                             3    


/* Display update mode constants   (Falcon) */
#define IS_GET_UPDATE_MODE                    0x8000    
#define IS_SET_UPDATE_TIMER                        1    
#define IS_SET_UPDATE_EVENT                        2    


/* Sync generator mode constants   (Falcon) */
#define IS_GET_SYNC_GEN                       0x8000    
#define IS_SET_SYNC_GEN_OFF                        0    
#define IS_SET_SYNC_GEN_ON                         1    


/* Decimation modes   (Falcon) */
#define IS_GET_DECIMATION_MODE                0x8000    
#define IS_GET_DECIMATION_NUMBER              0x8001    

#define IS_DECIMATION_OFF                          0    
#define IS_DECIMATION_CONSECUTIVE                  1    
#define IS_DECIMATION_DISTRIBUTED                  2    


/* Hardware watchdog defines   (Falcon) */
#define IS_GET_WATCHDOG_TIME                  0x2000    
#define IS_GET_WATCHDOG_RESOLUTION            0x4000    
#define IS_GET_WATCHDOG_ENABLE                0x8000    

#define IS_WATCHDOG_MINUTES                        0    
#define IS_WATCHDOG_SECONDS                   0x8000    
#define IS_DISABLE_WATCHDOG                        0    
#define IS_ENABLE_WATCHDOG                         1    
#define IS_RETRIGGER_WATCHDOG                      2    
#define IS_ENABLE_AUTO_DEACTIVATION                4    
#define IS_DISABLE_AUTO_DEACTIVATION               8    
#define IS_WATCHDOG_RESERVED                  0x1000    


/* Vertical AOI merge mode (old define for freerun mode) */
#define IS_VERTICAL_AOI_MERGE_MODE_ON              1    


#define IS_AOI_IMAGE_SET_POS_FAST_SUPPORTED     0x0021    

/* Timestamp configuration */
#define TIMESTAMP_CONFIGURATION_PIN_GPIO0          2    
#define TIMESTAMP_CONFIGURATION_PIN_GPIO1          3    


/* LUT */
#define IS_ENABLE_CAMERA_LUT                  0x0001    
#define IS_SET_CAMERA_LUT_VALUES              0x0002    
#define IS_ENABLE_RGB_GRAYSCALE               0x0004    
#define IS_GET_CAMERA_LUT_USER                0x0008    
#define IS_GET_CAMERA_LUT_COMPLETE            0x0010    
#define IS_GET_CAMERA_LUT_SUPPORTED_CHANNELS     0x0020    

#define IS_CAMERA_LUT_64                          64    
#define IS_CAMERA_LUT_128                        128    

#define IS_CAMERA_LUT_IDENTITY            0x00000100    
#define IS_CAMERA_LUT_NEGATIV             0x00000200    
#define IS_CAMERA_LUT_GLOW1               0x00000400    
#define IS_CAMERA_LUT_GLOW2               0x00000800    
#define IS_CAMERA_LUT_ASTRO1              0x00001000    
#define IS_CAMERA_LUT_RAINBOW1            0x00002000    
#define IS_CAMERA_LUT_MAP1                0x00004000    
#define IS_CAMERA_LUT_COLD_HOT            0x00008000    
#define IS_CAMERA_LUT_SEPIC               0x00010000    
#define IS_CAMERA_LUT_ONLY_RED            0x00020000    
#define IS_CAMERA_LUT_ONLY_GREEN          0x00040000    
#define IS_CAMERA_LUT_ONLY_BLUE           0x00080000    

/* Gamma */
#define IS_GET_GAMMA                          0x8000    
#define IS_MIN_GAMMA                               1    
#define IS_MAX_GAMMA                            1000    
#define IS_DEFAULT_GAMMA                          -1    


/* Capture errors */
typedef enum _UC480_CAPTURE_ERROR
{
    IS_CAPERR_API_NO_DEST_MEM           =       0xa2 ,  
    IS_CAPERR_API_CONVERSION_FAILED     =       0xa3 ,  
    IS_CAPERR_API_IMAGE_LOCKED          =       0xa5 ,  

    IS_CAPERR_DRV_OUT_OF_BUFFERS        =       0xb2 ,  
    IS_CAPERR_DRV_DEVICE_NOT_READY      =       0xb4 ,  

    IS_CAPERR_USB_TRANSFER_FAILED       =       0xc7 ,  

    IS_CAPERR_DEV_TIMEOUT               =       0xd6 ,  

    IS_CAPERR_ETH_BUFFER_OVERRUN        =       0xe4 ,  
    IS_CAPERR_ETH_MISSED_IMAGES         =       0xe5    

} UC480_CAPTURE_ERROR;


typedef struct _UC480_CAPTURE_ERROR_INFO
{
    DWORD dwCapErrCnt_Total;
    BYTE  reserved[60];
    DWORD adwCapErrCnt_Detail[256]; // access via UC480_CAPTURE_ERROR

} UC480_CAPTURE_ERROR_INFO;


/* functions only effective on Falcon boards */
USBCAMEXP   is_SetVideoInput               (HCAM hf, INT Source);
USBCAMEXP   is_SetHue                      (HCAM hf, INT Hue);
USBCAMEXP   is_SetVideoMode                (HCAM hf, INT Mode);
USBCAMEXP   is_SetSyncLevel                (HCAM hf, INT Level);
USBCAMEXP   is_ShowColorBars               (HCAM hf, INT Mode);
USBCAMEXP   is_SetScaler                   (HCAM hf, float Scalex, float Scaley);
USBCAMEXP   is_SetHorFilter                (HCAM hf, INT Mode);
USBCAMEXP   is_SetVertFilter               (HCAM hf, INT Mode);
USBCAMEXP   is_ScaleDDOverlay              (HCAM hf, BOOL boScale);
USBCAMEXP   is_GetCurrentField             (HCAM hf, int* pField);
USBCAMEXP   is_SetVideoSize                (HCAM hf, INT xpos, INT ypos, INT xsize, INT ysize);
USBCAMEXP   is_SetKeyOffset                (HCAM hf, INT nOffsetX, INT nOffsetY);
USBCAMEXP   is_SetParentHwnd               (HCAM hf, HWND hwnd);
USBCAMEXP   is_SetUpdateMode               (HCAM hf, INT mode);
USBCAMEXP   is_OvlSurfaceOffWhileMove      (HCAM hf, BOOL boMode);
USBCAMEXP   is_GetPciSlot                  (HCAM hf, INT* pnSlot);
USBCAMEXP   is_GetIRQ                      (HCAM hf, INT* pnIRQ);
USBCAMEXP   is_SetToggleMode               (HCAM hf, int nInput1, int nInput2, int nInput3, int nInput4);
USBCAMEXP   is_SetDecimationMode           (HCAM hf, INT nMode, INT nDecimate);
USBCAMEXP   is_SetSync                     (HCAM hf, INT nSync);
USBCAMEXP   is_SetVideoCrossbar            (HCAM hf, INT In, INT Out);
USBCAMEXP   is_WatchdogTime                (HCAM hf, long lTime);
USBCAMEXP   is_Watchdog                    (HCAM hf, long lMode);
USBCAMEXP   is_SetPassthrough              (HCAM hf, INT Source);
USBCAMEXP   is_SetAGC                      (HCAM hCam, INT Mode);
USBCAMEXP   is_SetCaptureMode              (HCAM hCam, INT Mode);
USBCAMEXP   is_SetRenderMode               (HCAM hCam, INT Mode);


/* Deprecated functions */
USBCAMEXP   is_InitBoard                   (HCAM* phf, HWND hWnd);
USBCAMEXP   is_ExitBoard                   (HCAM hf);
USBCAMEXP   is_InitFalcon                  (HCAM* phf, HWND hWnd);
USBCAMEXP   is_ExitFalcon                  (HCAM hf);
USBCAMEXP   is_GetBoardType                (HCAM hf);
USBCAMEXP   is_GetBoardInfo                (HCAM hf, PBOARDINFO pInfo);
USBCAMEXPUL is_BoardStatus                 (HCAM hf, INT nInfo, ULONG ulValue);
USBCAMEXP   is_GetNumberOfBoards           (INT* pnNumBoards);
USBCAMEXP   is_SetBrightness               (HCAM hf, INT Bright);
USBCAMEXP   is_SetContrast                 (HCAM hf, INT Cont);
USBCAMEXP   is_GetDC                       (HCAM hf, HDC* phDC);
USBCAMEXP   is_ReleaseDC                   (HCAM hf, HDC hDC);

USBCAMEXP   is_UpdateDisplay               (HCAM hf);
USBCAMEXP   is_SetDisplaySize              (HCAM hf, INT x, INT y);

USBCAMEXP   is_LockDDOverlayMem            (HCAM hf, VOID** ppMem, INT* pPitch);
USBCAMEXP   is_UnlockDDOverlayMem          (HCAM hf);
USBCAMEXP   is_LockDDMem                   (HCAM hf, VOID** ppMem, INT* pPitch);
USBCAMEXP   is_UnlockDDMem                 (HCAM hf);
USBCAMEXP   is_GetDDOvlSurface             (HCAM hf, void** ppDDSurf);
USBCAMEXP   is_SetKeyColor                 (HCAM hf, INT r, INT g, INT b);
USBCAMEXP   is_StealVideo                  (HCAM hf, int Wait);

USBCAMEXP   is_SetDDUpdateTime             (HCAM hf, INT ms);
USBCAMEXP   is_EnableDDOverlay             (HCAM hf);
USBCAMEXP   is_DisableDDOverlay            (HCAM hf);
USBCAMEXP   is_ShowDDOverlay               (HCAM hf);
USBCAMEXP   is_HideDDOverlay               (HCAM hf);

USBCAMEXP   is_GetExposureRange            (HCAM hf, double *min, double *max, double *intervall);
USBCAMEXP   is_SetExposureTime             (HCAM hf, double EXP, double* newEXP);

USBCAMEXP   is_SetBadPixelCorrection       (HCAM hf, INT nEnable, INT threshold);
USBCAMEXP   is_LoadBadPixelCorrectionTable (HCAM hf, const IS_CHAR *File);
USBCAMEXP   is_SaveBadPixelCorrectionTable (HCAM hf, const IS_CHAR *File);
USBCAMEXP   is_SetBadPixelCorrectionTable  (HCAM hf, INT nMode, WORD *pList);

USBCAMEXP   is_SetMemoryMode               (HCAM hf, INT nCount, INT nDelay);
USBCAMEXP   is_TransferImage               (HCAM hf, INT nMemID, INT seqID, INT imageNr, INT reserved);
USBCAMEXP   is_TransferMemorySequence      (HCAM hf, INT seqID, INT StartNr, INT nCount, INT nSeqPos);
USBCAMEXP   is_MemoryFreezeVideo           (HCAM hf, INT nMemID, INT Wait);
USBCAMEXP   is_GetLastMemorySequence       (HCAM hf, INT *pID);
USBCAMEXP   is_GetNumberOfMemoryImages     (HCAM hf, INT nID, INT *pnCount);
USBCAMEXP   is_GetMemorySequenceWindow     (HCAM hf, INT nID, INT *left, INT *top, INT *right, INT *bottom);
USBCAMEXP   is_IsMemoryBoardConnected      (HCAM hf, BOOL *pConnected);
USBCAMEXP   is_ResetMemory                 (HCAM hf, INT nReserved);
USBCAMEXP   is_SetTestImage                (HCAM hf, INT nMode);

USBCAMEXP   is_GetCaptureErrorInfo         (HCAM hf, UC480_CAPTURE_ERROR_INFO *pCaptureErrorInfo, UINT SizeCaptureErrorInfo);
USBCAMEXP   is_ResetCaptureErrorInfo       (HCAM hf );

USBCAMEXP   is_SetAutoCfgIpSetup           (INT iAdapterID, const UC480_ETH_AUTOCFG_IP_SETUP* pSetup, UINT uStructSize);
USBCAMEXP   is_SetPersistentIpCfg          (HCAM hf, UC480_ETH_IP_CONFIGURATION* pIpCfg, UINT uStructSize);

USBCAMEXP   is_ConvertImage                (HCAM hf, char* pcSource, int nIDSource, char** pcDest, INT *nIDDest, INT *reserved);
USBCAMEXP   is_SetConvertParam             (HCAM hf, BOOL ColorCorrection, INT BayerConversionMode, INT ColorMode, INT Gamma, double* WhiteBalanceMultipliers);

USBCAMEXP   is_SetEdgeEnhancement          (HCAM hf, INT nEnable);

USBCAMEXP   is_SetBlCompensation           (HCAM hCam, INT nEnable, INT offset, INT reserved);

USBCAMEXP   is_LoadParameters              (HCAM hf, const IS_CHAR* pFilename);
USBCAMEXP   is_SaveParameters              (HCAM hf, const IS_CHAR* pFilename);

USBCAMEXP   is_GetPixelClockRange          (HCAM hf, INT *pnMin, INT *pnMax);
USBCAMEXP   is_SetPixelClock               (HCAM hf, INT Clock);

USBCAMEXP   is_GetOsVersion                (void);

// Image AOI functions
USBCAMEXP   is_SetImageSize                (HCAM hf, INT x, INT y);
USBCAMEXP   is_SetImagePos                 (HCAM hf, INT x, INT y);
USBCAMEXP   is_SetAOI                      (HCAM hf, INT cmd, INT *pXPos, INT *pYPos, INT *pWidth, INT *pHeight);
USBCAMEXP   is_SetImageAOI                 (HCAM hf, INT xPos, INT yPos, INT width, INT height);

// IO functions
USBCAMEXP   is_SetIO                       (HCAM hf, INT nIO);
USBCAMEXP   is_SetIOMask                   (HCAM hf, INT nMask);
USBCAMEXP   is_SetLED                      (HCAM hf, INT nValue);
USBCAMEXP   is_GetGlobalFlashDelays        (HCAM hf, ULONG *pulDelay, ULONG *pulDuration);
USBCAMEXP   is_SetFlashDelay               (HCAM hf, ULONG ulDelay, ULONG ulDuration);
USBCAMEXP   is_SetFlashStrobe              (HCAM hf, INT nMode, INT nLine);

// GigE functions
USBCAMEXP   is_GetEthDeviceInfo            (HCAM hf, UC480_ETH_DEVICE_INFO* pDeviceInfo, UINT uStructSize);

// Image load / save functions
USBCAMEXP   is_LoadImage                   (HCAM hf, const IS_CHAR* File);
USBCAMEXP   is_LoadImageMem                (HCAM hf, const IS_CHAR* File, char** ppcImgMem, INT* pid);
USBCAMEXP   is_SaveImage                   (HCAM hf, const IS_CHAR* File);
USBCAMEXP   is_SaveImageMem                (HCAM hf, const IS_CHAR* File, char* pcMem, int nID);
USBCAMEXP   is_SaveImageEx                 (HCAM hf, const IS_CHAR* File, INT fileFormat, INT Param);
USBCAMEXP   is_SaveImageMemEx              (HCAM hf, const IS_CHAR* File, char* pcMem, INT nID, INT FileFormat, INT Param);

// LUT functions
USBCAMEXP   is_SetCameraLUT                (HCAM hCam, UINT Mode, UINT NumberOfEntries, double *pRed_Grey, double *pGreen, double *pBlue);
USBCAMEXP   is_GetCameraLUT                (HCAM hCam, UINT Mode, UINT NumberOfEntries, double *pRed_Grey, double *pGreen, double *pBlue);

// Gamma
USBCAMEXP   is_SetGamma                    (HCAM hCam, INT nGamma);


#ifdef __cplusplus
};
#endif  /* __cplusplus */

#pragma pack(pop)

#endif  // #ifndef __UC480_HEADER_DEPRECATED__
