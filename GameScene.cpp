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

Scene *GameScene::createScene(bool nextLevel, int coin, int life) 
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	if (nextLevel)
	{
		++m_level;
		m_coin = coin;
		m_life = life;
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

	m_visibleSize   = Director::getInstance()->getVisibleSize();
	Vec2 origin		= Director::getInstance()->getVisibleOrigin();

	m_background = Sprite::create("res/Backgrounds/BackgroundNebula.jpg");
	m_background->setScale(m_visibleSize.width / m_background->getContentSize().width,
		m_visibleSize.height / m_background->getContentSize().height);
	m_background->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	this->addChild(m_background);

	auto edgeBody = PhysicsBody::createEdgeBox(m_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(SCENE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(m_visibleSize.width / 2 + origin.x, m_visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	LoadFileNameBackground();
	SetBackground();

	m_graphicComponentHero			= new HeroGraphicComponent(CNT_NAME_HERO_HELL);		
	m_graphicComponentButtonFire	= new ButtonGraphicComponent();
	m_gameObjectMonster				= new GameObjectMonster();
	m_inputComponent				= new PlayerInputComponent();
	m_botInputComponent				= new BotInputComponent();
	m_physicComponent				= new PhysicComponent();
	m_hero							= new Monster	(
														*m_graphicComponentHero, 
														*m_graphicComponentButtonFire,
														*m_gameObjectMonster,
														*m_inputComponent,
														*m_botInputComponent,
														*m_physicComponent
													);
	
	m_bonusGraphicComponent = new BonusGraphicComponent();
	m_bonusGraphicComponent->setName("bonus");

	this->addChild(m_bonusGraphicComponent);

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

	this->schedule(schedule_selector(GameScene::SpawnEnemyAirplane),	CNT_TIME_SPAWN_ENEMY_AIRPLANE);
	this->schedule(schedule_selector(GameScene::update),				CNT_TIME_UPDATE_SCENE);
	//this->schedule(schedule_selector(GameScene::SpawnEnemyMeteor),	CNT_TIME_SPAWN_ENEMY_METEOR);

	return true;
}

void GameScene::update(float dt)
{
	m_hero->Update		(*this);
	m_gameLayer->Update	(*m_hero);
	m_bonusGraphicComponent->Update(*m_hero, *this);
}

void GameScene::SpawnEnemyMeteor(float dt)
{
	m_gameObjectMonster->SpawnerEnemyMeteor(*this);
}

void GameScene::SpawnEnemyAirplane(float dt)
{
	m_gameObjectMonster->SpawnerEnemyAirplane(*this);
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
	Size m_visibleSize = Director::getInstance()->getVisibleSize();

	m_background = Sprite::create(m_vecNameBackground[m_level]);
	m_background->setPosition(m_visibleSize.width / 2,
		m_visibleSize.height / 2);
}

GameScene::~GameScene()
{
	CCLOG("destructor gamescene");
}

/**********Jump table*********/
//std::random_shuffle(_grid.begin(), _grid.end());		//	shuffle all vector(change position for each component vector)
//this->setAnchorPoint();								//  around him move and transition