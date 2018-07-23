#ifndef atDBCredentialsH
#define atDBCredentialsH
#include "atDBExporter.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------

using std::string;
using dsl::gNoneString;

class AT_DB DBCredentials
{
	public:
    				                DBCredentials(const string& h = gNoneString, const string& db = gNoneString, const string& user = gNoneString, const string& pwd = gNoneString)
                                    :
                                    mHost(h),
                                    mDB(db),
                                    mUserName(user),
                                    mUserPassword(pwd)
                                    {}
		string		                getHost() const {return mHost;}
		string		                getDB() const {return mDB;}
		string		                getUserName() const {return mUserName;}
		string		                getUserPassword() const {return mUserPassword;}
        void		                setup(const string& h = gNoneString, const string& db = gNoneString, const string& user = gNoneString, const string& pwd = gNoneString);

    private:
    	string	                    mHost;
        string                      mDB;
    	string	                    mUserName;
    	string	                    mUserPassword;
};


#endif
