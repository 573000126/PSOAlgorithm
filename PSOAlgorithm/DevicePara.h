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
	Vector2(){}
	Vector2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
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
};
//�ڽӵ�ṹ
struct AdjPoint
{
	int index;//�±�
	InoutType inoutType;//���������
	Vector2 pos;		//����ڵ�λ��
};
//�豸����˳ʱ��ת����ΪĬ��/90/180/270��
enum DeviceDirect
{
	Default,
	Rotate90,
	Rotate180,
	Rotate270
};
//�豸�����(��0��5��������
enum DeviceRelation
{
	X,U,O,I,E,A
};
//�����豸�Ĳ���
class DevicePara
{
public:
	int ID;				//�豸ID
	//DeviceType type;	//�豸������ز��� 
	double workSpeed;	//�ӹ�/����1��λ���ϵ�ʱ��
	Vector2 size;		//�豸�ߴ磨�ֱ���x���y��ĳ��ȣ�
	Vector2 axis;		//�豸����
	DeviceDirect direct;//�豸����

	//����ڵ�����飨��Ӱ�������ߵĲ��֣�
	vector<AdjPoint> adjPointsIn;//���
	vector<AdjPoint> adjPointsOut;//����
	vector<AdjPoint> usableAdjPointsIn;
	vector<AdjPoint> usableAdjPointsOut;
	DevicePara() {}
};
//��������������ݽṹ
struct PointLink
{
public:
	int device1Index;
	int device1PointIndex;
	int device2Index;
	int device2PointIndex;
	PointLink() {}
	PointLink(int device1Index, int device1PointIndex, int device2Index, int device2PointIndex)
	{
		this->device1Index = device1Index;
		this->device1PointIndex = device1PointIndex;
		this->device2Index = device2Index;
		this->device2PointIndex = device2PointIndex;
	}
};

//������Ϣ
struct CargoType
{
	string cargoName;	//������
	int deviceSum;		//�������豸����
	int* deviceList;	//�豸����
	double totalVolume;	//һ��ʱ�����������
};

