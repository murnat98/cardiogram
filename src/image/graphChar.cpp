#include <Image.h>
#include <algorithm>

const int MAX_TIME = 50;

int Image::get_R_Char() const
{
	bool maxFlag = true;
	int yMax = std::get<1>(graphics_[0]);
	int maxCounter = 0;
	std::vector<int> maxes;

	for (const auto& point : graphics_)
	{
		int x = std::get<0>(point);
		int y = std::get<1>(point);

		if (maxFlag || y > yMax)
		{
			yMax = y;

			if (maxCounter > MAX_TIME)
			{
				maxFlag = true;
			}
			if (maxFlag)
			{
				maxes.push_back(yMax);
			}

			maxFlag = false;
			++maxCounter;
		}
	}

	int sum = 0;
	std::for_each(maxes.begin(), maxes.end(), [&](const auto& max)
	{
		sum += max;
	});

	for (const auto& max : maxes)
	{
		std::cout << max << std::endl;
	}

	return sum / maxes.size();
}