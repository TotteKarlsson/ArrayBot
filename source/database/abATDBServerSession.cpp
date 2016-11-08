#pragma hdrstop
#include "abATDBServerSession.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/RecordSet.h"
#include "abDBUtils.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
using namespace mtk;
using namespace ab;

using namespace Poco::Data;
using namespace Poco::Data::Keywords;

ATDBServerSession::ATDBServerSession(const string& db, const string& host, const string& user, const string& password)
:
DBConnection(db, host, user, password)
{}

ATDBServerSession::~ATDBServerSession()
{}

StringList ATDBServerSession::getTableNames()
{
   if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return StringList();
    }

    Statement select(*mTheSession);
    select << "SELECT table_name FROM information_schema.tables WHERE table_schema='"<<mDataBase<<"'" ;

    int nrRows = select.execute();
	RecordSet rs(select);

	StringList res;
    for(int i = 0; i < rs.rowCount(); i++)
    {
        Row row(rs.row(i));
        string val = row[0].convert<std::string>();
        res.append(val);
    }

    return res;
}

RecordSet* ATDBServerSession::getBlocks(dbSQLKeyword kw)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Statement select(*mTheSession);
    select << "SELECT * FROM block ORDER BY id " << ab::toString((dbSQLKeyword) kw);

    int nrRows = select.execute();
    return new RecordSet(select);
}

RecordSet* ATDBServerSession::getNotesForBlock(int blockID)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int id(blockID);

	Statement s(ses);
    s << "SELECT * FROM note WHERE id IN (SELECT note_id FROM block_note WHERE block_id = ?)", use(id), now;
    return new RecordSet(s);
}

bool ATDBServerSession::addNoteForBlock(int blockID, int userID, const string& _note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int bID(blockID);
    int uID(userID);
    string note(_note);

	Statement s(ses);
    s << "INSERT INTO note (created_by, note) VALUES(?, ?)", use(uID), use(note), now;
    s.reset(ses);

    int noteID;
    s << "SELECT MAX(id) FROM note", into(noteID), now;
    s.reset(ses);

    s << "INSERT INTO block_note (block_id, note_id) VALUES(?, ?)", use(bID), use(noteID), now;
	return true;
}

bool ATDBServerSession::addNoteForRibbon(const string& ribbonID, int userID, const string& _note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    string rID(ribbonID);
    int uID(userID);
    string note(_note);

	Statement s(ses);
    s << "INSERT INTO note (created_by, note) VALUES(?, ?)", use(uID), use(note), now;
    s.reset(ses);

    int noteID;
    s << "SELECT MAX(id) FROM note", into(noteID), now;
    s.reset(ses);

    s << "INSERT INTO ribbon_note (ribbon_id, note_id) VALUES(?, ?)", use(rID), use(noteID), now;
	return true;
}

bool ATDBServerSession::deleteNote(int noteID)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int nID(noteID);

	Statement s(ses);
    s << "DELETE FROM note WHERE id = ?", use(nID), now;
	return true;
}

bool ATDBServerSession::updateNote(int noteID, const string& note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int nID(noteID);
    string t(note);

	Statement s(ses);
    s << "UPDATE note SET note = ? WHERE id = ?", use(t), use(nID), now;
	return true;
}

bool ATDBServerSession::insertBlock(int userID, const string& lbl, const string& note)
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


bool ATDBServerSession::deleteBlock(int bId)
{
    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int bid(bId);

	Statement s(ses);

    //Delete associated notes
	s << "DELETE FROM block_note WHERE block_id = ?", use(bId), now;

    s.reset(ses);

    s << "DELETE FROM block WHERE id = ?", use(bId), now;
	return true;
}

bool ATDBServerSession::deleteNotesForBlock(int bId)
{
    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int bid(bId);

	Statement s(ses);

    //Delete associated notes
    s << "DELETE FROM note WHERE id IN (SELECT note_id FROM block_note WHERE block_id = ?)", use(bId), now;
    s.reset(ses);
	return true;
}

bool ATDBServerSession::deleteRibbonsForBlock(int bId)
{
    Session& ses = *mTheSession;

    //We need local variables for the statements..

    //Delete any notes
    int bID(bId);

	Statement s(ses);

    //Delete associated notes
    //Delete associated notes
    s << "DELETE FROM note WHERE id IN (SELECT note_id FROM ribbon_note where ribbon_id IN ( \
    	SELECT ribbon_id FROM ribbon WHERE block_id = ?))", use(bID), now;
	s.reset(ses);

    s << "DELETE FROM ribbon WHERE block_id = ?", use(bID), now;
    s.reset(ses);
	return true;
}

bool ATDBServerSession::deleteNotesForRibbon(const string& rId)
{
    Session& ses = *mTheSession;

    //We need local variables for the statements..
    string  rID(rId);

	Statement s(ses);

    //Delete associated notes
    s << "DELETE FROM note WHERE id IN (SELECT note_id FROM ribbon_note WHERE ribbon_id = ?)", use(rID), now;
    s.reset(ses);
	return true;
}

RecordSet* ATDBServerSession::getUsers(dbSQLKeyword kw)
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



