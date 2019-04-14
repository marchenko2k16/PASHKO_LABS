#include <random>
#include <iostream>
#include <vector>

//uniform random generator
namespace Random
{
	int random(int from, int to)
	{
		std::random_device randomDevice;
		std::mt19937_64 mt(randomDevice());
		std::uniform_real_distribution<> distribution(from, to);
		return static_cast<int>(distribution(mt));
	}	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int N = 1000;	
const int groupNumber_M = 61;
int inGroupNumber_MG = Random::random(1, 19);
std::pair<int, int> section;

std::vector<int> population;
float populationExpectedValue;
float populationDispersion;

std::vector<int> randomSample;
float sumOfRandomSample;
float randomSampleExpectedValue;
float randomSampleDispersion;

std::vector<int> systematizedSample;
float systematizedSampleExpectedValue;
float systematizedSampleDispersion;

int numOfStrats = 10;
std::vector<std::vector<int>> stratifiedParts;
std::vector<std::vector<int>> stratifiedSampleVector; 
std::vector<float> stratifiedExpectedValues;
std::vector<float> stratifiedDispersion;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<int> fillSampleFromStrat(std::vector<int> strat)
{
	std::vector<int> vec;
	for (auto i = 0; i < Random::random(1, numOfStrats); ++i)
	{
		vec.push_back(strat.at(i));
	}
	return vec;
}

std::vector<int> fillSample(int size)
{

	std::vector<int> vec;
	for (auto i = 0; i < size; ++i)
	{
		vec.push_back(population.at(Random::random(0, ::N)));
	}
	return vec;
}

std::vector<int> fillPopulation(int size)
{

	std::vector<int> vec;
	for (auto i = 0; i < size; ++i)
	{
		vec.push_back(Random::random(section.first, section.second));
	}
	return vec;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float countPopulationExpectedValue(std::vector<int> population)
{
	float sumOf{};
	for (auto e : population)
	{
		sumOf += e;
	}

	return sumOf / ::N;
}
float countPopulationDispersion(std::vector<int> population, float expectedValue)
{
	float sumOf{};
	for (auto e : population)
	{
		sumOf += std::pow((e - expectedValue), 2);
	}

	return sumOf / (::N - 1);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float sumOfRandom(std::vector<int> randS)
{
	float sumOf{};
	for (auto e : randS)
	{
		sumOf += e / randS.size();
	}
	return sumOf * ::N;
}
float countExpectedValue(std::vector<int> randS)
{
	float sumOf{};
	for (auto e : randS)
	{
		sumOf += e;
	}
	return  sumOf / randS.size();
}
float countDispersion(std::vector<int> randS, float randomExpectedValue)
{
	float sumOf{};
	for (auto e : randS)
	{
		sumOf += std::pow((e - randomExpectedValue),2);
	}
	return  sumOf / randS.size() - 1;
}

std::vector<int> makeStrat(int index, int nStr)
{
	std::vector<int> tmp;
	for (int i = index * ::N/nStr ; i <  (index + 1) * ::N / nStr;i++)
	{
		tmp.push_back(population.at(nStr * index + index));
	}
	return tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	/*-----FIRST PART OF TASK------------------------------------------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------------*/
	//generater random group number
	::inGroupNumber_MG = Random::random(1, 19);
	std::cout << "inGroupNumber_MG " << inGroupNumber_MG << std::endl;
	//start of section
	::section.first = 10 + ::groupNumber_M;
	std::cout << "section.first " << section.first << std::endl;
	//end of section
	::section.second = ::inGroupNumber_MG + 2 * ::groupNumber_M;
	std::cout << "section.second " << section.second << std::endl;

	//FILLING POPULATION BY UNIFORM//
	::population = fillPopulation(N);
	::populationExpectedValue = countPopulationExpectedValue(population);
	std::cout << "populationExpectedValue " << populationExpectedValue << std::endl;
	::populationDispersion	  = countPopulationDispersion(population, populationExpectedValue);
	std::cout << "populationDispersion " << populationDispersion << std::endl;

	/*-----------------------------------------------------------------------------------------------------*/
	int sizeOfRandomPopulation = 100;
	randomSample = fillSample(sizeOfRandomPopulation);
	::sumOfRandomSample	= sumOfRandom(randomSample);
	std::cout << "sumOfRandomSample " << sumOfRandomSample << std::endl;
	::randomSampleExpectedValue = countExpectedValue(randomSample);
	std::cout << "randomSampleExpectedValue " << randomSampleExpectedValue << std::endl;
	::randomSampleDispersion	= countDispersion(randomSample, randomSampleExpectedValue);
	std::cout << "randomSampleDispersion " << randomSampleDispersion << std::endl;
	/*-----------------------------------------------------------------------------------------------------*/

	int sizeOfSystemized = 100;
	int stepOfSystemized = ::N / sizeOfSystemized;
	//FILLING SYSTEMIZED
	for (int i = Random::random(0,10); i < ::N; i += stepOfSystemized)
	{
		systematizedSample.push_back(population.at(i));
	}
	systematizedSampleExpectedValue = countExpectedValue(systematizedSample);
	std::cout << "systematizedSampleExpectedValue " << systematizedSampleExpectedValue << std::endl;
	systematizedSampleDispersion = countDispersion(systematizedSample, systematizedSampleExpectedValue);
	std::cout << "systematizedSampleDispersion " << systematizedSampleDispersion << std::endl;

	/*-----------------------------------------------------------------------------------------------------*/

	for (auto i = 0; i < ::numOfStrats; i++)
	{	
		stratifiedParts.push_back(makeStrat(i, ::numOfStrats));
	}

	std::vector<std::vector<int>> stratifiedSampleVector;

	std::vector<float> stratifiedExpectedValues;
	std::vector<float> stratifiedDispersion;

	std::cin.get();
	return 0;
}



