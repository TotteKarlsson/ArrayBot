#ifndef atDirectSoundH
#define atDirectSoundH
#include "atATObject.h"
#include "atSoundExporter.h"
#include <windows.h>
#include <mmreg.h>
#include <dsound.h>

class AT_SOUND DirectSound //: public ATObject
{
    public:
							                        DirectSound(const string& resName, HWND hWnd = NULL);
        virtual 					                ~DirectSound();
        bool						                create(const string& resName, HWND hWnd = NULL);

        bool			                            isValid() const;
		virtual void	 			                setVolume(int volume);
        void						                setHandle(HWND h);
        HWND						                getHandle() const;

		void						                setName(const string& n);
        string						                getName() const;
        string						                getResourceName() const;

        virtual bool   	                            play(DWORD dwStartPosition = 0, bool bLoop = FALSE);
        bool			                            stop();
        bool			                            pause();
        bool			                            continuePlay();

    protected:
        bool						                create(LPVOID pSoundData, HWND hWnd =  NULL);
        bool                                        setSoundData(LPVOID pSoundData, DWORD dwSoundSize);
        bool                                        createSoundBuffer(WAVEFORMATEX * pcmwf);
        bool                                        getWaveData(void * pRes, WAVEFORMATEX * & pWaveHeader, void * & pbWaveData, DWORD & cbWaveSize);

    private:
        static DWORD 				                mNrOfInstances;
    	HWND						                mHandle;
        LPVOID 						                mTheSound;
        DWORD 						                mTheSoundBytes;
        LPDIRECTSOUNDBUFFER 		                mDirectSoundBuffer;
        LPDIRECTSOUND 				                mDirectSoundStructure;
        string						                mResourceName;
};

#pragma message("Linking with Microsoft's DirectSound library ...")
#pragma comment(lib, "dsound.lib")
#endif
