#include "GraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"

GraphicComponent::GraphicComponent()
{
	m_state = STATE_WALK;
	m_pSprite = Sprite::create("walk-0001.png");

	m_countSpritesInVectorHeroWalk		= 1;
	m_countSpritesInVectorHeroAttack	= 0;
	m_countSpritesInVectorHeroJump		= 0;
	m_countSpritesInVectorWeaponFire	= 0;

}

void GraphicComponent::update(Monster& heroes, GraphicComponent& graphic)
{

}

void GraphicComponent::Draw(EventKeyboard::KeyCode& keyCode, GameScene& scene, Monster& hero, GraphicComponent& graphic)
{
	int _sizeVector = LoadSprites(keyCode);
	Size _size = Director::getInstance()->getVisibleSize();

	switch (m_state)
	{
		case STATE_WALK:
		{
			//Walk();
			hero.m_sprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesHeroWalk[m_countSpritesInVectorHeroWalk]));
			hero.m_sprite->setScale(_size.width / hero.m_sprite->getContentSize().width / 6,
				_size.height / hero.m_sprite->getContentSize().height / 2);
			hero.m_sprite->setPosition(_size.width / 2,
				_size.height / 2);
			if (++m_countSpritesInVectorHeroWalk == 8)
			{
				m_countSpritesInVectorHeroWalk = 0;
			}
			break;
		}
		case STATE_ATTACK:
		{
			//Attack();

			break;
		}
		case STATE_JUMP:
		{
			//Jump();

			break;
		}
		case STATE_FIRE:
		{
			//Fire();

			break;
		}
	}
	scene.addChild(hero.m_sprite);
}

void GraphicComponent::Walk()
{
	Size _size = Director::getInstance()->getVisibleSize();
	
	m_pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesHeroWalk[m_countSpritesInVectorHeroWalk]));
	m_pSprite->setScale(_size.width / m_pSprite->getContentSize().width / 6,
		_size.height / m_pSprite->getContentSize().height / 2);
	m_pSprite->setPosition(_size.width / 2,
						  _size.height / 2);
	if (++m_countSpritesInVectorHeroWalk == 8)
	{
		m_countSpritesInVectorHeroWalk = 0;
	}
}

void GraphicComponent::Attack()
{
	Size _size = Director::getInstance()->getVisibleSize();

	m_pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesHeroAttack[m_countSpritesInVectorHeroAttack]));
	m_pSprite->setScale(_size.width / m_pSprite->getContentSize().width / 6,
		_size.height / m_pSprite->getContentSize().height / 2);
	m_pSprite->setPosition(50,
		_size.height / 2 - 80);

	if (++m_countSpritesInVectorHeroAttack == 4)
	{
		m_countSpritesInVectorHeroAttack = 0;
	}
}

void GraphicComponent::Jump()
{
	Size _size = Director::getInstance()->getVisibleSize();

	m_pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesHeroJump[m_countSpritesInVectorHeroJump]));
	m_pSprite->setScale(_size.width / m_pSprite->getContentSize().width / 6,
		_size.height / m_pSprite->getContentSize().height / 2);
	m_pSprite->setPosition(50,
		_size.height / 2 - 80);

	if (++m_countSpritesInVectorHeroJump == 3)
	{
		m_countSpritesInVectorHeroJump = 0;
	}
}

void GraphicComponent::Fire()
{
	Size _size = Director::getInstance()->getVisibleSize();

	m_pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesWeaponFire[m_countSpritesInVectorWeaponFire]));
	m_pSprite->setScale(_size.width / m_pSprite->getContentSize().width / 6,
		_size.height / m_pSprite->getContentSize().height / 2);
	m_pSprite->setPosition(50,
		_size.height / 2 - 80);

	if (++m_countSpritesInVectorWeaponFire == 4)
	{
		m_countSpritesInVectorWeaponFire = 0;
	}
}

int GraphicComponent::LoadSprites(EventKeyboard::KeyCode& keyCode)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			m_vecSpritesHeroWalk.push_back("walk-0001.png");
			m_vecSpritesHeroWalk.push_back("walk-0002.png");
			m_vecSpritesHeroWalk.push_back("walk-0003.png");
			m_vecSpritesHeroWalk.push_back("walk-0004.png");
			m_vecSpritesHeroWalk.push_back("walk-0005.png");
			m_vecSpritesHeroWalk.push_back("walk-0006.png");
			m_vecSpritesHeroWalk.push_back("walk-0007.png");
			m_vecSpritesHeroWalk.push_back("walk-0008.png");

			m_state = STATE_WALK;

			return m_vecSpritesHeroWalk.size();
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			m_vecSpritesHeroJump.push_back("fall-0001.png");
			m_vecSpritesHeroJump.push_back("fall-0002.png");
			m_vecSpritesHeroJump.push_back("fall-0003.png");

			m_state = STATE_JUMP;

			return m_vecSpritesHeroJump.size();
		}
		case EventKeyboard::KeyCode::KEY_A:
		{
			m_vecSpritesHeroAttack.push_back("attack-0001.png");
			m_vecSpritesHeroAttack.push_back("attack-0002.png");
			m_vecSpritesHeroAttack.push_back("attack-0003.png");
			m_vecSpritesHeroAttack.push_back("attack-0004.png");

			m_state = STATE_ATTACK;

			return m_vecSpritesHeroAttack.size();
		}
		case EventKeyboard::KeyCode::KEY_F:
		{
			m_vecSpritesWeaponFire.push_back("fire-0001.png");
			m_vecSpritesWeaponFire.push_back("fire-0002.png");
			m_vecSpritesWeaponFire.push_back("fire-0003.png");
			m_vecSpritesWeaponFire.push_back("fire-0004.png");
			m_vecSpritesWeaponFire.push_back("fire-0005.png");

			m_state = STATE_FIRE;

			return m_vecSpritesWeaponFire.size();
		}
	}
}

GraphicComponent::~GraphicComponent()
{

}