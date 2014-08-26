#include "HelloWorldScene.h"
#include "AgentManager.h"
#include "Ads.h"
#include "Analytics.h"
using namespace anysdk::framework;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	//Initialize AnySDK
    std::string oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";
    std::string appKey = "2B88D645-C6CA-D5CD-92F0-2E0D0933421D";
    std::string appSecret = "af990098f49aac67ceab938d39561a74";
    std::string privateKey = "A9B1ED4FCCDA9D48465311C61C540BF0";

    AgentManager::getInstance()->init(appKey,appSecret,privateKey,oauthLoginServer);
    AgentManager::getInstance()->loadALLPlugin();


    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menuClose = Menu::create(closeItem, NULL);
    menuClose->setPosition(Vec2::ZERO);
    this->addChild(menuClose, 0);

    /////////////////////////////
    // 3. add your codes below...

    auto showBannerLable = LabelTTF::create("Show Banner",  "Arial", 20);
    CCMenuItemLabel *showBannerItem = CCMenuItemLabel::create(showBannerLable, this, menu_selector(HelloWorld::showBanner) );
    showBannerItem->setPosition(Vec2(origin.x + visibleSize.width/2,
    		visibleSize.height - 100.0));


    auto hiddenBannerLable = LabelTTF::create("Hidden Banner",  "Arial", 20);
    CCMenuItemLabel *hiddenBannerItem = CCMenuItemLabel::create(hiddenBannerLable, this, menu_selector(HelloWorld::hiddenBanner) );
    hiddenBannerItem->setPosition(Vec2(origin.x + visibleSize.width/2,
    		visibleSize.height - 200.0));

    auto showInterstitialLable = LabelTTF::create("Show Interstitials",  "Arial", 20);
    CCMenuItemLabel *showInterstitialItem = CCMenuItemLabel::create(showInterstitialLable, this, menu_selector(HelloWorld::showInterstitial) );
    showInterstitialItem->setPosition(Vec2(origin.x + visibleSize.width/2,
    		visibleSize.height - 300.0));

    auto hiddenInterstitialLable = LabelTTF::create("Hidden Interstitials",  "Arial", 20);
    CCMenuItemLabel *hiddenInterstitialItem = CCMenuItemLabel::create(hiddenInterstitialLable, this, menu_selector(HelloWorld::hiddenInterstitial) );
    hiddenInterstitialItem->setPosition(Vec2(origin.x + visibleSize.width/2,
    		visibleSize.height - 400.0));

    auto menu = Menu::create(showBannerItem, hiddenBannerItem, showInterstitialItem, hiddenInterstitialItem, NULL);
    //auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);


    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

    //release AnySDK
    AgentManager::getInstance()->unloadALLPlugin();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::showBanner(Ref* pSender)
{
	Ads::getInstance()->showBanner();
	Analytics::getInstance()->logEvent("showBanner");

}

void HelloWorld::hiddenBanner(Ref* pSender)
{
	Ads::getInstance()->hiddenBanner();
	Analytics::getInstance()->logEvent("hiddenBanner");
}

void HelloWorld::showInterstitial(Ref* pSender)
{
	Ads::getInstance()->showInterstitial();
	std::map<std::string, std::string> info;
	info["type"] = "Interstitial";
	Analytics::getInstance()->logEvent("showInterstitial");
}

void HelloWorld::hiddenInterstitial(Ref* pSender)
{
	Ads::getInstance()->hiddenInterstitial();
	std::map<std::string, std::string> info;
	info["type"] = "Interstitial";
	Analytics::getInstance()->logEvent("hiddenInterstitial",info);
}
