#include "Ads.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>

using namespace anysdk::framework;

#define  LOG_TAG    "Ads"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
Ads* Ads::_pInstance = NULL;

Ads::Ads()
{
    if(AgentManager::getInstance()->getAdsPlugin())
    {
    	AgentManager::getInstance()->getAdsPlugin()->setDebugMode(true);
        AgentManager::getInstance()->getAdsPlugin()->setAdsListener(this);
    }

}

Ads::~Ads()
{

}

Ads* Ads::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Ads();
    }
    return _pInstance;
}

void Ads::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}
void Ads::onAdsResult(AdsResultCode code, const char* msg)
{
	switch(code)
	{
	case kAdsReceived://Ads request received success

		break;
	case kAdsShown://Ads view shown

		break;
	case kAdsDismissed://Ads view dismissed!

		break;
	case kPointsSpendSucceed:// Succeed to spend the points

		break;
	case kPointsSpendFailed:// Fail to spend the points

		break;
	case kNetworkError:// Network errors

		break;
	case kUnknownError:// Unknown Error

		break;
	case kOfferWallOnPointsChanged:// The points are changed

		break;
	default:
		break;
	}

}


void Ads::showBanner()
{
	AgentManager::getInstance()->getAdsPlugin()->showAds(AD_TYPE_BANNER);
}

void Ads::hiddenBanner()
{
	AgentManager::getInstance()->getAdsPlugin()->hideAds(AD_TYPE_BANNER);
}

void Ads::showInterstitial()
{
	AgentManager::getInstance()->getAdsPlugin()->showAds(AD_TYPE_FULLSCREEN);
}

void Ads::hiddenInterstitial()
{
	AgentManager::getInstance()->getAdsPlugin()->hideAds(AD_TYPE_FULLSCREEN);
}
