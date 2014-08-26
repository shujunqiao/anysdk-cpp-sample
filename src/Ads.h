#ifndef __MY_Ads_H__
#define __MY_Ads_H__

#include "AgentManager.h"
#include "string.h"
using namespace anysdk::framework;
using namespace std;
class Ads:public AdsListener
{
public:
    static Ads* getInstance();
    static void purge();

    virtual void onAdsResult(AdsResultCode code, const char* msg);

    void showBanner();

    void hiddenBanner();

    void showInterstitial();

    void hiddenInterstitial();


private:
    	Ads();
    virtual ~Ads();

    static Ads* _pInstance;

};

#endif
