#ifndef mtkLogClientH
#define mtkLogClientH
#include "mtkProperty.h"
#include "mtkMessageContainer.h"
#include "mtkToggleSocketConnectionThread.h"

namespace mtk
{

class MTK_COMMON LogClient : public DSLObject
{
     public:
                                            LogClient();
        virtual                             ~LogClient();

        virtual bool                        Init(int pNumber = 50010, const string& hostname = gEmptyString, bool connectOnInit = true);
        virtual bool                        ShutDown();
        virtual void                        PostLogMessage(const string& msg);                        //Post a message to the message list
        string                              GetClientInfo();
        SocketClient*                       GetSocketClient(){return mSocketClient;}
        unsigned int                        NumberOfProcessedMessages(){return mNrOfProcessedMessages;}
        bool                                StartProcessing();
        bool                                StopProcessing();
        bool                                IsFinished();
        Thread*                             GetProcessingThread(){return mProcessThread;}
        bool                                IsConnected();
        bool                                IsConnecting(){return mToggleSocket.IsTogglingConnection();}
        bool                                SetLogLevel(int lvl);
        bool                                Disconnect();
        bool                                Connect(int pNumber = -1, const string& host = gEmptyString);
        bool                                ReConnect();
        void                                ToggleConnection();

    protected:
        bool                                mIsActive;
        unsigned int                        mNrOfProcessedMessages;
        SocketClient                        *mSocketClient;          //Socket to the server
        Property<int>                       mLogLevel;
        MessageContainer                 	mMessageContainer;
        LogMessageProcessor                 *mProcessThread;
        ToggleSocketConnectionThread        mToggleSocket;
};

}
#endif
