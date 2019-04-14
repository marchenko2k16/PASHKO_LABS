#include "TwoFactorAnalysis.h"



void TwoFactorAnalysis::Q1()
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			float all = 0;
			for (int iter = 0; iter < size; ++iter)
			{
				all += pow(TwoFactorAnalysis::table[i][j][iter], 2);
			}
			Q1var += all / (100);
		}
	}
}

void TwoFactorAnalysis::Q2()
{
	for (int i = 0; i < m; ++i)
	{
		float avg = 0;
		float all = 0;
		for (int j = 0; j < k; ++j)
		{
			for (int iter = 0; iter < size; ++iter)
			{
				all += TwoFactorAnalysis::table[i][j][iter];
			}
		}
		avg += all / size;
		Q2var += pow(avg, 2);
	}
	Q2var /=  (m * k);
}

void TwoFactorAnalysis::Q3()
{
	for (int j = 0; j < k; ++j)
	{
		double avg = 0;
		double all = 0;
		for (int i = 0; i < m; ++i)
		{
			for (int iter = 0; iter < size; ++iter)
			{
				all += TwoFactorAnalysis::table[i][j][iter];
			}
		}
		avg += all/size;
		Q3var += pow(avg, 2);
	}
	Q3var /= (k * m);
}

void TwoFactorAnalysis::Q4()
{
	double sumOfAvg = 0;
	for (int j = 0; j < k; ++j)
	{
		double avg = 0;
		for (int i = 0; i < m; ++i)
		{
			float all = 0;
			for (int iter = 0; iter < size; ++iter)
			{
				all += TwoFactorAnalysis::table[i][j][iter];
			}
			avg += all/size;
		}
		sumOfAvg += avg;
	}

	Q4var = pow(sumOfAvg, 2) / (TwoFactorAnalysis::k * TwoFactorAnalysis::m) / k;
}

void TwoFactorAnalysis::Q5()
{
	float all = 0;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			for (int iter = 0; iter < size; ++iter)
			{
				all += pow(TwoFactorAnalysis::table[i][j][iter], 2);
			}
		}
	}
	Q5var = all;
}

void TwoFactorAnalysis::S02()
{
	S02var = (Q1var + Q4var - Q2var - Q3var) / ((k - 1) * (m - 1));
}

void TwoFactorAnalysis::SA2()
{
	SA2var = (Q2var - Q4var) / (k - 1);

}

void TwoFactorAnalysis::SB2()
{
	SB2var = (Q3var - Q4var) / (m - 1);

}

void TwoFactorAnalysis::SAB2()
{
	SAB2var = (Q5var - TwoFactorAnalysis::size * Q1var) / (m * k * (TwoFactorAnalysis::size - 1));

}


void TwoFactorAnalysis::fillTable()
{
	table.resize(m, std::vector<std::vector<double>>(k, std::vector<double>(size)));

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			for (int inner = 0; inner < TwoFactorAnalysis::size; ++inner)
			{
				table[i][j][inner] = (TwoFactorAnalysis::number * TwoFactorAnalysis::coef[i][j] + Random::random(0, 1));
			}
		}
	}
}

void TwoFactorAnalysis::callCalculations()
{
	Q1();
	Q2();
	Q3();
	Q4();
	Q5();

	S02();
	SA2();
	SB2();
	SAB2();
}

void TwoFactorAnalysis::showResult()
{
	std::cout << "TWO FACTOR ANALYSIS" << std::endl;

	std::cout << "Q1 IS --> " << Q1var << std::endl << std::endl;
	std::cout << "Q2 IS --> " << Q2var << std::endl << std::endl;
	std::cout << "Q3 IS --> " << Q3var << std::endl << std::endl;
	std::cout << "Q4 IS --> " << Q4var << std::endl << std::endl;
	std::cout << "Q5 IS --> " << Q5var << std::endl << std::endl;

	std::cout << std::endl;

	std::cout << "S02 IS --> " << S02var << std::endl;
	std::cout << "SA2 IS --> " << SA2var << std::endl;
	std::cout << "SB2  IS --> " << SB2var << std::endl;
	std::cout << "SAB2 IS --> " << SAB2var << std::endl;

	std::cout << std::endl;
	std::cout << "n*s02/sab2  --> " << size * S02var / SAB2var << std::endl;

	std::cout << std::endl;
}


