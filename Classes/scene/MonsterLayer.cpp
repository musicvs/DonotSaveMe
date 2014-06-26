#include "MonsterLayer.h"
#include "entity\Monster.h"

MonsterLayer::MonsterLayer()
{
    m_fTimeCounter = 0;
}

MonsterLayer::~MonsterLayer()
{
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("monster.plist");
}

bool MonsterLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monster.plist");

    /* ���عؿ��Ĺ������� */
    loadMonstersFromTmxConf();
    return true;
}

void MonsterLayer::loadMonstersFromTmxConf()
{
    /* ���ص�ͼ */
    TMXTiledMap* map = TMXTiledMap::create("tg1.tmx");
    this->addChild(map);

    /* ���ع�����������ж��� */
    TMXObjectGroup* objGroup = map->getObjectGroup("monster");
    ValueVector objects = objGroup->getObjects();

    /* �������ж��� */
    for (const auto v : objects)
    {
        const ValueMap dict = v.asValueMap();

        int id = dict.at("id").asInt();
        float fShowTime = dict.at("showTime").asFloat();
        int iPosX = dict.at("x").asInt();
        int iPosY = dict.at("y").asInt();

        /* ����������󣬲��������� */
        Monster* monster = Monster::create(id);
        monster->setID(id);
        monster->setfShowTime(fShowTime);
        monster->setiPosX(iPosX);
        monster->setiPosY(iPosY);

        /* ���������� */
        m_monsterVec.pushBack(monster);
    }
}

void MonsterLayer::logic(float dt)
{
    /* ��ʱ */
    m_fTimeCounter += dt;

    /* ��¼���γ����Ĺ��� */
    Vector<Monster*> deleteVec;

    /* �ôﵽ����ʱ��Ĺ�����ӵ��������� */
    for (auto monster : m_monsterVec)
    {
        /* �ﵽʱ�䣬���Գ����� */
        if (m_fTimeCounter >= monster->getfShowTime())
        {
            monster->joinToWorld(this);

            /* ��¼���γ����Ĺ��Ȼ��ɾ���� */
            deleteVec.pushBack(monster);
        }
    }

    /* ɾ���Ѿ���ӵ���������Ĺ�������ظ����� */
    for (auto monster : deleteVec)
    {
        m_monsterVec.eraseObject(monster, false);
    }
}
