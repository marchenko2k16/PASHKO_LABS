#include <iostream>
#include <random>
#include <vector>
#include <cmath>


double random(double from, double to)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<>distibution (from, to) ;
	return distibution(mt);
}
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
		_sqrSum += (e * e);
	}

	return _sqrSum;
}

double max(std::vector<double> v)
{
	double tmp{};
	for (auto e : v)
	{
		if (e > tmp) tmp = e;
	}
	return tmp;
}

int n = 1000;
int N = 9;// 9/15
int NG = 61;
double studentCoef = 1.96;
double fisherDistributionQuantum = 1;


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


double estimateSiSquared(std::vector<double> x, std::vector<double> e_values)
{
	double xAvg = avg(x);
	double countXdispersion{};
	pow(1, 2);
	for (auto e : x)
	{
		countXdispersion += pow((e - xAvg), 2);
	}
	double xDispersion = countXdispersion;
	double eSquared = sqrSum(e_values);
	double countReturnStatement{};
	for (auto e : x)
	{
		countReturnStatement += ( (eSquared / n - 2) * (1 - (1 / n)) - (pow((e - xAvg), 2)) / xDispersion );
	}

	return countReturnStatement;
}

double getEstimatedBetta(std::vector<double> x, std::vector<double> y, double realAlpha)
{
	double xAverage = avg(x);
	double SXsquared{};
	for (auto e : x)
	{
		SXsquared += (pow((e - xAverage), 2));
	}
	SXsquared /= (n - 1);
	double Ssquared{};
	for (auto i = 0; i < x.size(); ++i)
	{
		Ssquared += (pow(y.at(i) - realAlpha - x.at(i), 2));
	}
	Ssquared /= (n - 2);
	
	return sqrt(Ssquared) / ( sqrt(SXsquared) * sqrt(n - 1));
}

double getEstimatedAlpha(std::vector<double> x, std::vector<double> y, double realAlpha)
{
	double xAverage = avg(x);
	double SXsquared{};
	for (auto e : x)
	{
		SXsquared += (pow((e - xAverage), 2));
	}
	SXsquared /= (n - 1);
	double Ssquared{};
	for (auto i = 0; i < x.size(); ++i)
	{
		Ssquared += (pow(y.at(i) - realAlpha - x.at(i), 2));
	}
	Ssquared /= (n - 2);

	return sqrt(Ssquared)* sqrt((1 / n) + (pow(xAverage, 2) / ((n - 1) * SXsquared)));
}

double getNormalModelEstimation(std::vector<double>x, std::vector<double>y, double realAlpha)
{
	double yAverage = avg(y);
	double Ssquared{};
	for (auto i = 0; i < x.size(); ++i)
	{
		Ssquared += pow((y.at(i) - realAlpha - x.at(i)), 2);
	}
	Ssquared /= (n - 2);
	double SYsquared{}; 
	for (auto e : y)
	{
		SYsquared += pow((e - yAverage), 2 );
	}
	SYsquared /= (n - 1);

	return Ssquared / SYsquared;
}



int main()
{
	std::vector<double> xi(N);
	std::vector<double> yi(N);

	for (auto i = 0; i < N; ++i)
	{
		xi.at(i) = i + random(0, 1) * N / NG;
		yi.at(i) = N * random(0, 1) * xi.at(i) + NG * random(0, 1) + N;
	}

	double alpha = countAlpha(xi, yi);
	double betta = countBetta(xi, yi, alpha);

	std::vector<double> y_;
	for (auto e : xi)
	{
		y_.push_back(alpha * e + betta);
	}
	std::vector<double> e;
	for (auto i = 0; i < yi.size(); ++i)
	{
		e.push_back(yi.at(i) - y_.at(i));
	}
	double Si = sqrt(estimateSiSquared(xi, e));
	std::vector<double> Rvalues;
	for (auto element : e)
	{
		Rvalues.push_back(abs(element / Si));
	}
	double Rmax = max(Rvalues);

	double estimatedAlpha = getEstimatedAlpha(xi, yi, alpha);
	double estimatedBetta = getEstimatedBetta(xi, yi, alpha);
	double normalModelEstimation = getNormalModelEstimation(xi, yi, alpha);


	std::cout << "Check hypotheses :" << std::endl;;
	std::cout << "H0: BETTA = b" << std::endl;;

	if (abs(betta) > studentCoef * estimatedBetta)
	{
		std::cout << "Betta value IS significant" << std::endl;
	}
	else
	{
		std::cout << "Betta value IS NOT significant" << std::endl;
	}
	std::cout << "H0: ALPHA = a " << std::endl;
	if (abs(betta) > studentCoef * estimatedAlpha)
	{
		std::cout << "Alpha value IS significant" << std::endl;
	}
	else
	{
		std::cout << "Alpha value IS NOT significant" << std::endl;
	}
	std::cout << "H0: Model correctness" << std::endl;
	if (normalModelEstimation < fisherDistributionQuantum)
	{
		std::cout << "Model IS adequate" << std::endl;
	}
	else
	{
		std::cout << "Model IS NOT adequate" << std::endl;
	}
}