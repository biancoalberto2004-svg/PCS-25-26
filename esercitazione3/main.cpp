#include "rational.hpp"
#include <iostream>

int main(void)
{
	// casi normali
	rational<int> a(3,7);
	rational<int> b(2,5);
	std::cout << "a = " << a << "\n";
	std::cout << "b = " << b << "\n";
	std::cout << "a+b = " << a+b << "\n";
	std::cout << "a-b = " << a-b << "\n";
	std::cout << "a*b = " << a*b << "\n";
	std::cout << "a/b = " << a/b << "\n\n";
	
	// caso limite: NaN
	rational<int> c(0,0);
	std::cout << "c = " << c << "\n";
	std::cout << "a+c = " << a+c << "\n\n";
	
	// caso limite: Inf
	rational<int> d(3,0);
	rational<int> e(-5,0);
	std::cout << "a+Inf = " << a+d << "\n";
	std::cout << "b/(-Inf) = " << b/e << "\n";
	rational<int> f(0,3);
	std::cout << "a/0 = " << a/f << "\n\n";
	
	// forme indeterminate
	std::cout << "Inf+(-Inf) = " << d+e << "\n";
	std::cout << "0*Inf = " << f*d << "\n";
	std::cout << "Inf/Inf = " << d/d << "\n";
	std::cout << "0/0 = " << f/f << "\n";
	
	return 0;

}