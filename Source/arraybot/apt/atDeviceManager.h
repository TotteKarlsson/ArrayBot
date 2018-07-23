#ifndef atDeviceManagerH
#define atDeviceManagerH
#include <string>
#include <map>
#include "arraybot/atABExporter.h"
#include "atATObject.h"

#include "dslStringList.h"
#include "atAPTDevice.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------

using dsl::gEmptyString;
using dsl::StringList;
namespace at
{

using std::string;
using std::map;
//using std::ostream;



//Thorlabs device
//class APTDevice;
//struct TLI_DeviceInfo;

AT_AB bool 			buildDeviceList();
AT_AB int 			getNumberOfConnectedDevices();



class AT_AB DeviceManager : public ATObject
{
    public:
                                                    DeviceManager();
	    virtual                                     ~DeviceManager();
    	bool										reBuildDeviceList();

        APTDevice*                                  connectDevice(int serial);
        int                                         connectAllDevices();

        bool                                        disConnect(APTDevice* device = NULL);
        bool                                        disConnectAll();

        string                                      getInfo() const;
        StringList                                  getDeviceSerials() const;

        int                                         getNumberOfConnectableDevices() const;
        int                                         getNumberOfConnectedDevices() const;
        APTDevice*                                  getDevice(int serial);
        APTDevice*                                  getFirst() const;
        APTDevice*                                  getNext() const;
        APTDevice*                                  getPrevious() const;
        APTDevice*                                  getCurrent() const;

        AT_AB
        friend ostream&                             operator<<(ostream& os, DeviceManager& pm);

    private:
        mutable map<int, APTDevice*>              	mDevices;
        mutable map<int, APTDevice*>::iterator    	mDevicesIter;
};

}
#endif
