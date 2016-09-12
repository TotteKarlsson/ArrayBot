#pragma hdrstop
#include "abSoundPlayer.h"
#include "Poco/Timespan.h"
//---------------------------------------------------------------------------
using Poco::Timespan;

SoundPlayer::SoundPlayer(const string& snd, int nrOfTimes, int delay)
:
mSoundResourceName(snd),
mNrOfReps(nrOfTimes),
mDelay(delay)
{
	mPlayingTimer.OnTimerC = onTimer;
    mPlayingTimer.setInterval(mDelay* Timespan::MILLISECONDS);
}

SoundPlayer::~SoundPlayer()
{}

bool SoundPlayer::create(HWND hWnd)
{
	return mTheSound.Create(mSoundResourceName, hWnd);
}

bool SoundPlayer::stop()
{
	mPlayingTimer.stop();
	return mTheSound.Stop();
}

void SoundPlayer::onTimer()
{
	if(mNrOfTimesPlayed > mNrOfReps)
    {
		mPlayingTimer.stop();
    }
    else
    {
		mTheSound.Play(0,false);
        mNrOfTimesPlayed++;
    }
}

bool SoundPlayer::play(int nrTimes, int msDelay)
{
	mNrOfTimesPlayed = 0;
	mPlayingTimer.start();
	return true;
}

