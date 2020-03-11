//
//  CAstar.cpp
//  Astar
//
//  Created by xujw on 15/4/9.
//  Copyright (c) 2015�� xujw. All rights reserved.
//
//  ����������һ����Ϊ10��б����һ����Ϊ14���Է������
//  �����ӿ���Ϊ10 �Խ���Ϊ14
#pragma once
#include "AStar.h"
#include <algorithm>
//�Զ���������
bool mySort(const APoint* p1, const APoint* p2)
{
    return p1->f < p2->f;
}

APoint::APoint() :x(0)
, y(0)
, h(0)
, f(0)
, g(0)
, parent(nullptr)
, type(AType::ATYPE_UNKNOWN)
{
}
APoint::~APoint()
{
}


#pragma mark------CAstar-------

CAstar::CAstar() :_endPoint(nullptr)
, _curPoint(nullptr)
{
}

CAstar::~CAstar()
{
    _openList.clear();
    _closeList.clear();
    _neighbourList.clear();
    _allPoints.clear();
}
//����һ��·�����ܳ���
double CAstar::CalcuPathLength(APoint* point)
{
    double length = 0.0;
    while (point->parent)
    {
        length += point->CalcuPointDist(*(point->parent));
        point = point->parent;
    }
    return length;
}
void CAstar::resetAStar()
{
    for (int i = 0; i < _allPoints.size(); i++)
    {
        for (int j = 0; j < _allPoints[i].size(); j++)
        {
            _allPoints[i][j]->resetAPoint();
        }
    }
    _openList.clear();
    _closeList.clear();
    _neighbourList.clear();
}
APoint* CAstar::findWay(int beginRowIndex, int beginColIndex, int endRowIndex, int endColIndex)
{
    _endPoint = _allPoints[endRowIndex][endColIndex];
    APoint* beginPoint = _allPoints[beginRowIndex][beginColIndex];
    if (_endPoint->type == AType::ATYPE_BARRIER)
    {
        cout << "�յ����ϰ�" << endl;
        return nullptr;
    }
    if (*_endPoint == *beginPoint)
    {
        cout << "��ʼ����ͬ" << endl;
        return nullptr;
    }

    _openList.push_back(beginPoint);
    beginPoint->type = AType::ATYPE_OPENED;
    beginPoint->f = getF(beginPoint);
    //---------
    do
    {
        //��ȡ��Сֵ�Ľڵ�
        _curPoint = _openList[0];
        _openList.erase(_openList.begin());
        _curPoint->type = AType::ATYPE_CLOSED;
        _closeList.push_back(_curPoint);

        if (*_curPoint == *_endPoint)
        {
            //cout << "have find way" << endl;
            return _curPoint;
        }
        //��ȡ���ڵĽڵ�
        vector<APoint*> neVec = getNeighboringPoint(_curPoint);
        for (int i = 0; i < neVec.size(); i++)
        {
            auto tmpoint = neVec[i];
            if (tmpoint->type == AType::ATYPE_CLOSED)
            {
                continue;
            }
            //�Ƿ��ڿ����б���
            if (tmpoint->type != AType::ATYPE_OPENED)
            {
                tmpoint->parent = _curPoint;
                tmpoint->g = _curPoint->g + tmpoint->CalcuPointDist(*_curPoint);////////////
                //����Hֵ
                tmpoint->h = getH(tmpoint);
                //���ӵ������б���
                _openList.push_back(tmpoint);
                tmpoint->type = AType::ATYPE_OPENED;
            }
            else
            {
                //�Ѿ��ڿ����б���
                if (tmpoint->h < _curPoint->h)
                {
                    tmpoint->parent = _curPoint;
                    tmpoint->g = _curPoint->g + tmpoint->CalcuPointDist(*_curPoint);////////////
                }
            }
        }
        //���� Fֵ��С������ǰ��
        sort(_openList.begin(), _openList.end(), mySort);

    } while (_openList.size() > 0);


    cout << "---can not find way---" << endl;

    return nullptr;
}
//�õ�F=G+H
int CAstar::getF(APoint* point)
{
    return (point->g + getH(point));
}
//����H
int CAstar::getH(APoint* point)
{
    //�����ٳ��н������㷨
    return abs(_endPoint->y - point->y) + abs(_endPoint->x - point->x);
}

vector<APoint*> CAstar::getNeighboringPoint(APoint* point)
{
    _neighbourList.clear();
    if (point->rowIndex < _allPoints.size() - 1)
    {
        if (_allPoints[point->rowIndex + 1][point->colIndex]->type != AType::ATYPE_BARRIER)
        {
            _neighbourList.push_back(_allPoints[point->rowIndex + 1][point->colIndex]);
        }
    }
    if (point->rowIndex > 0)
    {
        if (_allPoints[point->rowIndex - 1][point->colIndex]->type != AType::ATYPE_BARRIER)
        {
            _neighbourList.push_back(_allPoints[point->rowIndex - 1][point->colIndex]);
        }
    }
    if (point->colIndex < _allPoints[0].size() - 1)
    {
        if (_allPoints[point->rowIndex][point->colIndex + 1]->type != AType::ATYPE_BARRIER)
        {
            _neighbourList.push_back(_allPoints[point->rowIndex][point->colIndex + 1]);
        }
    }
    if (point->colIndex > 0)
    {
        if (_allPoints[point->rowIndex][point->colIndex - 1]->type != AType::ATYPE_BARRIER)
        {
            _neighbourList.push_back(_allPoints[point->rowIndex][point->colIndex - 1]);
        }
    }

    return _neighbourList;
}