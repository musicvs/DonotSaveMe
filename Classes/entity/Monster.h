/*
	�ļ�����    Monster.h
	�衡����  
	�����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

	�������ڣ�  2014.4.8
*/
#ifndef Monster_H
#define Monster_H

#include "cocos2d.h"
USING_NS_CC;

class Monster : public Node 
{
public:
	Monster();
	~Monster();
    static Monster* create(int ID);
    bool init(int ID);

    /* ���뵽��ǰ�������������� */
    void joinToWorld(Node* parent);

    CC_SYNTHESIZE(int, m_ID, ID);
    CC_SYNTHESIZE(int, m_iPosX, iPosX);
    CC_SYNTHESIZE(int, m_iPosY, iPosY);
    CC_SYNTHESIZE(int, m_iAtk, iAtk);
    CC_SYNTHESIZE(float, m_fShowTime, fShowTime);
    CC_SYNTHESIZE(Value, m_sModelPath, sModelPath);
};

#endif