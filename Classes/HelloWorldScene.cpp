#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCLayerColor::initWithColor(ccc4(255,255,255,255));
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	this->setTouchEnabled(true);
	#if 0
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
# endif

	CCSprite*player=CCSprite::create("Player.png");
	player->setPosition(ccp(20,visibleSize.height/2));
	this->addChild(player);

	this->schedule(schedule_selector(HelloWorld::gameLogic),2);
	this->schedule(schedule_selector(HelloWorld::update));

	_projs=new CCArray;
	_targets=new CCArray;

    return true;
}

void HelloWorld::update(float delta)
{
	CCArray* targetToDelete=new CCArray;
	CCArray* projToDelete=new CCArray;
	CCObject* itarget,*iproj;
	CCARRAY_FOREACH(_targets,itarget){

		CCSprite*target=(CCSprite*)itarget;

		CCRect targetZone=CCRectMake(target->getPositionX(),
			target->getPositionY(),
			target->getContentSize().width,
			target->getContentSize().height);
	
		CCARRAY_FOREACH(_projs,iproj){

		CCSprite*proj=(CCSprite*)iproj;
		CCRect projZone=CCRectMake(
			proj->getPositionX(),
			proj->getPositionY(),
			proj->getContentSize().width,
			proj->getContentSize().height);

	    	if(projZone.intersectsRect(targetZone))
		   {
			  projToDelete->addObject(iproj);
			  targetToDelete->addObject(itarget);
		   }


		}//end of iterate p
	}//end of iterate 

	CCARRAY_FOREACH(projToDelete,iproj)
	{
		_projs->removeObject(iproj);
		CCSprite*proj=(CCSprite*)iproj;
		proj->removeFromParentAndCleanup(true);

	}

	CCARRAY_FOREACH(targetToDelete,itarget){
		_targets->removeObject(itarget);
		CCSprite*target=(CCSprite*)itarget;
		target->removeFromParentAndCleanup(true);
	}

	targetToDelete->release();
	projToDelete->release();
}

HelloWorld::~HelloWorld()
{
	if(_projs!=NULL)
	{
		_projs->release();
	}

	if(_targets!=NULL)
	{
		_targets->release();
	}
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch=(CCTouch*)pTouches->anyObject();
	CCPoint locInView=touch->getLocationInView();
	CCPoint loc=CCDirector::sharedDirector()->convertToGL(locInView);

	if(loc.x<=20)
	{
		return;
	}

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();  
	CCSprite*proj=CCSprite::create("Projectile.png");
	proj->setPosition(ccp(20,screenSize.height / 2.0));
	this->addChild(proj);

	_projs->addObject(proj);
	proj->setTag(2);

	double dx = loc.x - 20;  
	double dy = loc.y - screenSize.height / 2.0;  
	double d = sqrt(dx * dx + dy * dy); // 触摸点到出发点的距离  

	double D=sqrt(screenSize.width * screenSize.width + screenSize.height * screenSize.height);
	double ratio = D / d;  
	double endx = ratio * dx + 20; // 最终点的x坐标  
	double endy = ratio * dy + screenSize.height / 2.0;// 最终点的y坐标  

	CCMoveTo* move = CCMoveTo::create(D / 320, ccp(endx, endy));  
	CCCallFuncN* moveFinish = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::myDefine));  
	CCSequence* actions = CCSequence::create(move, moveFinish, NULL);  
	proj->runAction(actions);

}


void HelloWorld::gameLogic(float dt)
{
	this->createTarget();
}


void HelloWorld::createTarget()
{
	//enemy
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();

	target=CCSprite::create("Target.png");

	int y=rand()%(int)(screenSize.height);

	target->setPosition(ccp(screenSize.width-20,y));
	this->addChild(target);

	_targets->addObject(target);
	target->setTag(1);

	CCMoveTo*move=CCMoveTo::create(2,ccp(0,y));
	CCCallFuncN*disappear=CCCallFuncN::create(this,callfuncN_selector(HelloWorld::myDefine));

	CCSequence*actions=CCSequence::create(move,disappear,NULL);
	target->runAction(actions);
}

void HelloWorld::resposponseFunc(CCObject*obj)
{
	//CCLOG("menu item clicked");
	CCMoveTo*move=CCMoveTo::create(2,ccp(0,40));
	CCCallFuncN*disappear=CCCallFuncN::create(this,callfuncN_selector(HelloWorld::myDefine));

	CCSequence*actions=CCSequence::create(move,disappear,NULL);
	target->runAction(actions);

}

void HelloWorld::myDefine(CCNode*who)
{
	//who->setPosition(ccp(10,10));
	//who->setScale(2);
	who->removeFromParentAndCleanup(true);

	int tag=who->getTag();
	if(1==tag)
	{
		_targets->removeObject(who);
	}
	else if(2==tag)
	{
		CCLOG("_projs removed");
		_projs->removeObject(who);
	}

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
