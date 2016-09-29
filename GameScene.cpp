#include "GameScene.h"
#include "constants.h"
#include "InputComponent.h"
#include "GraphicComponent.h"
#include "HeroGraphicComponent.h"
#include "WeaponGraphicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "BreedGraphicComponent.h"
#include "BotInputComponent.h"
#include "PhysicComponent.h"
#include "GameLayer.h"

USING_NS_CC;

int GameScene::m_level = 0;

Scene *GameScene::createScene() 
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	if (++m_level == 12)
	{
		m_level = 0;
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
	m_graphicComponentHero->setScale(_visibleSize.width / m_graphicComponentHero->getContentSize().width / 6,
									 _visibleSize.height / m_graphicComponentHero->getContentSize().height / 4);
	this->addChild(m_graphicComponentHero);
	
	
	m_graphicComponentWeapon = new WeaponGraphicComponent(200, CNT_NAME_WEAPON_AK47);
	m_graphicComponentWeapon->setPosition(m_graphicComponentHero->getPosition().x, m_graphicComponentHero->getPosition().y - 20);
	m_graphicComponentWeapon->setScale(_visibleSize.width / m_graphicComponentWeapon->getContentSize().width / 8,
									   _visibleSize.height / m_graphicComponentWeapon->getContentSize().height / 8);
	this->addChild(m_graphicComponentWeapon);
	
	
	m_graphicComponentBullet	= new PlayerBulletGraphicComponent(150, CNT_NAME_BULLET_DEFAULT); 
	m_graphicComponentBullet->setScale(_visibleSize.width / m_graphicComponentBullet->getContentSize().width / 40,
										_visibleSize.height / m_graphicComponentBullet->getContentSize().height  / 40
										);
	this->addChild(m_graphicComponentBullet);

	m_inputComponent			= new PlayerInputComponent();
	m_gameObjectMonster			= new GameObjectMonster();
	m_botInputComponent			= new BotInputComponent();
	m_physicComponent			= new PhysicComponent();
	m_hero						= new Monster(	m_graphicComponentHero,		m_graphicComponentWeapon, 
												m_graphicComponentBullet,	m_gameObjectMonster, 
												m_inputComponent,			m_botInputComponent, 
												m_physicComponent
											 );
		
	m_bonusGraphicComponent = new BonusGraphicComponent();
	m_bonusGraphicComponent->setName("bonus");
	this->addChild(m_bonusGraphicComponent);

	m_gameLayer = GameLayer::create();
	
	this->addChild(m_gameLayer);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(InputComponent::onKeyPressed, m_inputComponent);
	//listener->onKeyReleased = CC_CALLBACK_2(InputComponent::onKeyReleased, inputComponent);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicComponent::onContactBegin, m_physicComponent);
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->schedule(schedule_selector(GameScene::update),		CNT_TIME_UPDATE_SCENE);
	//this->schedule(schedule_selector(GameScene::Spawn),			CNT_TIME_SPAWN);
	this->schedule(schedule_selector(GameScene::SpawnBonus),	CNT_TIME_SPAWN_BONUS);
	//this->scheduleUpdate();

	return true;
}

void GameScene::update(float dt)
{
	m_hero->Update		(*this);
	m_gameLayer->Update	(*m_hero);
}

void GameScene::Spawn(float dt)
{
	m_gameObjectMonster->Spawner(*this);
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

	m_bonusGraphicComponent->setPosition(250, 160);
	m_bonusGraphicComponent->setScale(	_visibleSize.width  / _sizeBonus.width / 10,
										_visibleSize.height / _sizeBonus.height / 10
									 );
	m_bonusGraphicComponent->m_actived = true;
	m_bonusGraphicComponent->setVisible(true);

	if (!m_bonusGraphicComponent->getParent())
	{
		this->addChild(m_bonusGraphicComponent);
	}
}

void GameScene::LoadFileNameBackground()
{
	m_vecNameBackground.push_back("res/Backgrounds/1-night.png");
	m_vecNameBackground.push_back("res/Backgrounds/2-night.png");
	m_vecNameBackground.push_back("res/Backgrounds/2.png");
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
	m_background->setScale(_visibleSize.width / m_background->getContentSize().width,
		_visibleSize.height / m_background->getContentSize().height);
	m_background->setPosition(_visibleSize.width / 2,
		_visibleSize.height / 2);
	
	this->addChild(m_background);
}

void GameScene::LoadLevel()
{
	auto reScene = TransitionFade::create(1.0f, GameScene::createScene(), Color3B(0, 0, 0));
	Director::getInstance()->replaceScene(reScene);
}

GameScene::~GameScene()
{

}