#ifndef atReticleH
#define atReticleH
#include <VCL.Graphics.hpp>
#include <utility>
#include "atATObject.h"
#include "atVCLCommonExporter.h"
//---------------------------------------------------------------------------

using std::pair;

class AT_VCLCOMMON TReticle : public at::ATObject
{
	public:
    	enum ReticleType	        {rtCrossHair, rtCircle, rtBoth};
							        TReticle(TCanvas* canvas, ReticleType rt = rtBoth, TColor = clRed);
		void				        draw(int clientW, int clientH);

        void				        setCircleRadius(int r);
        int				        	getCircleRadius(){return mCircleRadius;}
        void				        setReticleCenter(int x, int y);
        pair<int, int>              getReticleCenter(){return mReticleCenter;}

        void						visible(bool vis);
        bool						isVisible();

    protected:
    	TCanvas* 			        mCanvas;
        bool						mVisible;
        ReticleType			        mReticleType;
        TColor				        mLineColor;
        int					        mCircleRadius;
        pair<int,int>		        mReticleCenter;
};
#endif
