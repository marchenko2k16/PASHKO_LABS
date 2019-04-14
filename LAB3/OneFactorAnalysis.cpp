#include "OneFactorAnalysis.h"


void OneFactorAnalysis::Si2()
{
	for (int i = 0; i < 5; ++i)
	{
		float si2 = 0;
		for (int j = 0; j < size; ++j)
		{
			si2 += pow(OneFactorAnalysis::table.at(i).at(j) - OneFactorAnalysis::avgColumn.at(i), 2);
		}
		OneFactorAnalysis::Si2Vector.push_back(( 1.0 / (OneFactorAnalysis::size - 1)) * si2 );
	}

}

void OneFactorAnalysis::S02()
{
	float count = 0;
	for (int i = 0; i < 5; ++i)
	{
		float innerCount = 0;
		for (int innerI = 0; innerI < 5; ++innerI)
		{
			for (int innerJ = 0; innerJ< OneFactorAnalysis::size; ++innerJ)
			{
				innerCount += pow(OneFactorAnalysis::table.at(innerI).at(innerJ) - avgColumn.at(innerI), 2);
			}
		}
		count += 1.0 /( 5 * (OneFactorAnalysis::size - 1.0)) * OneFactorAnalysis::Si2Vector.at(i) * innerCount;
	}
	OneFactorAnalysis::S02var = ( 1.0 / 5 ) * count;
}



void OneFactorAnalysis::S2()
{
	float leftCount = 0;
	for (int innerI = 0; innerI < 5; ++innerI)
	{
		for (int innerJ = 0; innerJ < OneFactorAnalysis::size; ++innerJ)
		{
			leftCount += pow(OneFactorAnalysis::table.at(innerI).at(innerJ),2);
		}
	}

	float rightCount = 0;
	for (int innerI = 0; innerI < 5; ++innerI)
	{
		for (int innerJ = 0; innerJ < OneFactorAnalysis::size; ++innerJ)
		{
			rightCount += OneFactorAnalysis::table.at(innerI).at(innerJ);
		}
	}

	S2var = 1.0 / (5 * OneFactorAnalysis::size - 1) * (leftCount -  1.0 / (5.0 * OneFactorAnalysis::size) * pow(rightCount, 2));
}



void OneFactorAnalysis::SA2()
{
	float avgOfAvg = 0;
	for (int i = 0; i < 5; ++i)
	{
		avgOfAvg += avgColumn.at(i);
	}
	avgOfAvg /= 5;

	float count = 0;
	for (int i = 0; i < 5; ++i)
	{
		count += pow(avgColumn.at(i) - avgOfAvg, 2);
	}
	SA2var = OneFactorAnalysis::size / (5 - 1) * count;
}


void OneFactorAnalysis::countAvg()
{
	for (int i = 0; i < 5; ++i)
	{
		float avg = 0;
		for (int j = 0; j < size; ++j)
		{
			avg += OneFactorAnalysis::table.at(i).at(j);
		}
		OneFactorAnalysis::avgColumn.push_back(avg / size);
	}
}


void OneFactorAnalysis::fillTable()
{
	OneFactorAnalysis::table.resize(1000, std::vector<float>(1000));

	for (int i = 0; i < 5; ++i)
	{
		fillColumn(OneFactorAnalysis::coef.at(i), i);
	}
}


void OneFactorAnalysis::fillColumn(float coef, int columnNumber)
{
	for (int i = 0; i < OneFactorAnalysis::size; ++i)
	{
		OneFactorAnalysis::table.at(columnNumber).at(i) = coef * OneFactorAnalysis::number + Random::random(0, 1);
	}
}

void OneFactorAnalysis::callCalculations()
{
	countAvg();
	Si2();
	S02();
	S2();
	SA2();
}

void OneFactorAnalysis::showResult()
{
	std::cout << "ONE FACTOR ANALYSIS"	<< std::endl;

	for (int i = 0; i < 5; ++i)
	{
		std::cout << "Si2 number " << i << " IS --> " << Si2Vector.at(i) << std::endl;
	}

	std::cout << "S02 IS --> " << S02var<< std::endl;
	std::cout << "S2  IS --> " << S2var	<< std::endl;
	std::cout << "SA2 IS --> " << SA2var<< std::endl;

	std::cout << std::endl;

	std::cout << "SA2/S02 IS --> " << SA2var / S02var << std::endl;


	std::cout << std::endl;
}

OneFactorAnalysis::OneFactorAnalysis(int _size, int _number)
	: size(_size), number(_number)
{
	OneFactorAnalysis::coef.push_back(1.0);
	OneFactorAnalysis::coef.push_back(0.5); 
	OneFactorAnalysis::coef.push_back(1.8); 
	OneFactorAnalysis::coef.push_back(1.4); 
	OneFactorAnalysis::coef.push_back(2.0);
};
