#pragma hdrstop
#include "abDirectSound.h"
#include <mmsystem.h>
#include "mtkLogger.h"

using namespace mtk;

// The following macro is defined since DirectX 5, but will work with
// older versions too.
#ifndef DSBLOCK_ENTIREBUFFER
	#define DSBLOCK_ENTIREBUFFER        0x00000002
#endif

//LPDIRECTSOUND DirectSound::mDirectSoundStructure;
DWORD DirectSound::mNrOfInstances;

static void DSError(HRESULT hRes);

DirectSound::DirectSound()
:
mDirectSoundBuffer(0),
mTheSound(0),
mTheSoundBytes(0),
mEnabled(true)
{
	mDirectSoundStructure = 0;
	++mNrOfInstances;
}

DirectSound::~DirectSound()
{
	if( mDirectSoundBuffer )
    {
		mDirectSoundBuffer->Release();
    }

	if( !--mNrOfInstances && mDirectSoundStructure )
    {
		mDirectSoundStructure->Release();
		mDirectSoundStructure = 0;
	}
}

bool DirectSound::Create(UINT uResourceID)//, CWnd * pWnd = 0)
{
	return Create(MAKEINTRESOURCE(uResourceID));
}

DirectSound& DirectSound::EnableSound(bool bEnable)
{
	mEnabled = bEnable;

	if(!bEnable)
    {
		Stop();
    }

	return *this;
}

bool DirectSound::Create(const string& pszResource, HWND hWnd)
{
	//////////////////////////////////////////////////////////////////
	// load resource
	HINSTANCE hResourceDLL = ::GetModuleHandle("abResources.dll");

	HRSRC hResInfo = ::FindResourceA(hResourceDLL, pszResource.c_str(), MAKEINTRESOURCE(10));
	if(hResInfo == 0)
    {
		return false;
    }

	HGLOBAL hRes = ::LoadResource(hResourceDLL, hResInfo);
	if(hRes == 0)
    {
		return false;
    }

	LPVOID pTheSound = ::LockResource(hRes);
	if(pTheSound == 0)
    {
		return false;
    }

    if(!Create(pTheSound, hWnd))
    {
    	return false;
    }

	return true;
}

bool DirectSound::Create(LPVOID pSoundData, HWND hWnd)
{
	//////////////////////////////////////////////////////////////////
	// create direct sound object
	if(mDirectSoundStructure == 0)
    {
		// Someone might use sounds for starting apps. This may cause
		// DirectSoundCreate() to fail because the driver is used by
		// anyone else. So wait a little before starting with the work ...
		HRESULT hRes = DS_OK;
		short nRes = 0;

		do
        {
        	if(nRes)
            {
				::Sleep(500);
            }
			hRes = ::DirectSoundCreate(0, &mDirectSoundStructure, 0);
			++nRes;

		}
        while( nRes < 10 && (hRes == DSERR_ALLOCATED || hRes == DSERR_NODRIVER) );

		if(hRes != DS_OK)
        {
			return false;
        }

        if(!hWnd)
        {
			hWnd = ::GetConsoleWindow();
        }

		mDirectSoundStructure->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	}

	WAVEFORMATEX * pcmwf;
	if(!GetWaveData(pSoundData, pcmwf, mTheSound, mTheSoundBytes))
	{
    	string error = getLastWin32Error();
        Log(lError) << "Last win32 error: "<<error;
   		return false;
    }

    if(!CreateSoundBuffer(pcmwf))
    {
    	string error = getLastWin32Error();
        Log(lError) << "Last win32 error: "<<error;
		return false;
    }

    if(!SetSoundData(mTheSound, mTheSoundBytes) )
	{
    	string error = getLastWin32Error();
        Log(lError) << "Last win32 error: "<<error;
		return false;
    }

	return true;
}

bool DirectSound::GetWaveData(void* pRes, WAVEFORMATEX* &pWaveHeader, void* &pbWaveData, DWORD &cbWaveSize)
{
	pWaveHeader = 0;
	pbWaveData = 0;
	cbWaveSize = 0;

	DWORD *pdw 		= (DWORD *)pRes;
	DWORD dwRiff 	= *pdw++;
	DWORD dwLength 	= *pdw++;
	DWORD dwType 	= *pdw++;

	if(dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
    {
		return false;      // not even RIFF
    }

	if(dwType != mmioFOURCC('W', 'A', 'V', 'E'))
    {
		return false;      // not a WAV
    }

	DWORD* pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);

	while(pdw < pdwEnd)
    {
		dwType = *pdw++;
		dwLength = *pdw++;

		switch(dwType)
        {
			case mmioFOURCC('f', 'm', 't', ' '):
				if(!pWaveHeader)
                {
					if( dwLength < sizeof(WAVEFORMAT) )
                    {
                    	return false;      // not a WAV
                    }

					pWaveHeader = (WAVEFORMATEX *)pdw;

					if( pbWaveData && cbWaveSize )
                    {
						return true;
                    }
				}
				break;

			case mmioFOURCC('d', 'a', 't', 'a'):
				pbWaveData = LPVOID(pdw);
				cbWaveSize = dwLength;

				if(pWaveHeader)
                {
					return true;
                }
				break;
		}
		pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
	}

	return false;
}

