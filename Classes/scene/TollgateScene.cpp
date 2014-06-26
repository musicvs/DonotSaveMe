#include "TollgateScene.h"
#include "BackgroundLayer.h"
#include "entity\Player.h"
#include "ObjectTag.h"
#include "MonsterLayer.h"
#include "entity\Monster.h"

TollgateScene::~TollgateScene()
{

}

Scene* TollgateScene::scene()
{
    auto scene = Scene::createWithPhysics();

    /* ΢�������� */
    Vect gravity(0, -0.5f);
    scene->getPhysicsWorld()->setGravity(gravity);

    /* ��������ģʽ */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    //����һ���߽�
    Size visibleSize = Director::getInstance()->getVisibleSize();

    /* 
        ����һ�����ĺ��Ӹ��壬��Ϊ������Ϸ����ı߽磨������Ϸ�ڵ������ܳ���Ļ�� 
        �����ֱ��Ǹ����С�����ʣ���ʵ����һЩԤ����������ݣ������ߺ��
    */
    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);

    /* ����һ���ڵ㣬���ڳ��ظ��壬����������ܲ��뵽��Ϸ���������� */
    auto node = Node::create();
    node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    node->setPhysicsBody(body);
    scene->addChild(node);

    /* ������ */
    auto backgroundLayer = BackgroundLayer::create();
    scene->addChild(backgroundLayer, 0);

    /* ����� */
    auto monsterLayer = MonsterLayer::create();
    scene->addChild(monsterLayer, 1);

    auto layer = TollgateScene::create();
    scene->addChild(layer, 10);

    layer->m_backgroundLayer = backgroundLayer;
    layer->m_monsterLayer = monsterLayer;
    return scene;
}


bool TollgateScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    /* �������� */
    Size visibleSize = Director::getInstance()->getVisibleSize();

    m_player = Player::create();
    m_player->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.85f));
    this->addChild(m_player, 5);

    /* ��������UI */
    createOprUI();

    /* ��ײ���� */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(TollgateScene::onContactBegin, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


    this->schedule(schedule_selector(TollgateScene::logic));
    return true;
}

void TollgateScene::onExit()
{
    Layer::onExit();

    _eventDispatcher->removeEventListenersForTarget(this);
}

void TollgateScene::logic(float dt)
{
    m_backgroundLayer->logic(dt);
    m_monsterLayer->logic(dt);
}

void TollgateScene::createOprUI()
{
    auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("OprUI_1.ExportJson");
    this->addChild(UI);

    /* ��ȡ��ť���� */
    Button* rightBtn = (Button*)Helper::seekWidgetByName(UI, "rightBtn");
    Button* quickMoveBtn = (Button*)Helper::seekWidgetByName(UI, "quickMoveBtn");
    Button* leftBtn = (Button*)Helper::seekWidgetByName(UI, "leftBtn");

    /* ��Ӱ�ť�ص��¼� */
    leftBtn->addTouchEventListener(this, toucheventselector(TollgateScene::moveToLeft));
    rightBtn->addTouchEventListener(this, toucheventselector(TollgateScene::moveToRight));
    quickMoveBtn->addTouchEventListener(this, toucheventselector(TollgateScene::quickMove));

}

void TollgateScene::moveToLeft(Ref* sender, TouchEventType type)
{
    switch (type)
    {
    case TOUCH_EVENT_ENDED:
        m_player->moveToLeft();
        break;

    }
}

void TollgateScene::moveToRight(Ref* sender, TouchEventType type)
{
    switch (type)
    {
    case TOUCH_EVENT_ENDED:
        m_player->moveToRight();
        break;

    }
}

void TollgateScene::quickMove(Ref* sender, TouchEventType type)
{
    switch (type)
    {
    case TOUCH_EVENT_ENDED:
        m_player->quickMove();
        break;

    }
}

bool TollgateScene::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();

    if (nodeA == NULL || nodeB == NULL)
    {
        return true;
    }

    Node* playerNode = NULL;    /* ��Ҷ��� */
    Node* other = NULL;         /* �����ǽ���������� */

    if (nodeA->getTag() == ObjectTag_Player)
    {
        playerNode = nodeA;
        other = nodeB;
    }
    else if (nodeB->getTag() == ObjectTag_Player)
    {
        playerNode = nodeB;
        other = nodeA;
    }
    else
    {
        /* ���������ײ�������У���������Ҷ��󣬾ͺ��ԣ��������� */
        return true;
    }

    Player* player = (Player*)playerNode;

    /* ��ײ����Ե��ݣ�ǽ����+1Ѫ */
    if (other->getTag() == ObjectTag_Border)
    {
        /* ��-1Ѫ�����൱�ڼ�1Ѫ */
        player->beAtked(-1);

        log("player cur HP:%d", player->getiHP());
    }
    else if (other->getTag() == ObjectTag_Monster)
    {
        /* ��ײ��������ݹ�������Խ��в��� */
        Monster* monster = (Monster*)other;

        if (monster->getiAtk() != 0)
        {
            /* ������ң������Ǽ�Ѫ�� */
            player->beAtked(monster->getiAtk());

            /* ��ײ֮�󣬹�����ʧ */
            monster->removeFromParent();
        }
    }
    return true;
}


