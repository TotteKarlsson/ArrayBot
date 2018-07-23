#ifndef atBarcodeBuilderH
#define atBarcodeBuilderH
#include <string>
#include "atDBCoreExporter.h"
//---------------------------------------------------------------------------
using std::string;

class ATDB_CORE BarCodeBuilder
{
    public:
                                            BarCodeBuilder(const char& rDel = '\r');
        bool                                isBuilding();
        bool                                hasBarCode();
        void                                reset();
        bool                                build(const char& ch);
        string                              getBarCode();
        int		                            getBarCodeValue();
        void								setBarCode(const string& bc);

    private:
        string                              mBarCode;
        char                                mRightDelimiter;
        bool                                mIsBuilding;
        bool                                mHasBarCode;
};

#endif
