#pragma hdrstop
#include "abProcessSequenceProject.h"
#include "mtkXMLUtils.h"
#include "mtkLogger.h"
#include "abProcessSequence.h"

using namespace mtk;
using namespace tinyxml2;

//XML Version history
/*
    0.5 : Original version
*/

const string gProcessSequenceProjectFileVersion    = "0.6";

ProcessSequenceProject::ProcessSequenceProject(ProcessSequence& ps, const string& fName)
:
Project(fName),
mParent(ps)
{
	resetXML();
}

ProcessSequenceProject::~ProcessSequenceProject()
{}

string ProcessSequenceProject::getPresentModelVersion()
{
    return gProcessSequenceProjectFileVersion;
}

bool ProcessSequenceProject::resetXML()
{
    mProjectRoot = mTheXML.NewElement("ProcessSequenceProject");
    mRootNode = mTheXML.InsertFirstChild(mProjectRoot);

    //Insert as a minmimum project file version
    XMLElement* version = mTheXML.NewElement("version");
    XMLText* 	versionValue = mTheXML.NewText(gProcessSequenceProjectFileVersion.c_str());
    version->InsertEndChild(versionValue);
    mProjectRoot->InsertEndChild(version);

    XMLElement* name 		= mTheXML.NewElement("name");
    XMLText* 	nameValue 	= mTheXML.NewText(mParent.getName().c_str());
	name->InsertEndChild(nameValue);
    mProjectRoot->InsertEndChild(name);
    return true;
}

bool ProcessSequenceProject::save(const string& fName)
{
    resetXML();
//    Explorer*   anExplorer = mParent.getExplorer();
//    Box&        aBox =  mParent.getTheBox();
//    if(!anExplorer)
//    {
//        return false;
//    }
//
//    if(!saveExplorerSettings())
//    {
//        return false;
//    }
//
//    //For now, do a brute force save of Moleculix Objects
//    XMLElement* mlxObjects = newElement("MoleculixObjects");
//
//    //First save Molecules
//    Molecule* aMol = aBox.getFirstMolecule();
//    while(aMol)
//    {
//        Log(lDebug) << "Saving object: " << aMol->getTypeName();
//        XMLElement* elem = aMol->addToXMLDocument(mTheXML, mlxObjects);
//        aMol = aBox.getNextMolecule();
//    }
//
//    //Then save atoms not part of any molecule
//    Atom* a = aBox.getFirstAtom();
//    while(a)
//    {
//        if(!a->isPartOfMolecule())
//        {
//            Log(lDebug) << "Saving object: " << a->getTypeName();
//            XMLElement* elem = a->addToXMLDocument(mTheXML, mlxObjects);
////            this->addNode(elem);
//        }
//        a = aBox.getNextAtom();
//    }
//
//    this->addNode(mlxObjects);
//
////    //Save explorer objects..
////    ExplorerTree& objects = anExplorer->getObjectTree();
////
////    //create a ExplorerObjects node
////    if(objects.getNrOfSiblings() > 0)
////    {
////        XMLElement* eObjects = newElement("ExplorerObjects");
////        eObjects->SetAttribute("Count", objects.getNrOfSiblings());
////
////        for(int i = 0; i < objects.getNrOfSiblings(); i++)
////        {
////            ExplorerObject* obj = objects.getSibling(i);
////            if(obj)
////            {
////                Log(lDebug) << "Saving object: " << obj->getTypeName();
////                XMLElement* elem = obj->addToXMLDocument(mTheXML, eObjects);
////            }
////        }
////        this->addNode(eObjects);
////    }
////
////    mIsModified = false;
////
    return saveToFile(fName);
}

bool ProcessSequenceProject::open()
{
    try
    {
        Log(lInfo) << "Attempting to load model: "<<this->getModelFileName();
        if(!loadExplorerSettings())
        {
            Log(lWarning) << "Failed to load explorer settings";
        }

        int nrOfObjs = loadObjects();
        Log(lDebug) << "Loaded " << nrOfObjs << " explorer objects";
        return true;
    }
    catch(...)
    {
        throw(("Bad model file!"));
    }
}

