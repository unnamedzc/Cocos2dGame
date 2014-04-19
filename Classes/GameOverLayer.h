#include "cocos2d.h"

class GameOverLayer:public cocos2d::CCLayerColor
{
public:
	cocos2d::CCLabelTTF* _label;
	bool init();
	~GameOverLayer();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(GameOverLayer);
	void returnToGame(cocos2d::CCNode*);
};