#include "rational.hpp"
#include <iostream>

int main(void)
{
	rational<int> r(1,0);
	rational<int> q(0,1);
	r *= q;
	std::cout << r << "\n";
	return 0;
}