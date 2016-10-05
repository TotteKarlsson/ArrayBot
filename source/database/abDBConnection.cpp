#pragma hdrstop
#include "abATDBServerSession.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SessionFactory.h"
#include "abDBUtils.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
using namespace mtk;
using namespace ab;

using namespace Poco::Data;
using namespace Poco::Data::Keywords;

DBConnection::DBConnection(const string& db, const string& host, const string& user, const string& password)
:
mDataBase(db),
mHost(host),
mDataBaseUser(user),
mDataBasePassword(password),
mTheSession(NULL)
{}

DBConnection::~DBConnection()
{}

bool DBConnection::isConnected()
{
	return mTheSession ? true : false;
}

bool DBConnection::connect()
{
	try
    {
		//Register DB connector
	    MySQL::Connector::registerConnector();

    	//Create connection string
		//string str = "host=127.0.0.1;user=atdb_client;password=atdb123;db=atdb";
        stringstream c;
        c <<"host="<<mHost<<";"<<"user="<<mDataBaseUser<<";"<<"password="<<mDataBasePassword<<";"<<"db="<<mDataBase;
		mTheSession = new Poco::Data::Session(Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, c.str() ));
        Log(lInfo) << "Connected to "<<mHost;
        return true;
    }
  	catch (const Poco::Data::MySQL::ConnectionException& e)
    {
        Log(lError) << e.message() <<endl;
        return false;
    }
    catch(const Poco::Data::MySQL::StatementException& e)
    {
        Log(lError) << e.message() << endl;
        return false;
    }
    catch(const Poco::Data::MySQL::MySQLException& e)
    {
        Log(lError) << e.message() << endl;
        return false;
    }
}

bool DBConnection::disConnect()
{
	try
    {
    	delete mTheSession;
        mTheSession = NULL;
	    MySQL::Connector::unregisterConnector();
        return true;
    }
    catch(...)
    {
    	Log(lError) << "Failed to delete db session..";
        return false;
    }
}
