#include "BackgroundLayer.h"
#include "ObjectTag.h"
//#include "ObjectTag.h"

BackgroundLayer::BackgroundLayer()
{
}

BackgroundLayer::~BackgroundLayer()
{
}

bool BackgroundLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    /* ����ͼƬ */
    m_bg1 = Sprite::create("background.jpg");
    m_bg1->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    this->addChild(m_bg1);

    m_bg2 = Sprite::create("background.jpg");
    m_bg2->setPosition(Point(visibleSize.width * 0.5f, -visibleSize.height * 0.5f));
    this->addChild(m_bg2);

    /* ������Ե��� */
    auto border = Sprite::create("border.png");
    Size borderSize = border->getContentSize();

    auto border1 = createBorder(Point(borderSize.width * 0.5f, borderSize.height * 0.5f));
    this->addChild(border1);

    auto border2 = createBorder(Point(visibleSize.width - borderSize.width * 0.5f, borderSize.height * 0.5f));
    border2->setFlippedX(true);
    this->addChild(border2);

    auto border3 = createBorder(Point(visibleSize.width * 0.5f, visibleSize.height * 0.15f));
    borderSize = border3->getContentSize();
    border3->setRotation(90.0f);
    this->addChild(border3);

//     border1->setTag(ObjectTag_Border);
//     border2->setTag(ObjectTag_Border);
//     border3->setTag(ObjectTag_Border);
    return true;
}

Sprite* BackgroundLayer::createBorder(Point pos)
{
    auto border = Sprite::create("border.png");

    Size borderSize = border->getContentSize();

    auto body = PhysicsBody::createBox(borderSize);
    body->setDynamic(false);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    border->setPhysicsBody(body);
    border->setPosition(pos);

    border->setTag(ObjectTag_Border);
    return border;
}

void BackgroundLayer::logic(float dt) {
    int posY1 = m_bg1->getPositionY();	// ������ͼ1��Y����
    int posY2 = m_bg2->getPositionY();	// ������ͼ2��Y����

    int iSpeed = 3;	// ��ͼ�����ٶ�

    /* ���ŵ�ͼ���Ϲ��������ŵ�ͼ�����ڵģ�����Ҫһ��������������ֿ�϶�� */
    posY1 += iSpeed;
    posY2 += iSpeed;

    /* ��Ļ�� */
    int iVisibleHeight = Director::getInstance()->getVisibleSize().height;

    /* ����1����ͼ��ȫ�뿪��Ļʱ���õ�2����ͼ��ȫ��������Ļ�ϣ�ͬʱ�õ�1����ͼ�����ڵ�2����ͼ���� */
    if (posY1 > iVisibleHeight * 1.5f) {
        posY2 = iVisibleHeight * 0.5f;
        posY1 = -iVisibleHeight * 0.5f;
    }
    /* ͬ������2����ͼ��ȫ�뿪��Ļʱ���õ�1����ͼ��ȫ��������Ļ�ϣ�ͬʱ�õ�2����ͼ�����ڵ�1����ͼ���� */
    if (posY2 > iVisibleHeight * 1.5f) {
        posY1 = iVisibleHeight * 0.5f;
        posY2 = -iVisibleHeight * 0.5f;
    }

    m_bg1->setPositionY(posY1);
    m_bg2->setPositionY(posY2);
}
