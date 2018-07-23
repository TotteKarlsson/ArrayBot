#ifndef atApplicationSoundH
#define atApplicationSoundH
#include "dslProperty.h"
#include "atATObject.h"
#include "atDirectSound.h"
#include "dslConstants.h"
#include "dslStringList.h"
#include "dslUtils.h"


using dsl::Property;
using dsl::StringList;
using dsl::IniFile;
class ApplicationSound;
namespace dsl
{
	AT_SOUND	string	toString(const ApplicationSound& sound);
}

//!An application sound object is a sound that is associated to a part of an application. Its properties are typically stored in
//!an ini file.
class AT_SOUND ApplicationSound : public DirectSound
{
	public:
							            ApplicationSound(const string& name = dsl::gEmptyString, long vol = 0, bool repeats = false, bool enabled = false, HWND handle = NULL);
							            ApplicationSound(const ApplicationSound& s);
							            ~ApplicationSound();
		ApplicationSound&	            operator=(const ApplicationSound& rhs);

        void				            setVolume(int v);
        bool   	  			   	        play(DWORD dwStartPosition = 0, bool bLoop = FALSE);
        long				            getVolume() const {return mVolume;}

        bool				            enabled() const {return mEnabled;}
        void				            enable()  {mEnabled = true;}
        void				            disable() {mEnabled = false;}
        bool				            repeats() const {return mRepeats;}
        void				            setRepeats(bool val){mRepeats = val;}

    private:
        long			                mVolume;
        bool			                mRepeats;
        bool							mEnabled;
};

template<>
inline Property<ApplicationSound>::operator ApplicationSound() const
{
    return (*mValue);
}

//---------------------------------------------------------------------------
template<> inline
std::string Property< ApplicationSound >::getValueAsString() const
{
    return dsl::toString(getValue());
}

template<> inline
bool Property< ApplicationSound >::write(IniFile* iniFile, const string& section)
{
    if(iniFile == NULL)
    {
        return false;
    }

    string toWrite;
    toWrite = dsl::toString(getValue());
    iniFile->writeString(mKey, toWrite, "", section);
    return true;
}

template<> inline
bool Property< ApplicationSound >::read(IniFile* iniFile, const string& section)
{
    if(iniFile == NULL)
    {
        return false;
    }

    StringList val(iniFile->readString(mKey, section, ""),',');
    ApplicationSound tempVal;
    if(val.size() == 4)
    {
    	tempVal = ApplicationSound(val[0], dsl::toInt(val[1]), toBool(val[2]), toBool(val[3]));
    }

    mWasRead = iniFile->wasItFound();
    setValue( mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

template<> inline
bool Property< ApplicationSound >::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
string Property< ApplicationSound >::getTypeName() const
{
    return "applicationSound";
}


#endif
