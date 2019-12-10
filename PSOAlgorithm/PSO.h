#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "ProblemParas.h"

// ��Ӧ����Խ��Խ�û���ԽСԽ��
//#define MINIMIZE_FITNESS
#define MAXIMIZE_FITNESS

struct PSOPara
{
	int dim_;									// ����ά�ȣ�position��velocity��ά�ȣ�
	int particle_num_;							// ���Ӹ���
	int max_iter_num_;							// ����������

	double* dt_ = nullptr;						// ʱ�䲽��
	double* wstart_ = nullptr;					// ��ʼȨ��
	double* wend_ = nullptr;					// ��ֹȨ��
	double* C1_ = nullptr;						// ���ٶ�����1
	double* C2_ = nullptr;						// ���ٶ�����2

	double* upper_bound_ = nullptr;				// position������Χ����
	double* lower_bound_ = nullptr;				// position������Χ����
	double* range_interval_ = nullptr;			// position�������䳤��

	int results_dim_ = 0;						// results��ά��

	ProblemParas problemParas;					//�����Ӷ�Ӧ����������
	PSOPara() {}

	PSOPara(int dim, bool hasBound = false)
	{
		dim_ = dim;

		dt_ = new double[dim_];
		wstart_ = new double[dim_];
		wend_ = new double[dim_];
		C1_ = new double[dim_];
		C2_ = new double[dim_];
		if (hasBound)
		{
			upper_bound_ = new double[dim_];
			lower_bound_ = new double[dim_];
			range_interval_ = new double[dim_];
		}
		ProblemParas problemParas();
	}

	// �����������ͷŶ��ڴ�
	~PSOPara()
	{
		if (upper_bound_) { delete[]upper_bound_; }
		if (lower_bound_) { delete[]lower_bound_; }
		if (range_interval_) { delete[]range_interval_; }
		if (dt_) { delete[]dt_; }
		if (wstart_) { delete[]wstart_; }
		if (wend_) { delete[]wend_; }
		if (C1_) { delete[]C1_; }
		if (C2_) { delete[]C2_; }
	}

	// ��������������ز���
	void SetProblemParas(ProblemParas paras) {
		problemParas = paras;
	}

	// ����ʱ�䲽��
	void SetDt(double stepLength) {
		for (int i = 0; i < dim_; i++) {
			dt_[i] = stepLength;
		}
	}

	// ����wstart_
	void SetWstart(double startWeight) {
		for (int i = 0; i < dim_; i++) {
			wstart_[i] = startWeight;
		}
	}

	// ����wend_
	void SetWend(double endWeight) {
		for (int i = 0; i < dim_; i++) {
			wend_[i] = endWeight;
		}
	}

	// ����C1
	void SetC1(double c1) {
		for (int i = 0; i < dim_; i++) {
			C1_[i] = c1;
		}
	}

	// ����C2
	void SetC2(double c2) {
		for (int i = 0; i < dim_; i++) {
			C2_[i] = c2;
		}
	}

	// ����low_bound_
	void SetLowBound(double lowBound) {
		for (int i = 0; i < dim_; i++) {
			lower_bound_[i] = lowBound;
		}
	}

	// ����upper_bound_
	void SetUpBound(double upBound) {
		for (int i = 0; i < dim_; i++) {
			upper_bound_[i] = upBound;
		}
	}
};


//���ӽṹ��
struct Particle
{
	int dim_;							// ����ά�ȣ�position��velocity��ά�ȣ�
	double fitness_;
	double* position_ = nullptr;
	double* velocity_ = nullptr;

	double* best_position_ = nullptr;
	double best_fitness_;
	double* results_ = nullptr;			// һЩ��Ҫ������Ľ��
	int results_dim_ = 0;				// results_��ά��

	Particle() {}

	~Particle()
	{
		if (position_) { delete[]position_; }
		if (velocity_) { delete[]velocity_; }
		if (best_position_) { delete[]best_position_; }
		if (results_) { delete[]results_; }
	}

	Particle(int dim, double* position, double* velocity, double* best_position, double best_fitness);
};

typedef double(*ComputeFitness)(Particle& particle, ProblemParas proParas);

class PSOOptimizer
{
public:
	int particle_num_;					// ���Ӹ���
	int max_iter_num_;					// ����������
	int curr_iter_;						// ��ǰ��������

	int dim_;							// ����ά�ȣ�position��velocity��ά�ȣ�

	Particle* particles_ = nullptr;		// ��������

	double* upper_bound_ = nullptr;					// position������Χ����
	double* lower_bound_ = nullptr;					// position������Χ����
	double* range_interval_ = nullptr;				// position�������䳤��

	double* dt_ = nullptr;							// ʱ�䲽��
	double* wstart_ = nullptr;						// ��ʼȨ��
	double* wend_ = nullptr;						// ��ֹȨ��
	double* w_ = nullptr;							// ��ǰ����Ȩ��
	double* C1_ = nullptr;							// ���ٶ�����
	double* C2_ = nullptr;							// ���ٶ�����

	double all_best_fitness_;						// ȫ���������ӵ���Ӧ��ֵ
	double* all_best_position_ = nullptr;			// ȫ���������ӵ�poistion
	double* results_ = nullptr;						// һЩ��Ҫ������Ľ��
	int results_dim_ = 0;							// results��ά��

	ProblemParas problemParas;						// �����������

	ComputeFitness fitness_fun_ = nullptr;			// ��Ӧ�Ⱥ���

public:
	// Ĭ�Ϲ��캯��
	PSOOptimizer() {}

	// ���캯��
	PSOOptimizer(PSOPara* pso_para, ComputeFitness fitness_fun);

	// ��������
	~PSOOptimizer();

	// ��ʼ���������Ӳ���
	void InitialAllParticles();

	// ��ʼ����i�����Ӳ���
	void InitialParticle(int i);

	// ��ȡ˫�����������Ĭ�Ͼ���Ϊ0.0001��
	double GetDoubleRand(int N = 9999);

	// ��������ӵ���Ӧ��ֵ
	double GetFitness(Particle& particle);

	// �����������Ӳ���
	void UpdateAllParticles();

	// ���µ�i������
	void UpdateParticle(int i);

	// ��ȡ��ǰ������Ȩ��
	void GetInertialWeight();

};