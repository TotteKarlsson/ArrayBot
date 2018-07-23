#ifndef atdbVCLUtilsH
#define atdbVCLUtilsH
#include <Datasnap.DBClient.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Data.SqlExpr.hpp>
#include <vector>
#include <string>
#include "labelprinter/atTSCLIB.h"
//---------------------------------------------------------------------------

using std::vector;
using std::string;
PACKAGE bool 				SortClientDataSet(TClientDataSet* ClientDataSet,  const String& FieldName);
PACKAGE std::vector<int> 	getSelectedIDS(TDBGrid* grid, const std::string& field);
PACKAGE int 				getLastInsertID(TSQLConnection* connection);
PACKAGE bool				createAndPrintCoverSlipLabels(BarcodePrintParameters& p, const vector<int>& coverslipIDS, TSQLConnection* c);
PACKAGE bool				addNoteToMultipleCoverSlips(const vector<int>& coverslipIDS, TSQLConnection* c, const string& note);
#endif
