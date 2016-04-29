#pragma hdrstop
#include "abTLWrapper.h"
//---------------------------------------------------------------------------

ThorLabsData::ThorLabsData()
{
	mDeviceIDMap[73] = "Benchtop Brushless Motor";
}

string ThorLabsData::getDeviceTypeName(int id)
{
	return mDeviceIDMap[id];
}

//int buildDeviceList()
//{
//	return TLI_BuildDeviceList();
//}
//
//int getDeviceListSize()
//{
//	return TLI_GetDeviceListSize();
//}


