#pragma hdrstop
#include "abPosition.h"
//---------------------------------------------------------------------------

Position::Position(const string& lbl, double x, double y, double z)
:
mPosition(x,y,z),
mLabel(lbl)
{}

Position::~Position()
{}

string Position::getLabel()
{
	return mLabel;
}

double Position::x() const
{
	return mPosition.x();
}

double Position::y() const
{
	return mPosition.y();
}

double Position::z() const
{
	return mPosition.z();
}
