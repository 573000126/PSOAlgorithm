#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "PSO.h"
#include "FitnessFunction.h"
//��������txt
//void SaveLayoutResults(PSOOptimizer psooptimizer, double* result) {
//	ofstream OutFile;
//	//��ÿһ�ε���Ӧ��ֵ#include <time.h>
//
//
//
//	OutFile.open("../../IterateResult.txt");
//	for (int i = 0; i < psooptimizer.max_iter_num_; i++)
//	{
//		string line = to_string(1.0 / result[i]) + "\n";
//		OutFile << line;
//	}
//	OutFile.close();
//	//�����Ĳ��ֽ��
//	OutFile.open("../../LayoutResult.txt");
//	for (int i = 0; i < psooptimizer.dim_; i += 2) {
//		string line = to_string(psooptimizer.all_best_position_[i]) + "," + to_string(psooptimizer.all_best_position_[i + 1]) + "\n";
//		OutFile << line;
//	}
//	OutFile.close();
//}
int main()
{
	//������ز���
	int deviceNum = 6;	
	ProblemParas proParas(deviceNum);




	#pragma region ����PSO����
	int dim = deviceNum * 2;				// ��ά��=�豸��*2
	PSOPara psopara(dim);					// dim�Ǳ���ά��
	psopara.mesh_div_count = 4;				// ���񻮷���Ŀ
	psopara.problemParas = proParas;		// ��������Ĳ���
	psopara.particle_num_ = 100;			// ���Ӹ���
	psopara.max_iter_num_ = 2000;			// ����������
	psopara.fitness_count_ = 2;				// ��Ӧ����Ŀ
	psopara.archive_max_count = 200;		// archive����������Ŀ
	psopara.SetDt(1.0);						// ʱ�䲽��
	psopara.SetWstart(0.9);					// ��ʼȨ��
	psopara.SetWend(0.4);					// ����Ȩ��
	psopara.SetC1(1.49445);					// ���ٶ�����1
	psopara.SetC2(1.49445);					// ���ٶ�����2
	psopara.SetLowBound(0, 0);				// position��������Χ����
	psopara.SetUpBound(proParas.WorkshopSize.x, proParas.WorkshopSize.y);// position��������Χ����
	#pragma endregion

	#pragma region ����PSO�㷨����������

	#pragma region ��ʼ��

	PSOOptimizer psooptimizer(&psopara, FitnessFunction);//���캯��

	std::srand((unsigned int)time(0));


	psooptimizer.InitialAllParticles();//��ʼ����������
	psooptimizer.InitialArchiveList();//��ʼ��Archive�浵
	psooptimizer.InitGbest();//��ʼ��ȫ������

	#pragma endregion

	//������������
	ofstream OutFile;
	//��ÿһ�ε���Ӧ��ֵ
	OutFile.open("../archiveList.txt");
	for (int i = 0; i < psooptimizer.max_iter_num_; i++)
	{
		psooptimizer.UpdateAllParticles();//�����������ӵ�λ�ú��ٶ�
		psooptimizer.UpdatePbest();//����pbest
		psooptimizer.UpdateArchiveList();//�����ⲿ�浵����
		psooptimizer.UpdateGbest();//����gbest

		//�洢ÿ�ε�Archive����
		OutFile << to_string(i) + "\n";
		for (auto it = psooptimizer.archive_list.begin(); it != psooptimizer.archive_list.end(); it++)
		{
			string line = to_string(it->fitness_[0]) + ", " + to_string(it->fitness_[1]) + "\n";
			OutFile << line;
		}
		OutFile << "\n";
	}
	OutFile.close();
	//���Ľ���浽txt��(���ֽ����ÿһ�ε�������Ӧ��ֵ��
	//SaveLayoutResults(psooptimizer, result);

	#pragma endregion

	system("pause");
}
