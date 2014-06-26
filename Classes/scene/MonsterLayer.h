/*
	�ļ�����    MonsterLayer.h
	�衡����  
	�����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

	�������ڣ�  2014.4.8
*/
#ifndef MonsterLayer_H
#define MonsterLayer_H

#include "cocos2d.h"
USING_NS_CC;

class Monster;
class MonsterLayer : public Layer 
{
public:
	MonsterLayer();
	~MonsterLayer();
	CREATE_FUNC(MonsterLayer);
	virtual bool init();

    void logic(float dt);
private:
    /* �������ļ��м��ع������� */
    void loadMonstersFromTmxConf();

    /* ������м���Ҫ�����Ĺ������ */
    Vector<Monster*> m_monsterVec;

    /* ��ʱ�� */
    float m_fTimeCounter;
};

#endif