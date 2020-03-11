#pragma once
//
//  CAstar.h
//  Astar
//
//  Created by xujw on 15/4/9.
//  Copyright (c) 2015�� xujw. All rights reserved.
//
/*
    F:·������ = g+h
    G:��һ����ӵĻ���
    H:��ǰ���ӵ�Ŀ����ӵĹ��㻨��

    ����������һ����Ϊ10��б����һ����Ϊ14���Է������
    �����ӿ���Ϊ10 �Խ���Ϊ14
 */
#ifndef __Astar__CAstar__
#define __Astar__CAstar__

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

enum class AType
{
    ATYPE_UNKNOWN,
    ATYPE_CLOSED,
    ATYPE_OPENED,
    ATYPE_BARRIER   //�ϰ�
};

class APoint
{
public:
    APoint();
    ~APoint();
    int rowIndex;
    int colIndex;
    double x;
    double y;
    AType type;   //����:�ϰ��������б����ر��б�
    double f;  //f = g+h
    double g;
    double h;
    APoint* parent;
    bool operator == (const APoint& po)
    {
        if (x == po.x && y == po.y)
        {
            return true;
        }
        return false;
    }
    double CalcuPointDist(const APoint& point)
    {
        return abs(this->y - point.y) + abs(this->x - point.x);
    }
    void resetAPoint()
    {
        f = g = h = 0;
        type = AType::ATYPE_UNKNOWN;
        parent = nullptr;
    }
};

class CAstar
{
public:
    vector<APoint*> _openList;      //�����б�
    vector<APoint*> _closeList;     //�ر��б�
    vector<APoint*> _neighbourList; //�ܱ߽ڵ�
    APoint* _endPoint;
    APoint* _curPoint;
    vector< vector<APoint*> > _allPoints;
    CAstar();
    ~CAstar();
    double CalcuPathLength(APoint* point);
    APoint* findWay(int beginRowIndex, int beginColIndex, int endRowIndex, int endColIndex);
    void resetAStar();
    //    APoint* findWay(int beginX,int beginY,int endX,int endY);
private:
    int getF(APoint* point);
    int getH(APoint* point);
    vector<APoint*> getNeighboringPoint(APoint* point);
};




#endif /* defined(__Astar__CAstar__) */