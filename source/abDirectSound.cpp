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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LPDIRECTSOUND DirectSound::m_lpDirectSound;
DWORD DirectSound::m_dwInstances;

static void DSError(HRESULT hRes);
DirectSound::DirectSound()
{
	m_lpDirectSound = 0;
	m_pDsb = 0;
	m_pTheSound = 0;
	m_dwTheSound = 0;
	m_bEnabled = true;

	++m_dwInstances;
}

DirectSound::~DirectSound()
{
	if( m_pDsb )
    {
		m_pDsb->Release();
    }

	if( !--m_dwInstances && m_lpDirectSound )
    {
		m_lpDirectSound->Release();
		m_lpDirectSound = 0;
	}
}

bool DirectSound::Create(UINT uResourceID)//, CWnd * pWnd = 0)
{
	return Create(MAKEINTRESOURCE(uResourceID));
}

DirectSound& DirectSound::EnableSound(bool bEnable)
{
	m_bEnabled = bEnable;

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

	return Create(pTheSound, hWnd);
}

bool DirectSound::Create(LPVOID pSoundData, HWND hWnd)
{
	//////////////////////////////////////////////////////////////////
	// create direct sound object
	if( m_lpDirectSound == 0 )
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
			hRes = ::DirectSoundCreate(0, &m_lpDirectSound, 0);
			++nRes;

		}while( nRes < 10 && (hRes == DSERR_ALLOCATED || hRes == DSERR_NODRIVER) );

		if(hRes != DS_OK)
        {
			return false;
        }

        if(!hWnd)
        {
			hWnd = ::GetConsoleWindow();
        }

		m_lpDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	}

	WAVEFORMATEX * pcmwf;
	if( !GetWaveData(pSoundData, pcmwf, m_pTheSound, m_dwTheSound) ||
		!CreateSoundBuffer(pcmwf) ||
		!SetSoundData(m_pTheSound, m_dwTheSound) )
	{
		return false;
    }

	return true;
}

bool DirectSound::GetWaveData(void * pRes, WAVEFORMATEX * & pWaveHeader, void * & pbWaveData, DWORD & cbWaveSize)
{
	pWaveHeader = 0;
	pbWaveData = 0;
	cbWaveSize = 0;

	DWORD * pdw = (DWORD *)pRes;
	DWORD dwRiff = *pdw++;
	DWORD dwLength = *pdw++;
	DWORD dwType = *pdw++;

	if( dwRiff != mmioFOURCC('R', 'I', 'F', 'F') )
		return false;      // not even RIFF

	if( dwType != mmioFOURCC('W', 'A', 'V', 'E') )
		return false;      // not a WAV

	DWORD * pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);

	while( pdw < pdwEnd ) {
		dwType = *pdw++;
		dwLength = *pdw++;

		switch( dwType ) {
			case mmioFOURCC('f', 'm', 't', ' '):
				if( !pWaveHeader ) {
					if( dwLength < sizeof(WAVEFORMAT) )
						return false;      // not a WAV

					pWaveHeader = (WAVEFORMATEX *)pdw;

					if( pbWaveData && cbWaveSize )
						return true;
				}
				break;

			case mmioFOURCC('d', 'a', 't', 'a'):
				pbWaveData = LPVOID(pdw);
				cbWaveSize = dwLength;

				if( pWaveHeader )
					return true;
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
	dsbdesc.dwFlags = DSBCAPS_STATIC;		// assumes that the sound is played often
	dsbdesc.dwBufferBytes = m_dwTheSound;
	dsbdesc.lpwfxFormat = pcmwf;    // Create buffer.
	HRESULT hRes;
	if(DS_OK != (hRes = m_lpDirectSound->CreateSoundBuffer(&dsbdesc, &m_pDsb, 0)))
    {
		// Failed.
		DSError(hRes);
		m_pDsb = 0;
		return false;
	}

	return true;
}

bool DirectSound::SetSoundData(void * pSoundData, DWORD dwSoundSize)
{
	LPVOID lpvPtr1;
	DWORD dwBytes1;
	// Obtain write pointer.
	HRESULT hr = m_pDsb->Lock(0, 0, &lpvPtr1, &dwBytes1, 0, 0, DSBLOCK_ENTIREBUFFER);

    // If DSERR_BUFFERLOST is returned, restore and retry lock.
	if(DSERR_BUFFERLOST == hr)
    {
		m_pDsb->Restore();
		hr = m_pDsb->Lock(0, 0, &lpvPtr1, &dwBytes1, 0, 0, DSBLOCK_ENTIREBUFFER);
	}

	if(DS_OK == hr)
    {
		// Write to pointers.
		::CopyMemory(lpvPtr1, pSoundData, dwBytes1);
		// Release the data back to DirectSound.
		hr = m_pDsb->Unlock(lpvPtr1, dwBytes1, 0, 0);
		if(DS_OK == hr)
        {
            return true;
        }
	}

	// Lock, Unlock, or Restore failed.
	return false;
}

void DirectSound::Play(DWORD dwStartPosition, bool bLoop)
{
	if(!IsValid() || ! IsEnabled())
    {
		return;		// no chance to play the sound ...
    }

	if(dwStartPosition > m_dwTheSound)
    {
    	dwStartPosition = m_dwTheSound;
    }

	m_pDsb->SetCurrentPosition(dwStartPosition);

	if( DSERR_BUFFERLOST == m_pDsb->Play(0, 0, bLoop ? DSBPLAY_LOOPING : 0) )
    {
		// another application had stolen our buffer
		// Note that a "Restore()" is not enough, because
		// the sound data is invalid after Restore().
		SetSoundData(m_pTheSound, m_dwTheSound);

		// Try playing again
		m_pDsb->Play(0, 0, bLoop ? DSBPLAY_LOOPING : 0);
	}
}

void DirectSound::Stop()
{
	if( IsValid() )
    {
		m_pDsb->Stop();
    }
}

void DirectSound::Pause()
{
	Stop();
}

void DirectSound::Continue()
{
	if(IsValid())
    {
		DWORD dwPlayCursor, dwWriteCursor;
		m_pDsb->GetCurrentPosition(&dwPlayCursor, &dwWriteCursor);
		Play(dwPlayCursor);
	}
}

bool DirectSound::IsValid() const
{
	return (m_lpDirectSound && m_pDsb && m_pTheSound && m_dwTheSound) ? true : false;
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


