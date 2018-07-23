#pragma hdrstop
#include "dslWin32Utils.h"
#include "atDirectSound.h"
#include <mmsystem.h>
#include "dslLogger.h"

using namespace dsl;

DWORD DirectSound::mNrOfInstances;

static void DSError(HRESULT hRes);

DirectSound::DirectSound(const string& resName, HWND hWnd)
:
mTheSound(NULL),
mTheSoundBytes(0),
mResourceName(resName),
mHandle(hWnd),
mDirectSoundBuffer(NULL),
mDirectSoundStructure(NULL)
{
    if(mResourceName.size())
    {
    	create(mResourceName);
    }
	++mNrOfInstances;
}

DirectSound::~DirectSound()
{
	if(mDirectSoundBuffer)
    {
		mDirectSoundBuffer->Release();
    }

	if( !--mNrOfInstances && mDirectSoundStructure )
    {
		mDirectSoundStructure->Release();
		mDirectSoundStructure = NULL;
	}
}

void DirectSound::setName(const string& n)
{
    if(n == mResourceName)
    {
    	return;
    }

	mResourceName = n;
    if(mHandle)
    {
    	create(mResourceName, mHandle);
    }
}

void DirectSound::setVolume(int volume)
{
	if(mDirectSoundBuffer)
    {
    	mDirectSoundBuffer->SetVolume(volume);
    }
}

void DirectSound::setHandle(HWND h)
{
	create(mResourceName, h);
}

HWND DirectSound::getHandle() const
{
	return mHandle;
}

string DirectSound::getName() const
{
	return mResourceName;
}

string DirectSound::getResourceName() const
{
	return mResourceName;
}


bool DirectSound::play(DWORD dwStartPosition, bool loop)
{
	if(!isValid())
    {
		return false;		// no chance to play the sound ...
    }

	if(dwStartPosition > mTheSoundBytes)
    {
    	dwStartPosition = mTheSoundBytes;
    }

	mDirectSoundBuffer->SetCurrentPosition(dwStartPosition);

	if(DSERR_BUFFERLOST == mDirectSoundBuffer->Play(0, 0, loop ? DSBPLAY_LOOPING : 0) )
    {
		// another application had stolen our buffer
		// Note that a "Restore()" is not enough, because
		// the sound data is invalid after Restore().
		setSoundData(mTheSound, mTheSoundBytes);

		// Try playing again
		mDirectSoundBuffer->Play(0, 0, loop ? DSBPLAY_LOOPING : 0);
        return true;
	}
    return true;
}

bool DirectSound::stop()
{
	if( isValid() )
    {
		mDirectSoundBuffer->Stop();
        return true;
    }
	return false;
}

bool DirectSound::pause()
{
	return stop();
}

bool DirectSound::create(const string& resName, HWND hWnd)
{
	mHandle = hWnd;

	// load resource
	HINSTANCE modHandle = ::GetModuleHandle("atResources.dll");
	HRSRC hResInfo 		= ::FindResourceA(modHandle, resName.c_str(), RT_RCDATA);

	if(hResInfo == 0)
    {
    	Log(lError) << "Failed to find resource: "<<resName<<" in resource DLL";
		return false;
    }

	HGLOBAL hRes = ::LoadResource(modHandle, hResInfo);
	if(hRes == 0)
    {
		return false;
    }

	LPVOID pTheSound = ::LockResource(hRes);
	if(pTheSound == 0)
    {
		return false;
    }

    if(!create(pTheSound, hWnd))
    {
    	return false;
    }

	return true;
}

bool DirectSound::create(LPVOID pSoundData, HWND hWnd)
{
	//////////////////////////////////////////////////////////////////
	// create direct sound object
	if(mDirectSoundStructure == 0)
    {
		if(::DirectSoundCreate(0, &mDirectSoundStructure, 0) != DS_OK)
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
	if(!getWaveData(pSoundData, pcmwf, mTheSound, mTheSoundBytes))
	{
    	string error = getLastWin32Error();
        Log(lError) << "Last win32 error: "<<error;
   		return false;
    }

    if(!createSoundBuffer(pcmwf))
    {
    	string error = getLastWin32Error();
        Log(lError) << "Last win32 error: "<<error;
		return false;
    }

    if(!setSoundData(mTheSound, mTheSoundBytes) )
	{
    	string error = getLastWin32Error();
        Log(lError) << "Last win32 error: "<<error;
		return false;
    }

	return true;
}

bool DirectSound::getWaveData(void* pRes, WAVEFORMATEX* &pWaveHeader, void* &pbWaveData, DWORD &cbWaveSize)
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

bool DirectSound::createSoundBuffer(WAVEFORMATEX * pcmwf)
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

bool DirectSound::setSoundData(void* pSoundData, DWORD dwSoundSize)
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

	return false;
}

bool DirectSound::continuePlay()
{
	if(isValid())
    {
		DWORD dwPlayCursor, dwWriteCursor;
		mDirectSoundBuffer->GetCurrentPosition(&dwPlayCursor, &dwWriteCursor);
		return play(dwPlayCursor);
	}
    return false;
}

bool DirectSound::isValid() const
{
	return (mDirectSoundStructure && mDirectSoundBuffer && mTheSound && mTheSoundBytes) ? true : false;
}

static void DSError(HRESULT hRes)
{
	switch(hRes)
    {
		case DS_OK: 					Log(lError) << "NO ERROR"; 			       	    break;
		case DSERR_ALLOCATED: 			Log(lError) << "ALLOCATED"; 		            break;
		case DSERR_INVALIDPARAM: 		Log(lError) << "INVALIDPARAM"; 		            break;
		case DSERR_OUTOFMEMORY: 		Log(lError) << "OUTOFMEMORY"; 		            break;
		case DSERR_UNSUPPORTED: 		Log(lError) << "UNSUPPORTED"; 		            break;
		case DSERR_NOAGGREGATION: 		Log(lError) << "NOAGGREGATION"; 	            break;
		case DSERR_UNINITIALIZED: 		Log(lError) << "UNINITIALIZED"; 	            break;
		case DSERR_BADFORMAT: 			Log(lError) << "BADFORMAT"; 		            break;
		case DSERR_ALREADYINITIALIZED: 	Log(lError) << "ALREADYINITIALIZED";            break;
		case DSERR_BUFFERLOST: 			Log(lError) << "BUFFERLOST"; 		            break;
		case DSERR_CONTROLUNAVAIL: 		Log(lError) << "CONTROLUNAVAIL"; 	            break;
		case DSERR_GENERIC: 			Log(lError) << "GENERIC"; 			            break;
		case DSERR_INVALIDCALL: 		Log(lError) << "INVALIDCALL"; 		            break;
		case DSERR_OTHERAPPHASPRIO: 	Log(lError) << "OTHERAPPHASPRIO"; 	            break;
		case DSERR_PRIOLEVELNEEDED: 	Log(lError) << "PRIOLEVELNEEDED"; 	            break;
		default: 						Log(lError) << "Direct Sound error: "<<hRes;    break;
	}
}

