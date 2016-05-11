#pragma hdrstop
#include "abXYZUnitPosition.h"
//---------------------------------------------------------------------------

XYZUnitPosition::XYZUnitPosition(const string& lbl, double x, double y, double z)
:
mPosition(x,y,z),
mLabel(lbl)
{}

XYZUnitPosition::~XYZUnitPosition()
{}

string XYZUnitPosition::getLabel()
{
	return mLabel;
}

double XYZUnitPosition::x() const
{
	return mPosition.x();
}

double XYZUnitPosition::y() const
{
	return mPosition.y();
}

double XYZUnitPosition::z() const
{
	return mPosition.z();
}

//Point XYZUnitPosition::getPosition()
//{
//	return mPosition;
//}

