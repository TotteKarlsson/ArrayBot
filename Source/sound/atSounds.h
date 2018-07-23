#ifndef atSoundsH
#define atSoundsH
#include "atSoundExporter.h"
#include "dslThread.h"
#include <string>
#include <deque>
#include <mmsystem.h>
#include "atATObject.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

using std::string;
using std::deque;
using dsl::Thread;
using dsl::StringList;

////These are names of sounds available
////These will be replaced by usage of properties instead
//enum ABSound
//{
//	absMotorStop = 0,
//    absAlert1,
//    absMotorWarning,
//    absCameraShot,
//    absSlowSpeed,
//    absMediumSpeed,
//    absFastSpeed,
//    absBeforeBackOff,
//    absButtonClick4,
//    absDefaultClick
//};
//
//!Load our resource DLL and get a list of sound resources
AT_SOUND StringList		getSoundResources();

//!Flags are
//!SND_ASYNC SND_SYNC
//!See: https://msdn.microsoft.com/en-us/library/windows/desktop/dd743680(v=vs.85).aspx
//AT_SOUND void 			playABSound(ABSound, long flags = SND_ASYNC);

//class SoundPlayer;
//
//class SoundWorker : public dsl::Thread, public ATObject
//{
//	public:
//    						SoundWorker(deque<ABSound>& soundDeck , Poco::Mutex bufferMutex);
//
//	private:
//    	SoundPlayer&		mSoundPlayer;
//};
//
//class AT_SOUND SoundPlayer : public ATObject
//{
//	public:
//								SoundPlayer();
//
//                                //!Add a sound to the soundplayer
//		bool					play(ABSound aSound, int repeat, int delay);
//
//    private:
//    	deque<ABSound> 			mSounds;
//        SoundWorker				mSoundWorker;
//        Poco::Mutex				mSoundMutex;
//};

#endif
