#pragma hdrstop
#include "abATDBClientDBSession.h"
#include "mtkLogger.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Data/SessionFactory.h"
#include "mtkFileUtils.h"
#include "Poco/Data/RecordSet.h"
//---------------------------------------------------------------------------
using namespace mtk;
using namespace ab;
using namespace Poco::Data;
using namespace Poco::Data::Keywords;

ATDBClientDBSession::ATDBClientDBSession(const string& db, const string& host, const string& user, const string& password)
:
DBConnection(db, host, user, password)
{}

ATDBClientDBSession::~ATDBClientDBSession()
{}

RecordSet* ATDBClientDBSession::getBlocks(dbSQLKeyword kw)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Statement select(*mTheSession);
    select << "SELECT * FROM block ORDER BY id " << mtk::toString(kw);

    int nrRows = select.execute();
    return new RecordSet(select);
}


bool ATDBClientDBSession::insertSensorData(int _id, double _t, double _h)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..

    int id(_id);
    double t(_t), h(_h);

	Statement s(ses);
    s << "INSERT INTO sensor_data (device_id, temperature, humidity) VALUES(?,?,?)", use(id), use(t), use(h);
    s.execute();
    s.reset(ses);
	return true;
}

bool ATDBClientDBSession::insertImageFile(const string& fName, int userID, const string& note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..

    string f(fName), n(note);

	Statement s(ses);
    s << "INSERT INTO umimage (file_name) VALUES(?)", use(f), now;
    s.reset(ses);

    int image_id;
    s << "SELECT MAX(id) FROM umimage", into(image_id), now;
    s.reset(ses);

	return insertImageNote(image_id, userID, note);
}

bool ATDBClientDBSession::insertImageNote(int imageID, int userID, const string& note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;
	Statement s(ses);

    //We need local variables for the statements..
	int id(imageID);

    string n(note);
    int user_id(userID);
    s << "INSERT INTO note (created_by, note) VALUES(?, ?)", use(user_id), use(n), now;
    s.reset(ses);

    int noteID;
    s << "SELECT MAX(id) FROM note", into(noteID), now;
    s.reset(ses);

    s << "INSERT INTO umimage_note (image_id, note_id) VALUES(?, ?)", use(id), use(noteID), now;
	return true;
}

bool ATDBClientDBSession::insertBlock(int userID, const string& lbl, const string& note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int id(userID);
    string l(lbl), n(note);

	Statement s(ses);
    s << "INSERT INTO block (created_by, label) VALUES(?, ?)", use(id), use(l), now;
    s.reset(ses);

    int blockID;
    s << "SELECT MAX(id) FROM block", into(blockID), now;
    s.reset(ses);

    s << "INSERT INTO note (created_by, note) VALUES(?, ?)", use(id), use(n), now;
    s.reset(ses);

    int noteID;
    s << "SELECT MAX(id) FROM note", into(noteID), now;
    s.reset(ses);

    s << "INSERT INTO block_note (block_id, note_id) VALUES(?, ?)", use(blockID), use(noteID), now;
	return true;
}

bool ATDBClientDBSession::deleteBlock(int bId)
{
    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int bid(bId);

	Statement s(ses);
    s << "DELETE FROM block WHERE id = ?", use(bId), now;

	return true;
}

RecordSet* ATDBClientDBSession::getUsers(dbSQLKeyword kw)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Statement select(*mTheSession);
    select << "SELECT * FROM user";
    int nrRows = select.execute();

    Log(lInfo) <<"Selected "<<nrRows<<" from user table";
    return new RecordSet(select);
}

bool ATDBClientDBSession::insertOrUpdateUser(const _uid, const string& u)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Statement select(*mTheSession);
    string user(u);
    int uid(_uid);
    select << "INSERT INTO user (id, user_name) VALUES (?,?) ON DUPLICATE KEY UPDATE user_name=user_name", use(uid), use(user);
    int nrRows = select.execute();
	return nrRows ? true : false;

}

