#pragma once
#include <iostream>
#include <vector>
using namespace std;
//��ʾһ������
struct Vector2
{
public:
	double x;
	double y;
};
//�豸����
enum DeviceTypeEnum
{
	HighBayWarehouse,
	DenseWarehouse,
	MultiWarehouse,

	StraightConveryer,
	CentringConveyor,
	AlignConveyor,
	CurveConveyor,
	SpiralConveyor,
	LiftingConveyor,

	LiftingTransfer,
	UniversalWheelTransfer,

	RGVSys,
};
//ÿ���豸�Ķ��ز���
struct DeviceType
{
	DeviceTypeEnum ypeName;//�豸������
	vector<DeviceType> adjTypes;//�ڽ��豸������
	int adjLowNum;//�豸�ڽ��豸��Ŀ�½�
	int adjUpNum;//�豸�ڽ��豸��Ŀ�Ͻ�
};
//�豸����
enum DeviceDirect
{
	Up,
	Down,
	Left,
	Right
};
//�����豸�Ĳ���
class DevicePara
{
public:
	int ID;				//�豸ID
	DeviceType type;	//�豸������ز��� 
	double length;		//�豸����
	double width;		//�豸���
	double axisX;		//�豸X����
	double axisY;		//�豸Y����
	DeviceDirect direct;//�豸����

	vector<Vector2> adjPoints;//�豸�ڽӵ�λ������(�����豸��С��������㣩

};
