#include <Python.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    char* myPath = "C:\\\\pDisk\\\\ArrayCam\\\\plugins\\\\python";
    string moduleName("pure_embedding"), functionName("execute");

    vector<string> args;
    args.push_back("2");
    args.push_back("45");

	Py_SetProgramName(Py_DecodeLocale("TjolaHey", NULL));

    Py_Initialize();
	PyRun_SimpleString("import sys");
    stringstream cmd;
    cmd << "sys.path.append(\"" << myPath << "\")";
	PyRun_SimpleString(cmd.str().c_str());
    PyRun_SimpleString("print (sys.path)");


    PyObject* pName = PyUnicode_DecodeFSDefault(moduleName.c_str());

    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (!pModule)
    {
        PyErr_Print();
        cerr << "Failed to load python module: " << pName;
        return 1;
    }

    PyObject* pFunc = PyObject_GetAttrString(pModule, functionName.c_str());

    if (!pFunc || !PyCallable_Check(pFunc))
    {
        if (PyErr_Occurred())
        {
            PyErr_Print();
        }
        cerr << "Failed to find function "<<functionName;
    }
    else
    {
        PyObject* pArgs = PyTuple_New(args.size());
        PyObject *pValue;
        for (int i = 0; i < args.size(); ++i)
        {
            pValue = PyLong_FromLong(atoi(args[i].c_str()));
            if (!pValue)
            {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert argument\n");
                return 1;
            }

            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, i, pValue);
        }

        pValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs);
        if (pValue)
        {
            cout << "Result of call: "<<PyLong_AsLong(pValue) << endl;
            Py_DECREF(pValue);
        }
        else
        {
            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            PyErr_Print();
            cerr << "Python call failed" << endl;
            return 1;
        }
    }

    Py_XDECREF(pFunc);
    Py_DECREF(pModule);

    Py_Finalize();
    return 0;
}
