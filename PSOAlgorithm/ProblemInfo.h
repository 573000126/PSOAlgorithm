#pragma once
#include <iostream>
using namespace std;

struct ProblemParas
{
	int DeviceSum;				//�豸����
	double* DeviceDist;			//�豸֮��ľ�������
	double* DeviceLengthArray;	//�豸�ĳ�������
	double* DeviceWidthArray;	//�豸�Ŀ������
	double WorkshopLength;		//���䳤��
	double WorkshopWidth;		//������
	double* DeviceSquareArray;	//�豸�������
	double* UnitCostArray;		//�豸֮�䵥λ������������˳ɱ�����
	int* TotalMatFlowArray;		//������������

	int* AdjRankArray;			//�ڽӵȼ�����
};
