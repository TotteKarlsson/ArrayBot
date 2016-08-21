#ifndef abDirectSoundH
#define abDirectSoundH
#include "abABObject.h"

#include <windows.h>
#include <Mmreg.h>
#include <dsound.h>

class AB_CORE CDirectSound : public ABObject
{
    public:		// construction/destruction
							        CDirectSound();
        virtual 					~CDirectSound();

    	// If the "pWnd" paramter is NULL, then AfxGetApp()->GetMainWnd() will be used.
        bool						Create(LPCTSTR pszResource);
        bool						Create(UINT uResourceID);

        // Alternativly you can specify the sound by yourself
        // Note that the class does not copy the entire data ! Instead
        // a pointer to the given data will be stored !
        // You can load an entire WAV file into memory and then call this
        // Create() method.
        bool						Create(LPVOID pSoundData);//, CWnd * pWnd = 0);

    public:		// operations
        bool			            IsValid() const;
        void			            Play(DWORD dwStartPosition = 0, bool bLoop = FALSE);
        void			            Stop();
        void			            Pause();
        void			            Continue();
        CDirectSound &	            EnableSound(bool bEnable = TRUE);
        bool						IsEnabled() const { return m_bEnabled; }

    protected:	// implementation
        bool                        SetSoundData(LPVOID pSoundData, DWORD dwSoundSize);
        bool                        CreateSoundBuffer(WAVEFORMATEX * pcmwf);
        bool                        GetWaveData(void * pRes, WAVEFORMATEX * & pWaveHeader, void * & pbWaveData, DWORD & cbWaveSize);

    private:	// data member
        LPVOID 						m_pTheSound;
        DWORD 						m_dwTheSound;
        LPDIRECTSOUNDBUFFER 		m_pDsb;
        bool 						m_bEnabled;
        static LPDIRECTSOUND 		m_lpDirectSound;
        static DWORD 				m_dwInstances;
};

#pragma message("linking with Microsoft's DirectSound library ...")
#pragma comment(lib, "dsound.lib")

#endif
