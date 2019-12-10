#include <iostream>
#include <fstream>
#include <string>
#include "PSO.h"
#include "FitnessFunction.h"
#include <time.h>
//�ַ����ָ��
vector<string> split(const string& str, const string& pattern)
{
	vector<string> res;
	if ("" == str)
		return res;

	string strs = str + pattern;

	size_t pos = strs.find(pattern);
	size_t size = strs.size();

	while (pos != string::npos)
	{
		string x = strs.substr(0, pos);
		res.push_back(x);//stoi(x)ת����
		strs = strs.substr(pos + 1, size);
		pos = strs.find(pattern);
	}
	return res;
}
int main()
{
	#pragma region �����㷨����


	// �豸��
	int deviceNum = 4;	

	#pragma region �豸�ߴ�����
	ProblemParas proParas(deviceNum);
	proParas.DeviceSizeArray = new Size[deviceNum];
	ifstream fileIn("Para.txt");
	string line;
	if (fileIn) // �и��ļ�
	{
		getline(fileIn, line);
		vector<string> strSplit = split(line, " ");
		for (int i = 0; i < proParas.DeviceSum; i++)
		{
			vector<string> deviceSizeStr = split(strSplit[i], ",");
			proParas.DeviceSizeArray[i].x = atof(deviceSizeStr[0].c_str());
			proParas.DeviceSizeArray[i].y = atof(deviceSizeStr[1].c_str());
			cout << proParas.DeviceSizeArray[i].x << "," << proParas.DeviceSizeArray[i].y << endl;
		}
	}
	else // û�и��ļ�
	{
		cout << "no such file" << endl;
	}
	#pragma endregion

	#pragma region ����ߴ�
	proParas.WorkshopSize.x = 20.0;
	proParas.WorkshopSize.y = 20.0;
	#pragma endregion

	#pragma region �ɱ��������
	proParas.CostParaArray = new CostPara * [proParas.DeviceSum];
	for (int i = 0; i < proParas.DeviceSum; i++) {
		proParas.CostParaArray[i] = new CostPara[proParas.DeviceSum];
	}
	if (fileIn) // �и��ļ�
	{
		getline(fileIn, line);//��һ��
		for (int i = 0; i < proParas.DeviceSum; i++) {
			getline(fileIn, line);
			cout << line << endl;
			vector<string> strSplit = split(line, " ");
			for (int j = 0; j < proParas.DeviceSum; j++)
			{
				vector<string> costParaStr = split(strSplit[j], ",");
				proParas.CostParaArray[i][j].MatFlow = atof(costParaStr[0].c_str());
				proParas.CostParaArray[i][j].UnitCost = atof(costParaStr[1].c_str());
				cout << proParas.CostParaArray[i][j].MatFlow << 
					"," << proParas.CostParaArray[i][j].UnitCost << endl;
			}
		}
	}
	else // û�и��ļ�
	{
		cout << "no such file" << endl;
	}
	#pragma endregion

	#pragma region PSO����
	int dim = deviceNum * 2;		// ��ά��=�豸��*2
	PSOPara psopara(dim, true);		// 2Ϊ����ά�ȣ�true��ʾ������������
	psopara.particle_num_ = 20;		// ���Ӹ���
	psopara.max_iter_num_ = 300;	// ����������
	psopara.SetDt(1.0);				// ʱ�䲽��
	psopara.SetWstart(0.9);			// ��ʼȨ��
	psopara.SetWend(0.4);			// ����Ȩ��
	psopara.SetC1(1.49445);			// ���ٶ�����1
	psopara.SetC2(1.49445);			// ���ٶ�����2
	psopara.SetLowBound(0);			// position������Χ����
	psopara.SetUpBound(20);			// position������Χ����
	psopara.problemParas = proParas;// ��������Ĳ���
	#pragma endregion


	#pragma endregion

	PSOOptimizer psooptimizer(&psopara, FitnessFunction);//���캯��

	std::srand((unsigned int)time(0));
	psooptimizer.InitialAllParticles();//��ʼ����������
	double fitness = psooptimizer.all_best_fitness_;
	double* result = new double[psooptimizer.max_iter_num_];//��ʼ���洢ÿһ���������ӵ�����

	//������������
	for (int i = 0; i < psooptimizer.max_iter_num_; i++)
	{
		psooptimizer.UpdateAllParticles();//�����������ӵ�λ�ú��ٶ�
		result[i] = psooptimizer.all_best_fitness_;//��¼����һ������������
		cout << "��" << i << "�ε��������" << endl;
		for (int j = 0; j < dim; j+=2) {
			cout << "X" << (j + 1) / 2 << ": "<< psooptimizer.all_best_position_[j] << ", " << "Y" << (j + 1) / 2 << ": " << psooptimizer.all_best_position_[j + 1] << endl;
		}
		cout << ", fitness = " << result[i] << std::endl;
	}

	system("pause");
}