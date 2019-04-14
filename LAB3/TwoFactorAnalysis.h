#pragma once

#include <vector>
#include <iostream>

#include "Random.h"

class TwoFactorAnalysis
{
private:
	
	int size;
	int number;
	int m;
	int k;
	std::vector<std::vector<std::vector<double>>> table;
	std::vector<std::vector<float>> coef;


	double Q1var;
	double Q2var;
	double Q3var;
	double Q4var;
	double Q5var;
	
	float S02var;
	float SA2var;
	float SB2var;
	float SAB2var;

	void Q1();
	void Q2();
	void Q3();
	void Q4();
	void Q5();

	void S02();
	void SA2();
	void SB2();
	void SAB2();

public:

	TwoFactorAnalysis(int _size, int _number) : size(_size), number(_number)
	{
		m = 4;
		k = 5;
		TwoFactorAnalysis::coef.resize(m, std::vector<float>(k));
		
		coef.at(0) = { 1.0, 3.5, 3.8, 1.4, 2 };
		coef.at(1) = { 1.0, 2.5, 2.8, 2.4, 3 };
		coef.at(2) = { 1.0, 1.5, 1.8, 3.4, 4 };
		coef.at(3) = { 1.0, 0.5, 0.8, 4.4, 5 };
	}

	void fillTable();
	void callCalculations();
	void showResult();
};

