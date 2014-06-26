#include "Monster.h"
#include "scene\ObjectTag.h"
#include "json\writer.h"
#include "json\reader.h"
Monster::Monster()
{
}

Monster::~Monster()
{
}

Monster* Monster::create(int ID)
{
    auto monster = new Monster();
    
    if(monster && monster->init(ID)) 
    {
    	monster->autorelease();
    }
    else
    {
    	CC_SAFE_DELETE(monster);
    }
    
    return monster;
}

bool Monster::init(int ID)
{
    this->m_ID = ID;

    /* ----------- ��ȡ���������ļ� ------------ */

    /* ��ȡ�����ļ��ַ������� */
    std::string sData = FileUtils::getInstance()->getStringFromFile("monsterConf.plist");

    /* ���ڽ���Json */
    Json::Reader reader;
    
    /* ����Json��ĸ��ڵ� */
    Json::Value root;

    /* ��ʼ���� */
    if (!reader.parse(sData, root, false))
    {
        return false;
    }

    /* ��������ڵ���һ�����飬�������飬�ҵ�����Ҫ��ID */
    int size = root.size();
    for (int i = 0; i < size; ++i)
    {
        int id = root[i]["id"].asInt();

        if (id == ID)
        {
            m_sModelPath = root[i]["model"].asCString();
            m_iAtk = root[i]["atk"].asInt();
            break;
        }
    }

    return true;
}

void Monster::joinToWorld(Node* parent)
{
    Sprite* sp = Sprite::createWithSpriteFrameName(m_sModelPath.asString().c_str());

    /* �������� */
    PhysicsBody* body = PhysicsBody::createBox(sp->getContentSize());
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001

    /* ������� */
    sp->setPosition(Point(sp->getContentSize().width * 0.5f, sp->getContentSize().height * 0.5f));

    /* ������ΪMonster�ı��֣���ӵ�Monster���� */
    this->addChild(sp);

    /* ���ù���Tag���� */
    this->setTag(ObjectTag_Monster);

    /* ������ΪMonster�ı��֣�Monster����û�д�С������Ҫ����һ�´�С */
    this->setContentSize(sp->getContentSize());

    /* ������ӵ�Monster���������Ǿ������� */
    this->setPhysicsBody(body);

    /* �������� */
    this->setPosition(Point(getiPosX(), getiPosY()));

    /* Monster���뵽�������� */
    parent->addChild(this);

}

