#ifndef atPresetH
#define atPresetH
#include <string>
#include "atATObject.h"
#include "dslProperty.h"
//---------------------------------------------------------------------------

using std::string;
using dsl::Property;
using dsl::ObjectType;
using dsl::IniFile;

template <class T>
class Preset : public Property<T>
{
    public:
        						                Preset(const string& name, const T& val);
		virtual	        		                ~Preset(){}

                                                //!The set member function may change hardware and is defined in
                                                //!subclases
		virtual bool			                set() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////////
        string                                  getINIRecord()							        {return Property<T>::getINIRecord();}
        bool                                    assignValueFromString(const string& val)        {return Property<T>::assignValueFromString(val);}
        string                                  getLabel()								        {return Property<T>::getLabel();}
        string                                  getValueAsString() const				        {return Property<T>::getValueAsString();}
        void*                                   getValueHandle()						        {return Property<T>::getValueHandle();}
        ObjectType                              getPropertyType()						        {return Property<T>::getPropertyType();}
        bool                                    read(IniFile* iniFile, const string& section)	{return Property<T>::read(iniFile, section);}
        bool                                    write(IniFile* iniFile, const string& section)	{return Property<T>::write(iniFile, section);}

                                                //Copy temporary value to real value
        void                                    applyModification()								{Property<T>::applyModification();}
		///////////////////////////////////////////////////////////////////////////////////////////
};

template<class T>
Preset<T>::Preset(const string& name, const T& val)
:
Property<T>(val, name)
{
}

#endif
