#pragma once


#include <vector>
#include "Random.h"
#include <iostream>

class OneFactorAnalysis
{
	int size;
	int number;
	std::vector<float> coef;
	
	std::vector<std::vector<float>> table;
	std::vector<float> avgColumn;
	std::vector<float> Si2Vector;
	float S02var;
	float S2var;
	float SA2var;

	void countAvg();
	void Si2();

	void S02();
	void S2();
	void SA2();



public:

	void callCalculations();
	void showResult();

	OneFactorAnalysis(int _size, int _number);
	void fillTable();
	void fillColumn(float coef, int columnNumber);
	


};

