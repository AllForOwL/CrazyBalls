#include "TransitionMainScene.h"
#include "GameScene.h"

const int CNT_SCALE = 5;
const int CNT_CHOOISE_COIN		= 10;
const int CNT_CHOOISE_LIFE		= 11;
const int CNT_CHOOISE_WEAPON	= 12;

USING_NS_CC;

int TransitionMainScene::m_sCoin = 0;
int TransitionMainScene::m_sLife = 0;
std::vector<int> TransitionMainScene::m_sVecWeapon;

Scene *TransitionMainScene::createScene(int coin, int life, std::vector<int>& vecWeapon)
{
	auto scene = Scene::create();

	m_sCoin = coin;
	m_sLife = life;
	m_sVecWeapon.resize(vecWeapon.size());
	std::copy(vecWeapon.begin(), vecWeapon.end(), m_sVecWeapon.begin());

	auto layer = TransitionMainScene::create();

	scene->addChild(layer);

	return scene;
}

bool TransitionMainScene::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	m_quentityCounter = 0;

	m_coin = 0;
	m_life = 0;

	Size _visibleSize = Director::getInstance()->getVisibleSize();
	Size _spriteSize;

	m_spriteCoin = Sprite::create("res/Bonus/Coins/Coin_1.png");
	_spriteSize  = m_spriteCoin->getContentSize();
	m_spriteCoin->setScale(_visibleSize.width / _spriteSize.width / CNT_SCALE,
		_visibleSize.height / _spriteSize.height / CNT_SCALE);
	m_spriteCoin->setPosition(_visibleSize.width / 4, _visibleSize.height / 2);
	this->addChild(m_spriteCoin);

	m_spriteLife = Sprite::create("res/Bonus/Power/life_power_up_1.png");
	_spriteSize = m_spriteLife->getContentSize();
	m_spriteLife->setScale(_visibleSize.width / _spriteSize.width / CNT_SCALE,
		_visibleSize.height / _spriteSize.height / CNT_SCALE);
	m_spriteLife->setPosition(_visibleSize.width / 4 * 2, _visibleSize.height / 2);
	this->addChild(m_spriteLife);

	m_spriteWeapon = Sprite::create("res/Weapons/AK47.png");
	_spriteSize = m_spriteWeapon->getContentSize();
	m_spriteWeapon->setScale(_visibleSize.width / _spriteSize.width / CNT_SCALE,
		_visibleSize.height / _spriteSize.height / CNT_SCALE);
	m_spriteWeapon->setPosition(_visibleSize.width / 4  * 3, _visibleSize.height / 2);
	this->addChild(m_spriteWeapon);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(TransitionMainScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

/*virtual*/ bool TransitionMainScene::onTouchBegan(Touch* touch, Event* event_)
{
	Rect _rectCoin		= m_spriteCoin->getBoundingBox();
	Rect _rectLife		= m_spriteLife->getBoundingBox();
	Rect _rectWeapon	= m_spriteWeapon->getBoundingBox();

	auto _touch = touch;
	auto _location = _touch->getLocation();
	
	// chooise coin
	if (_rectCoin.containsPoint(_location))
	{	
		m_coin = m_sCoin;
		CCLOG("COIN");
	}// life
	else if (_rectLife.containsPoint(_location))
	{
		m_life = m_sLife;
		CCLOG("LIFE");
	}//weapon
	else if (_rectWeapon.containsPoint(_location))
	{
		m_vecWeapon.resize(m_sVecWeapon.size());
		std::copy(m_sVecWeapon.begin(), m_sVecWeapon.end(), m_vecWeapon.begin());
		CCLOG("WEAPON");
	}

	if (++m_quentityCounter == 2)
	{
		srand(time(NULL));
		auto reScene = TransitionFade::create(0.1f, GameScene::createScene(true, m_coin, m_life, m_vecWeapon), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
		Director::getInstance()->replaceScene(reScene);
	}

	return true;
}

TransitionMainScene::~TransitionMainScene()
{
	CCLOG("destructor trnsition mainscene");
}

/*	04:10:16
Animation:
	+ power;
	+ coin;
	- onyx(by kills enemy); // not need
	- chooise counter in ends level (second from three bonuses):
		1 - power;
		2 - weapon;
		3 - ball for kills enemy(onyx);
	- save on next level chooises counter;
*/