bool DirectSound::CreateSoundBuffer(WAVEFORMATEX * pcmwf)
{
	DSBUFFERDESC dsbdesc;

	// Set up DSBUFFERDESC structure.
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); // Zero it out.
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	// Need no controls (pan, volume, frequency).
	dsbdesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME;
	dsbdesc.dwBufferBytes = mTheSoundBytes;
	dsbdesc.lpwfxFormat = pcmwf;    // Create buffer.
	HRESULT hRes;
	if(DS_OK != (hRes = mDirectSoundStructure->CreateSoundBuffer(&dsbdesc, &mDirectSoundBuffer, 0)))
    {
		// Failed.
		DSError(hRes);
		mDirectSoundBuffer = 0;
		return false;
	}

	return true;
}

bool DirectSound::SetSoundData(void * pSoundData, DWORD dwSoundSize)
{
	LPVOID lpvPtr1;
	DWORD dwBytes1;
	// Obtain write pointer.
	HRESULT hr = mDirectSoundBuffer->Lock(0, 0, &lpvPtr1, &dwBytes1, 0, 0, DSBLOCK_ENTIREBUFFER);

    // If DSERR_BUFFERLOST is returned, restore and retry lock.
	if(DSERR_BUFFERLOST == hr)
    {
		mDirectSoundBuffer->Restore();
		hr = mDirectSoundBuffer->Lock(0, 0, &lpvPtr1, &dwBytes1, 0, 0, DSBLOCK_ENTIREBUFFER);
	}

	if(DS_OK == hr)
    {
		// Write to pointers.
		::CopyMemory(lpvPtr1, pSoundData, dwBytes1);
		// Release the data back to DirectSound.
		hr = mDirectSoundBuffer->Unlock(lpvPtr1, dwBytes1, 0, 0);
		if(DS_OK == hr)
        {
            return true;
        }
	}

	// Lock, Unlock, or Restore failed.
	return false;
}

bool DirectSound::Play(DWORD dwStartPosition, bool loop)
{
	if(!IsValid() || ! IsEnabled())
    {
		return false;		// no chance to play the sound ...
    }

	if(dwStartPosition > mTheSoundBytes)
    {
    	dwStartPosition = mTheSoundBytes;
    }

	mDirectSoundBuffer->SetCurrentPosition(dwStartPosition);

	if( DSERR_BUFFERLOST == mDirectSoundBuffer->Play(0, 0, loop ? DSBPLAY_LOOPING : 0) )
    {
		// another application had stolen our buffer
		// Note that a "Restore()" is not enough, because
		// the sound data is invalid after Restore().
		SetSoundData(mTheSound, mTheSoundBytes);

		// Try playing again
		mDirectSoundBuffer->Play(0, 0, loop ? DSBPLAY_LOOPING : 0);
        return true;
	}
    return true;
}

bool DirectSound::Stop()
{
	if( IsValid() )
    {
		mDirectSoundBuffer->Stop();
        return true;
    }
	return false;
}

bool DirectSound::Pause()
{
	return Stop();
}

bool DirectSound::Continue()
{
	if(IsValid())
    {
		DWORD dwPlayCursor, dwWriteCursor;
		mDirectSoundBuffer->GetCurrentPosition(&dwPlayCursor, &dwWriteCursor);
		return Play(dwPlayCursor);
	}
    return false;
}

bool DirectSound::IsValid() const
{
	return (mDirectSoundStructure && mDirectSoundBuffer && mTheSound && mTheSoundBytes) ? true : false;
}

static void DSError(HRESULT hRes)
{
	switch(hRes)
    {
		case DS_OK: 					Log(lError) << ("NO ERROR\n"); 			        break;
		case DSERR_ALLOCATED: 			Log(lError) << ("ALLOCATED\n"); 		        break;
		case DSERR_INVALIDPARAM: 		Log(lError) << ("INVALIDPARAM\n"); 		        break;
		case DSERR_OUTOFMEMORY: 		Log(lError) << ("OUTOFMEMORY\n"); 		        break;
		case DSERR_UNSUPPORTED: 		Log(lError) << ("UNSUPPORTED\n"); 		        break;
		case DSERR_NOAGGREGATION: 		Log(lError) << ("NOAGGREGATION\n"); 	        break;
		case DSERR_UNINITIALIZED: 		Log(lError) << ("UNINITIALIZED\n"); 	        break;
		case DSERR_BADFORMAT: 			Log(lError) << ("BADFORMAT\n"); 		        break;
		case DSERR_ALREADYINITIALIZED: 	Log(lError) << ("ALREADYINITIALIZED\n");        break;
		case DSERR_BUFFERLOST: 			Log(lError) << ("BUFFERLOST\n"); 		        break;
		case DSERR_CONTROLUNAVAIL: 		Log(lError) << ("CONTROLUNAVAIL\n"); 	        break;
		case DSERR_GENERIC: 			Log(lError) << ("GENERIC\n"); 			        break;
		case DSERR_INVALIDCALL: 		Log(lError) << ("INVALIDCALL\n"); 		        break;
		case DSERR_OTHERAPPHASPRIO: 	Log(lError) << ("OTHERAPPHASPRIO\n"); 	        break;
		case DSERR_PRIOLEVELNEEDED: 	Log(lError) << ("PRIOLEVELNEEDED\n"); 	        break;
		default: 						Log(lError) << "Direct Sound error: "<<hRes;    break;
	}
}


