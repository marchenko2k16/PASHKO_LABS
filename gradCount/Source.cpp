#include <iostream>

void countGrad(float x1, float x2)
{
	std::cout << "top " << (6 * x1 + x2) << std::endl;
	std::cout << "top " << (x1 + 4 * x2) << std::endl;
}

int main()
{
	float x01 = 4;
	float x02 = 4;

	float x11 = 0.193;
	float x12 = -0.252;
	countGrad(x11,x12);


	std::cin.get();
}