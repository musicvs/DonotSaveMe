/*
    �ļ�����    Player.h
    �衡����
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

    �������ڣ�  2014.4.7
*/
#ifndef Player_H
#define Player_H

#include "cocos2d.h"
USING_NS_CC;

class Player : public Node
{
public:
    Player();
    ~Player();
    CREATE_FUNC(Player);
    virtual bool init();

    void moveToRight();
    void moveToLeft();
    void quickMove();

    void logic(float dt);

    /* ���˺����������� */
    void beAtked(int iValue);

private:
    CC_SYNTHESIZE(int, m_iHP, iHP);

    /* ���˺� */
    void hurt(int iValue);

    /* ���� */
    void cure(int iValue);
};

#endif