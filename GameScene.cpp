#include "GameScene.h"
#include "constants.h"
#include "InputComponent.h"
#include "GraphicComponent.h"
#include "HeroGraphicComponent.h"
#include "WeaponGraphicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "BreedGraphicComponent.h"
#include "ButtonGraphicComponent.h"
#include "BotInputComponent.h"
#include "PhysicComponent.h"
#include "GameLayer.h"
#include <time.h>

USING_NS_CC;

int GameScene::m_level = 0;
int GameScene::m_coin  = 0;
int GameScene::m_life  = 0;
std::vector<int> GameScene::m_vecNameWeapon;

Scene *GameScene::createScene(bool nextLevel, int coin, int life, std::vector<int>& vecNameWeapon) 
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	if (nextLevel)
	{
		if (++m_level == 12)
		{
			m_level = 0;
		}

		m_coin = coin;
		m_life = life;
	}
	else 
	{
		m_level = 0;
	}
	
	if (vecNameWeapon.size())
	{
		m_vecNameWeapon.resize(vecNameWeapon.size());
		std::copy(vecNameWeapon.begin(), vecNameWeapon.end(), m_vecNameWeapon.begin());
	}
	else
	{
		m_vecNameWeapon.clear();
	}

	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	Size _visibleSize   = Director::getInstance()->getVisibleSize();
	Vec2 origin			= Director::getInstance()->getVisibleOrigin();

	m_background = Sprite::create("res/Backgrounds/BackgroundNebula.jpg");
	m_background->setScale(_visibleSize.width / m_background->getContentSize().width,
		_visibleSize.height / m_background->getContentSize().height);
	m_background->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);

	this->addChild(m_background);

	m_countLevel = 0;

	auto edgeBody = PhysicsBody::createEdgeBox(_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(SCENE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(_visibleSize.width / 2 + origin.x, _visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	LoadFileNameBackground();
	SetBackground();

	m_graphicComponentHero	= new HeroGraphicComponent(CNT_NAME_HERO_HELL);
	m_graphicComponentHero->setPosition(_visibleSize.width  / m_graphicComponentHero->getContentSize().width + 100,
										_visibleSize.height / m_graphicComponentHero->getContentSize().height + 100);
	m_graphicComponentHero->setScale(_visibleSize.width / m_graphicComponentHero->getContentSize().width / 10,
									 _visibleSize.height / m_graphicComponentHero->getContentSize().height / 8);
	
	m_graphicComponentButtonFire = new ButtonGraphicComponent();

	m_inputComponent				= new PlayerInputComponent();
	m_gameObjectMonster				= new GameObjectMonster();
	m_botInputComponent				= new BotInputComponent();
	m_physicComponent				= new PhysicComponent();
	m_hero							= std::make_shared<Monster>(
													*m_graphicComponentHero, 
													*m_graphicComponentButtonFire,
													*m_gameObjectMonster,
													*m_inputComponent,
													*m_botInputComponent,
													*m_physicComponent
												 );
	
	m_bonusGraphicComponent = std::make_shared<BonusGraphicComponent>();
	m_bonusGraphicComponent->setName("bonus");

	m_gameLayer = GameLayer::create();
	
	this->addChild(m_gameLayer);

	auto _touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(InputComponent::onTouchBegan, m_inputComponent);
	_touchListener->onTouchMoved = CC_CALLBACK_2(InputComponent::onTouchMoved, m_inputComponent);
	_touchListener->onTouchEnded = CC_CALLBACK_2(InputComponent::onTouchEnded, m_inputComponent);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicComponent::onContactBegin, m_physicComponent);
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->schedule(schedule_selector(GameScene::update),		CNT_TIME_UPDATE_SCENE);
	//this->schedule(schedule_selector(GameScene::SpawnEnemyMeteor),	CNT_TIME_SPAWN_ENEMY_METEOR);
	this->schedule(schedule_selector(GameScene::SpawnEnemyAirplane), CNT_TIME_SPAWN_ENEMY_AIRPLANE);
	//this->schedule(schedule_selector(GameScene::SpawnBonus),	CNT_TIME_SPAWN_BONUS);

	return true;
}

void GameScene::update(float dt)
{
	m_hero->Update		(*this);
	m_gameLayer->Update	(*m_hero);
}

void GameScene::SpawnEnemyMeteor(float dt)
{
	m_gameObjectMonster->SpawnerEnemyMeteor(*this);
}

void GameScene::SpawnEnemyAirplane(float dt)
{
	m_gameObjectMonster->SpawnerEnemyAirplane(*this);
}

void GameScene::SpawnBonus(float dt)
{
	if (m_bonusGraphicComponent->m_actived)
	{
		return;
	}

	m_bonusGraphicComponent->AddBonus(CNT_TYPE_OBJECT_RANDOM);

	Size _visibleSize	= Director::getInstance()->getVisibleSize();
	Size _sizeBonus		= m_bonusGraphicComponent->getContentSize();		

	srand(time(NULL));
	int _rand_X = rand() % 240 + 200;
	int _rand_Y = rand() % 200 + 20;

	m_bonusGraphicComponent->setPosition(_rand_X, _rand_Y);
	m_bonusGraphicComponent->setScale(	_visibleSize.width  / _sizeBonus.width / 10,
										_visibleSize.height / _sizeBonus.height / 10
									 );
	m_bonusGraphicComponent->m_actived = true;
	m_bonusGraphicComponent->setVisible(true);

	if (m_bonusGraphicComponent->m_typeObject == CNT_NAME_DIAMOND ||
		m_bonusGraphicComponent->m_typeObject == CNT_NAME_GOLD ||
		m_bonusGraphicComponent->m_typeObject == CNT_NAME_ONYX ||
		m_bonusGraphicComponent->m_typeObject == CNT_NAME_RUBY
		)
	{
		this->m_hero->m_stateBonus = Monster::StateBonus::SUPER_BONUS;
	}
}

void GameScene::LoadFileNameBackground()
{
	m_vecNameBackground.push_back("res/Backgrounds/1.png");
	m_vecNameBackground.push_back("res/Backgrounds/9.png");
	m_vecNameBackground.push_back("res/Backgrounds/10.png");
	m_vecNameBackground.push_back("res/Backgrounds/11.png");
	m_vecNameBackground.push_back("res/Backgrounds/12.png");
	m_vecNameBackground.push_back("res/Backgrounds/13.png");
	m_vecNameBackground.push_back("res/Backgrounds/14.png");
	m_vecNameBackground.push_back("res/Backgrounds/15.png");
	m_vecNameBackground.push_back("res/Backgrounds/3-night.png");
	m_vecNameBackground.push_back("res/Backgrounds/4-night.png");
	m_vecNameBackground.push_back("res/Backgrounds/4.png");
	m_vecNameBackground.push_back("res/Backgrounds/5-night.png");
	m_vecNameBackground.push_back("res/Backgrounds/5.png");
	m_vecNameBackground.push_back("res/Backgrounds/6-night.png");
	m_vecNameBackground.push_back("res/Backgrounds/6.png");
	m_vecNameBackground.push_back("res/Backgrounds/7-night.png");
	m_vecNameBackground.push_back("res/Backgrounds/7.png");
}

void GameScene::SetBackground()
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();

	m_background = Sprite::create(m_vecNameBackground[m_level]);
	//m_background->setScale(_visibleSize.width / m_background->getContentSize().width,
	//	_visibleSize.height / m_background->getContentSize().height);
	
	m_background->setPosition(_visibleSize.width / 2,
		_visibleSize.height / 2);
	
	//this->addChild(m_background);
}

void GameScene::LoadLevel()
{
	/*auto reScene = TransitionFade::create(1.0f, GameScene::createScene(true, ), Color3B(0, 0, 0));
	Director::getInstance()->replaceScene(reScene);*/
}

GameScene::~GameScene()
{
	CCLOG("destructor gamescene");
}

/**********Jump table*********/
//std::random_shuffle(_grid.begin(), _grid.end());		//	shuffle all vector(change position for each component vector)
//this->setAnchorPoint();								//  around him move and transition