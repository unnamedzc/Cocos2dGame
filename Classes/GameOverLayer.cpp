#include "GameOverLayer.h"
#include "HelloWorldScene.h"
USING_NS_CC;
bool GameOverLayer::init()
{
	if(CCLayerColor::initWithColor(ccc4(0,255,0,255)))
	{

		_label=CCLabelTTF::create("word","Artial",40);

		CCSize size=CCDirector::sharedDirector()->getVisibleSize();
		_label->setPosition(ccp(size.width/2,size.height/2));

		this->addChild(_label);

		CCDelayTime* delay=CCDelayTime::create(5);
		CCCallFuncN* returnToGame=CCCallFuncN::create(this,callfuncN_selector(GameOverLayer::returnToGame));
		this->runAction(CCSequence::create(delay,returnToGame,NULL));

		_label->retain();

		return true;
	}
	return false;
}

void GameOverLayer::returnToGame(CCNode*)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

GameOverLayer::~GameOverLayer()
{
	if(_label)
	{
		_label->release();

	}
}

cocos2d::CCScene* GameOverLayer::scene()
{
	CCScene*scene=CCScene::create();
	GameOverLayer*layer=GameOverLayer::create();

	layer->setTag(100);
	scene->addChild(layer);

	return scene;
}

