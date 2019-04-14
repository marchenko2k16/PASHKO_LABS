#include "OneFactorAnalysis.h"
#include "TwoFactorAnalysis.h"

#include <iostream>

constexpr int SERIAL_NUMBER_ALEXANDER = 11;
constexpr int SERIAL_NUMBER_MARIAM = 16;
constexpr int SIZE = 1000;


int main() 
{
	
	//OneFactorAnalysis oneFactor(SIZE, SERIAL_NUMBER_ALEXANDER);
	//oneFactor.fillTable();
	//oneFactor.callCalculations();
	//oneFactor.showResult();

	TwoFactorAnalysis twoFactor(100, SERIAL_NUMBER_ALEXANDER);
	twoFactor.fillTable();
	twoFactor.callCalculations();
	twoFactor.showResult();

	std::cin.get();
}
