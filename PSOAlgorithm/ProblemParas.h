#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Size {
	double x;
	double y;
};
//�ɱ�������ز���
struct CostPara {
	double MatFlow;		//��������
	double UnitCost;	//��λ�������ĳɱ�
};
struct ProblemParas
{	
	int DeviceSum;					//�豸����
	Size* DeviceSizeArray;			//�豸�ߴ�����

	Size WorkshopSize;				//����ߴ�

	CostPara** CostParaArray;			//�ɱ������������

	ProblemParas() {}
	ProblemParas(int deviceNum)
	{
		DeviceSum = deviceNum;
	}
};
