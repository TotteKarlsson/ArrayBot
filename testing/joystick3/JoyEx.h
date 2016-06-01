#ifndef JoyExH
#define JoyExH
#include <dinput.h>
#include <windows.h>
#include <mmsystem.h>


const int _joystick_max = 16;

class joystick
{
	public:
    		int _enable_double;
            int _x,_y,_z,_r,_u,_v,_pov; // status non zero ?
            double x,y,z,r,u,v,pov;     // pos
            double x0,y0,z0,r0,u0,v0;   // min
            double dx,dy,dz,dr,du,dv;   // 2/(max-min)
            double deadzone;
            DWORD  buttons;

            JOYINFOEX joy_info;
            JOYCAPS joy_cp;

            int joy_list[_joystick_max],joy_num;
            int joy_id;

            joystick()
            {
            	deadzone = 0.1;
                _enable_double = 0;
                joy_id = -1;
                joy_num = 0;
                init_list();
            }

            joystick(joystick& a) { *this = a; }
            ~joystick()    {}

            joystick* operator = (const joystick *a) { *this = *a; return this; }

            void init_list();
            void refresh();
            void refresh_cp();
};

//---------------------------------------------------------------------------
void joystick::init_list()
{
    int i,j;
    joy_num = 0;
    j = JOYSTICKID1;

    for (i = 0; i < _joystick_max;i++)
    {
        joy_info.dwSize = sizeof(JOYINFOEX);
        joy_info.dwFlags  =  JOY_RETURNALL;
        if (joyGetPosEx(i, &joy_info)  ==  JOYERR_NOERROR)
        {
            joy_list[joy_num] = i;
            joy_num++;
            j++;
        }
    }

    j = 0;
    for (i = 0;i<joy_num;i++)
    {
        if (joy_list[i] == joy_id)
        {
        	j = 1;
            break;
        }
    }

    if (!j)
    {
        joy_id = -1;
        if (joy_num>0) joy_id = joy_list[0];
    }
    refresh();
    refresh_cp();
}
//---------------------------------------------------------------------------
void joystick::refresh()
{
    if (joy_id == -1)
    return;

    joy_info.dwSize  =  sizeof(JOYINFOEX);

    joy_info.dwFlags = JOY_RETURNALL;

    joyGetPosEx(joy_id,&joy_info);

    if (_enable_double)
    {
        x  =  double(joy_info.dwXpos-x0)*dx-1.0;
        y = double(joy_info.dwYpos-y0)*dy-1.0;
        z = double(joy_info.dwZpos-z0)*dz-1.0;
        r = double(joy_info.dwRpos-r0)*dr-1.0;
        u = double(joy_info.dwUpos-u0)*du-1.0;
        v = double(joy_info.dwVpos-v0)*dv-1.0;
        pov = double(joy_info.dwPOV)*0.01;
        _x = 0;
        if (x <= -deadzone) { _x = 1; x += deadzone; }
        if (x >= +deadzone) { _x = 1; x -= deadzone; }

        _y = 0;
        if (y <= -deadzone)
        {
        	_y = 1; y += deadzone;
        }

        if (y >= +deadzone)
        {
        	_y = 1; y -= deadzone;
        }

        _z = 0;
        if (z <= -deadzone) { _z = 1; z += deadzone; } if (z >= +deadzone) { _z = 1; z -= deadzone; }

        _r = 0;
        if (r <= -deadzone) { _r = 1; r += deadzone; } if (r >= +deadzone) { _r = 1; r -= deadzone; }

        _u = 0;
        if (u <= -deadzone) { _u = 1; u += deadzone; } if (u >= +deadzone) { _u = 1; u -= deadzone; }

        _v = 0;
        if (v <= -deadzone) { _v = 1; v += deadzone; } if (v >= +deadzone) { _v = 1; v -= deadzone; }

        _pov = 1;

        if(joy_info.dwPOV == 65535)
        {
        	_pov = 0;
        }

        buttons  =  joy_info.dwButtons;
    }
}

void joystick::refresh_cp()
{
    if (joy_id == -1)
    {
    	return;
    }

    joyGetDevCaps(joy_id, &joy_cp, sizeof(JOYCAPS));

    double q  =  2.0 + deadzone + deadzone;

    x0  =  joy_cp.wXmin;
    dx  =  joy_cp.wXmax-x0;

    if (dx)
    {
    	dx = q/dx;
    }

    y0  =  joy_cp.wYmin;
    dy  =  joy_cp.wYmax-y0;

    if(dy)
    {
    	dy  =  q/dy;
    }

    z0  =  joy_cp.wZmin;
    dz = joy_cp.wZmax-z0;
    if(dz)
    {
    	dz = q/dz;
    }

    r0 = joy_cp.wRmin;
    dr = joy_cp.wRmax-r0;
    if (dr)
    {
    	dr = q/dr;
    }

    u0 = joy_cp.wUmin;
    du = joy_cp.wUmax-u0;
    if (du)
    {
    	du = q/du;
    }

    v0 = joy_cp.wVmin;
    dv = joy_cp.wVmax-v0;
    if(dv)
    {
    	dv = q/dv;
    }
}


#endif
