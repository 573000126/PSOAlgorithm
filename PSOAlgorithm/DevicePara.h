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
//�豸���ࣨ��ʱ��
enum DeviceTypeEnum
{
	//�����
	HighBayWarehouse,
	DenseWarehouse,
	MultiWarehouse,

	//���ͻ�
	StraightConveryer,
	CentringConveyor,
	AlignConveyor,
	CurveConveyor,
	SpiralConveyor,
	LiftingConveyor,

	//�����������֡������е��
	LiftingTransfer,
	UniversalWheelTransfer,
	FourJointArm,

	//RGV
	RGVSys,
};
//ÿ���豸�Ķ��ز���
struct DeviceType
{
	DeviceTypeEnum typeName;//�豸������
	vector<DeviceType> adjTypes;//�ڽ��豸������
	int adjLowNum;//�豸�ڽ��豸��Ŀ�½�
	int adjUpNum;//�豸�ڽ��豸��Ŀ�Ͻ�
};
//����� ����
enum InoutType
{
	In,			//���
	Out,		//����
	Inout		//�����
};
//�ڽӵ�ṹ
struct AdjPoint
{
	InoutType inoutType;//���������
	Vector2 pos;//����ڵ�λ��
};
//�豸����
enum DeviceDirect
{
	Up,			//��
	Down,		//��
	Left,		//��
	Right		//��
};
//�����豸�Ĳ���
class DevicePara
{
public:
	int ID;				//�豸ID
	//DeviceType type;	//�豸������ز��� 
	double workSpeed;	//����/����Ч�ʣ�xx�룬������߼ӹ�һ����λ���ϣ�
	double length;		//�豸����
	double width;		//�豸���
	Vector2 axis;		//�豸����
	DeviceDirect direct;//�豸����

	//�ĸ�����ĳ�������飨��Ӱ�������ߵĲ��֣�
	vector<AdjPoint> leftAdjPoints;
	vector<AdjPoint> rightAdjPoints;
	vector<AdjPoint> upAdjPoints;
	vector<AdjPoint> downAdjPoints;

};