bool ProcessSequenceProject::loadExplorerSettings()
{
//    //Get explorer data
//    XMLElement* explorer = this->getXML("Explorer");
//
//    int winAttr[4];
//    if(!explorer)
//    {
//        return false;
//    }
//
//    Log(lDebug3) << "Creating an explorer";
//    winAttr[0] = explorer->IntAttribute("xPos");
//    winAttr[1] = explorer->IntAttribute("yPos");
//    winAttr[2] = explorer->IntAttribute("xWidth");
//    winAttr[3] = explorer->IntAttribute("yWidth");
////    Explorer* anExplorer = mParent.getExplorer();
//    if(!anExplorer)
//    {
//        anExplorer = mParent.openExplorer(winAttr[2], winAttr[3], winAttr[0], winAttr[1]);
//        if(!anExplorer)
//        {
//            return false;
//        }
//    }
//
//    //Retrieve camera settings
//    XMLElement* cameraE = explorer->FirstChildElement("Camera");
//    if(!cameraE)
//    {
//        return false;
//    }
//    vtkCamera* camera = anExplorer->getCamera();
//
//    if(!camera)
//    {
//        return false;
//    }
//
//    //Get Position
//    XMLElement* elem = cameraE->FirstChildElement("Position");
//    if(elem)
//    {
//        double vec[3];
//        vec[0] = elem->DoubleAttribute("x");
//        vec[1] = elem->DoubleAttribute("y");
//        vec[2] = elem->DoubleAttribute("z");
//        camera->SetPosition(vec);
//    }
//
//    elem = cameraE->FirstChildElement("FocalPoint");
//    if(elem)
//    {
//        double vec[3];
//        vec[0] = elem->DoubleAttribute("x");
//        vec[1] = elem->DoubleAttribute("y");
//        vec[2] = elem->DoubleAttribute("z");
//        camera->SetFocalPoint(vec);
//    }
//
//    elem = cameraE->FirstChildElement("ViewUp");
//    if(elem)
//    {
//        double vec[3];
//        vec[0] = elem->DoubleAttribute("x");
//        vec[1] = elem->DoubleAttribute("y");
//        vec[2] = elem->DoubleAttribute("z");
//        camera->SetViewUp(vec);
//    }
//
//    elem = cameraE->FirstChildElement("ViewAngle");
//    if(elem)
//    {
//        double dblValue = toDouble(elem->GetText());
//        camera->SetViewAngle(dblValue);
//    }
//
//    elem = cameraE->FirstChildElement("ParallellProjection");
//    if(elem)
//    {
//        bool val = toBool(elem->GetText());
//        camera->SetParallelProjection(val);
//    }
//
//    elem = cameraE->FirstChildElement("ParallellScale");
//    if(elem)
//    {
//        double dblValue = toDouble(elem->GetText());
//        camera->SetParallelScale(dblValue);
//    }
//
//    return true;
}

int ProcessSequenceProject::loadObjects()
{
//    //This function creates explorer objects from XML
//    XMLElement* objects = this->getXML("MoleculixObjects");
//
//    if(objects == NULL)
//    {
//        return 0;
//    }
//
//    Explorer* anExplorer = mParent.getExplorer();
//
//    int nrOfObjects = 0;
//
//     //Load object by object
//    XMLElement* obj = objects->FirstChildElement();
//    while(obj)
//    {
//        //Find out what kind of element obj is!
//        shared_ptr<RigidBody> aObj = createObject(obj);
//        if(aObj)
//        {
//            anExplorer->add(aObj.get());
//            Log(lDebug) <<"Imported a "<<obj->Name()<<" object.";
//            nrOfObjects++;
//        }
//        else
//        {
//            Log(lError) << "Failed importing a "<<obj->Name()<<" object";
//        }
//
//        obj = obj->NextSiblingElement();
//    }
//
//    return nrOfObjects;
}

