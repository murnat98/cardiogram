#include <iostream>
#include <utility>

/*int operator -(const std::pair<int, int>& pair1, const std::pair<int, int>& pair2)
{
#define PAIR(name, number) std::get<number>(name)

#define x0 PAIR(pair1, 0)
#define x1 PAIR(pair1, 1)
#define y0 PAIR(pair2, 0)
#define y1 PAIR(pair2, 1)

	return y0 - y1;

#undef y1
#undef y0
#undef x1
#undef x0

#undef PAIR
}*/

int main()
{
	std::pair<int, int> pair1(0, 5);
	std::pair<int, int> pair2(0, 8);
	std::cout << pair1 - pair2 << std::endl;

	system("pause");

	return 0;
}