#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <cstdint>

int main(void)
{
	std::vector<int> vec;
	std::srand(std::time(nullptr));

	std::clock_t start = std::clock();

	/*for (size_t i = 0; i < 10000000; i++)
	{
		int a = std::rand();
		int b = std::rand();
		//std::swap(a, b);
		int tmp = a;
		a = b;
		b = tmp;
		vec.push_back(a);
		vec.push_back(b);
	}*/

	int32_t a = -42;
	a &= ~0xffff0000;
	std::cout << a << std::endl;
	/*unsigned char* c = (unsigned char*)&a;
	std::cout << +c[0] << std::endl;
	std::cout << +c[1] << std::endl;
	std::cout << +c[2] << std::endl;
	std::cout << +c[3] << std::endl;*/

	std::clock_t end = std::clock();
	std::cout << "Passed: " << (end - start) << " ms" << std::endl;
	system("PAUSE");
	return 0;
}