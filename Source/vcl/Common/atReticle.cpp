#pragma hdrstop
#include "atReticle.h"
#include <vcl.controls.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

TReticle::TReticle(TCanvas* canvas, ReticleType rt, TColor cl)
:
mCanvas(canvas),
mReticleType(rt),
mCircleRadius(10),
mLineColor(cl),
mReticleCenter(0,0),
mVisible(true)
{}

void TReticle::setCircleRadius(int r)
{
	mCircleRadius = r;
}

void TReticle::visible(bool vis)
{
	mVisible = vis;
}

void TReticle::setReticleCenter(int x, int y)
{
	mReticleCenter = pair<int,int>(x,y);
}

bool TReticle::isVisible()
{
	return mVisible;
}

void TReticle::draw(int w, int h)
{
	if(!mVisible)
    {
    	return;
    }

    mCanvas->Pen->Color = mLineColor;
    mCanvas->Brush->Style = bsClear;

    int r(mCircleRadius); //Circle radius
    if(mReticleType == rtCircle || mReticleType == rtBoth)
    {
	   	mCanvas->Ellipse(-r + mReticleCenter.first, -r + mReticleCenter.second, r + mReticleCenter.first, r + mReticleCenter.second);
    }
    else
    {
    	r = 0;
    }

	//Top vertical
    mCanvas->MoveTo(mReticleCenter.first, -h/2);
    mCanvas->LineTo(mReticleCenter.first, -r + mReticleCenter.second);
    mCanvas->MoveTo(mReticleCenter.first, h/2); 	//Bottom vertical
    mCanvas->LineTo(mReticleCenter.first, r + mReticleCenter.second);

    //Left horiz
    mCanvas->MoveTo(-r + mReticleCenter.first, 				   mReticleCenter.second);
    mCanvas->LineTo(-w/2., mReticleCenter.second);
    mCanvas->MoveTo(r + mReticleCenter.first, 					   mReticleCenter.second);     //Right horiz
    mCanvas->LineTo(w/2.,  mReticleCenter.second);
}
