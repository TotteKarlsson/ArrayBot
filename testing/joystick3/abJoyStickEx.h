#ifndef abJoyStickExH
#define abJoyStickExH
#include <dinput.h>
#include <windows.h>
#include <mmsystem.h>


const int gMaxNrOfJoySticks = 16;

class JoyStickEx
{
	public:
                                mJoyStickEx()
                                {
                                    deadzone = 0.1;
                                    mJoyStickID = -1;
                                    mCurrentJoyStickID = 0;
                                    init_list();
                                }

					            ~JoyStickEx()    {}
            int _x,_y,_z,_r,_u,_v,_pov; // status non zero ?
            double x,y,z,r,u,v,pov;     // pos
            double x0,y0,z0,r0,u0,v0;   // min
            double dx,dy,dz,dr,du,dv;   // 2/(max-min)
            double 							deadzone;


            JOYINFOEX 						mJoyInfo;
            JOYCAPS 						mJoyStickCapabilities;

            int 							mListOfJoySticks[gMaxNrOfJoySticks];
            int								mCurrentJoyStickID;
            int 							mJoyStickID;

            void 							refresh();
	private:
//            JoyStickEx(JoyStickEx& a) { *this = a; }


            JoyStickEx* operator = (const JoyStickEx *a) { *this = *a; return this; }
            void init_list();

            void refresh_cp();
};

//---------------------------------------------------------------------------
void JoyStickEx::init_list()
{
    int i,j;
    mCurrentJoyStickID = 0;
    j = JOYSTICKID1;

    for (i = 0; i < gMaxNrOfJoySticks; i++)
    {
        mJoyInfo.dwSize = sizeof(JOYINFOEX);
        mJoyInfo.dwFlags  =  JOY_RETURNALL;
        if (joyGetPosEx(i, &mJoyInfo)  ==  JOYERR_NOERROR)
        {
            mListOfJoySticks[mCurrentJoyStickID] = i;
            mCurrentJoyStickID++;
            j++;
        }
    }

    j = 0;
    for (i = 0;i<mCurrentJoyStickID;i++)
    {
        if (mListOfJoySticks[i] == mJoyStickID)
        {
        	j = 1;
            break;
        }
    }

    if (!j)
    {
        mJoyStickID = -1;
        if (mCurrentJoyStickID>0)
        	mJoyStickID = mListOfJoySticks[0];
    }
    refresh();
    refresh_cp();
}
//---------------------------------------------------------------------------
void JoyStickEx::refresh()
{
    if (mJoyStickID == -1)
    return;

    mJoyInfo.dwSize  =  sizeof(JOYINFOEX);

    mJoyInfo.dwFlags = JOY_RETURNALL;

    joyGetPosEx(mJoyStickID, &mJoyInfo);

}

void JoyStickEx::refresh_cp()
{
    if (mJoyStickID == -1)
    {
    	return;
    }

    joyGetDevCaps(mJoyStickID, &mJoyStickCapabilities, sizeof(JOYCAPS));

    double q  =  2.0 + deadzone + deadzone;

    x0  =  mJoyStickCapabilities.wXmin;
    dx  =  mJoyStickCapabilities.wXmax-x0;

    if (dx)
    {
    	dx = q/dx;
    }

    y0  =  mJoyStickCapabilities.wYmin;
    dy  =  mJoyStickCapabilities.wYmax-y0;

    if(dy)
    {
    	dy  =  q/dy;
    }

    z0  =  mJoyStickCapabilities.wZmin;
    dz = mJoyStickCapabilities.wZmax-z0;
    if(dz)
    {
    	dz = q/dz;
    }

    r0 = mJoyStickCapabilities.wRmin;
    dr = mJoyStickCapabilities.wRmax-r0;
    if (dr)
    {
    	dr = q/dr;
    }

    u0 = mJoyStickCapabilities.wUmin;
    du = mJoyStickCapabilities.wUmax-u0;
    if (du)
    {
    	du = q/du;
    }

    v0 = mJoyStickCapabilities.wVmin;
    dv = mJoyStickCapabilities.wVmax-v0;
    if(dv)
    {
    	dv = q/dv;
    }
}


#endif
