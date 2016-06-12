#ifndef amlDataStructuresH
#define amlDataStructuresH

#include "Poco/DateTime.h"
#include <System.hpp>

enum ApplicationMessageEnum
{
    amSplashWasClosed,
    amNewOrder,
    amSalesSummary,
    amDBDataStats,
    amCheckForNewOrdersStarted,
    amCheckForNewOrdersFinished,
    amAllOrdersSyncStarted,
    amAllOrdersSyncFinished
};

using Poco::DateTime;

struct DBStatistics
{
	int 		mNumberOfRecs;
	DateTime 	mFirstOrderDate;
	DateTime 	mLastOrderDate;
	int 		mNumberOfCustomers;
	int 		mNumberOfRepeatCustomers;
	int			mNumberOfProducts;
	int 		mNumberOfStates;
	int 		mAllTimeUnitsSoldCount;
	double 		mAllTimeOrderSales;
};

struct SalesSummary
{
	int			mNrOfUnitsLastDay;
	double		mProductSalesLastDay;

	int			mNrOfUnitsLast7Days;
	double		mProductSalesLast7Days;

	int			mNrOfUnitsLast15Days;
	double		mProductSalesLast15Days;

	int			mNrOfUnitsLast30Days;
	double		mProductSalesLast30Days;
	DateTime 	mTimeStamp;
};

struct AppMessageStruct;

struct mlxStructMessage
{
	Cardinal            Msg;
	int                 wparam;
	AppMessageStruct*   lparam;
	LRESULT             Result;
};

struct AppMessageStruct
{
	ApplicationMessageEnum 	mMessageEnum;
	void*                   mData;

};




#endif
