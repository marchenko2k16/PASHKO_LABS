#include <iostream>
#include <random>
#include <vector>

double random(double from, double to)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<>distibution (from, to) ;
	return distibution(mt);
}

int n = 1000;
int N = 9;// 9/15
int NG = 61;

double studentCoef{};
double fisherDisttibutionQuantum{};

double avg(std::vector<double> v)
{
	double count{};
	for (auto e : v)
	{
		count += e;
	}
	return count / v.size();
}

double sqrSum(std::vector<double> v)
{
	double _sqrSum{};
	for (auto e : v)
	{
		_sqrSum += e * e;
	}

	return _sqrSum;
}
//estimate regression coef 
double countAlpha(std::vector<double> x, std::vector<double> y)
{
	double ssXY{};
	for (auto i = 0; i < x.size(); ++i)
	{
		ssXY += x.at(i) * y.at(i);
	}
	ssXY -= (x.size() * avg(x) * avg(y));

	double ssXX{};
	for (auto i = 0; i < x.size(); ++i)
	{
		ssXY += x.at(i) * x.at(i);
	}
	ssXY -= ((x.size()) * avg(x) * avg(x));

	return ssXY / ssXX;
}

//estimate regression coef 
double countBetta(std::vector<double> x, std::vector<double> y, double alpha)
{
	return avg(y) - alpha * avg(x);
}

int main()
{
	std::vector<double> xi(N);
	std::vector<double> yi(N);

	for (auto i = 0; i < N; ++i)
	{
		xi.at(i) = i + random(0, 1) * N / NG;
		yi.at(i) = N * random(0, 1)* xi.at(i) + NG*random(0,1) + N;
 	}

	double alpha = countAlpha(xi, yi);
	double betta = countBetta(xi, yi, alpha);



}