//shared_ptr<RigidBody> ProcessSequenceProject::createObject(tinyxml2::XMLElement* element)
//{
//    if(!element)
//    {
//        return shared_ptr<RigidBody>();
//    }
//
//    if(compareStrings(element->Name(), "molecule", csCaseInsensitive))
//    {
//        //Molecular data in Moleculix project files are in the CML format
//        XMLPrinter printer;
//        element->Accept(&printer);
//        string cml(printer.CStr());
//        shared_ptr<Molecule> mol = mParent.getTheBox().createMolecule();
//        mol->load(cml, dfCML);
//        return mol;
//    }
//
//    if(compareStrings(element->Name(), "atom", csCaseInsensitive))
//    {
//        //Molecular data in Moleculix project files are in the CML format
//        XMLPrinter printer;
//        element->Accept(&printer);
//        string cml(printer.CStr());
//        shared_ptr<Atom> a = mParent.getTheBox().createAtom(cml);
//        return a;
//    }
//
//
////    if(compareStrings(element->Name(), "AxisSystem", csCaseInsensitive))
////    {
////        //Get Position
////        Point origin(getRecordOfDoubles(element, "origin", StringList("x,y,z", ',')));
////        AxisSystem* axes = new AxisSystem;//(origin);
////
////        //Get Axes vectors
////        Point x(getRecordOfDoubles(element, "x-axis", StringList("x,y,z", ',')));
////        Point y(getRecordOfDoubles(element, "y-axis", StringList("x,y,z", ',')));
////        Point z(getRecordOfDoubles(element, "z-axis", StringList("x,y,z", ',')));
////        axes->X() = x;
////        axes->Y() = y;
////        axes->Z() = z;
////        axes->setOrigin(origin);
////        return axes;
////    }
//
//    return shared_ptr<RigidBody>();
//}


//bool ProcessSequenceProject::saveExplorerSettings()
//{
//    XMLElement* explorer = newElement("Explorer");
//    Explorer* anExplorer = mParent.getExplorer();
//
//    if(!anExplorer)
//    {
//        return false;
//    }
//    //This does not seem to work
//    int* pos = anExplorer->getRenderWindow()->GetPosition();
//
//    int* size = anExplorer->getRenderWindow()->GetSize();
//
//    explorer->SetAttribute("xPos", pos[0]);
//    explorer->SetAttribute("yPos", pos[1]);
//
//    explorer->SetAttribute("xWidth", size[0]);
//    explorer->SetAttribute("yWidth", size[1]);
//
//    //Camera settings
//    XMLElement* camRecord = this->newElement("Camera");
//    vtkCamera* vCamera = anExplorer->getCamera();
//    double* vec = vCamera->GetPosition();
//
//    //Save Camera position, FocalPoint, ViewUp & ViewAngle
//    XMLElement* elem = this->newElement("Position");
//    elem->SetAttribute("x", vec[0]);
//    elem->SetAttribute("y", vec[1]);
//    elem->SetAttribute("z", vec[2]);
//    camRecord->InsertEndChild(elem);
//
//    vec = vCamera->GetFocalPoint();
//    elem = this->newElement("FocalPoint");
//    elem->SetAttribute("x", vec[0]);
//    elem->SetAttribute("y", vec[1]);
//    elem->SetAttribute("z", vec[2]);
//    camRecord->InsertEndChild(elem);
//
//    vec = vCamera->GetViewUp();
//    elem = this->newElement("ViewUp");
//    elem->SetAttribute("x", vec[0]);
//    elem->SetAttribute("y", vec[1]);
//    elem->SetAttribute("z", vec[2]);
//    camRecord->InsertEndChild(elem);
//
//    double dVal = vCamera->GetViewAngle();
//    elem = this->newElement("ViewAngle");
//    elem->SetText(toString(dVal).c_str());
//    camRecord->InsertEndChild(elem);
//
//    bool bVal = vCamera->GetParallelProjection() == 0 ? false : true;
//    elem = this->newElement("ParallellProjection");
//    elem->SetText(toString(bVal).c_str());
//    camRecord->InsertEndChild(elem);
//
//    dVal = vCamera->GetParallelScale();
//    elem = this->newElement("ParallellScale");
//    elem->SetText(toString(dVal).c_str());
//    camRecord->InsertEndChild(elem);
//
//    explorer->InsertEndChild(camRecord);
//    this->addNode(explorer);
//    return true;
//}


