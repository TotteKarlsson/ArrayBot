#ifndef abDirectSoundH
#define abDirectSoundH
#include "abABObject.h"

#include <windows.h>
#include <mmreg.h>
#include <dsound.h>

class AB_CORE DirectSound : public ABObject
{
    public:
							        DirectSound();
        virtual 					~DirectSound();

    								// If the "pWnd" paramter is NULL, then AfxGetApp()->GetMainWnd() will be used.
        bool						Create(const string& pszResource, HWND hWnd = NULL);
        bool						Create(UINT uResourceID);

                                    // Alternativly you can specify the sound by yourself
                                    // Note that the class does not copy the entire data ! Instead
                                    // a pointer to the given data will be stored !
                                    // You can load an entire WAV file into memory and then call this
                                    // Create() method.
        bool						Create(LPVOID pSoundData, HWND hWnd =  NULL);//, CWnd * pWnd = 0);

        bool			            IsValid() const;
        bool			            Play(DWORD dwStartPosition = 0, bool bLoop = FALSE);
        bool			            Stop();
        bool			            Pause();
        bool			            Continue();
        DirectSound &	            EnableSound(bool bEnable = true);
        bool						IsEnabled() const {return mEnabled;}

    protected:
        bool                        SetSoundData(LPVOID pSoundData, DWORD dwSoundSize);
        bool                        CreateSoundBuffer(WAVEFORMATEX * pcmwf);
        bool                        GetWaveData(void * pRes, WAVEFORMATEX * & pWaveHeader, void * & pbWaveData, DWORD & cbWaveSize);

    private:
        LPVOID 						mTheSound;
        DWORD 						mTheSoundBytes;
        LPDIRECTSOUNDBUFFER 		mDirectSoundBuffer;
        bool 						mEnabled;
        LPDIRECTSOUND 				mDirectSoundStructure;
        static DWORD 				mNrOfInstances;
};

#pragma message("linking with Microsoft's DirectSound library ...")
#pragma comment(lib, "dsound.lib")

#endif
