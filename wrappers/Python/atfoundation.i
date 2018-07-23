%module(docstring="Array Tomography Library for Python (atfoundation), (c) 2016-2018 Allen Institute for BrainScience",threads="1", directors="0" ) atfoundation

// ************************************************************
// Module Includes
// ************************************************************
%{
#include "dslObject.h"
#include "atATObject.h"
#include "atCore.h"
#include  <string>
using namespace dsl;
using namespace std;
%}
 
//The atfoundation module is using many features from dsl
%include "p:/build/debug/include/dsl/dsl.i"

#define AT_CORE
//ATCore header only contains a few utlity functions
%include "atCore.h"

//%inline %{
//    char* getVersion() {
//        return "0.5";
//    }
//%}


