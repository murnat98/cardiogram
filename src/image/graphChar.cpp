#include <Image.h>
#include <algorithm>

const int MAX_LINE = 100;

int Image::get_R_Char() const
{	
	int sum = 0, counter = 0;

	std::vector<int> extremumes;
	getExtremums(extremumes);

	std::for_each(extremumes.begin(), extremumes.end(), [&](const auto& max)
	{
		sum += max;
		++counter;
	});

	return counter ? sum / counter : -1; // TODO: think about returning the errors
}

int Image::get_RR_Char() const
{
	return 0;
}

int Image::getAbsExtremum() const
{
	int max = 0;
	bool maxFlag = true;

	for (const auto& point : graphics_)
	{
		int y = std::get<1>(point);

		if (maxFlag || y > max)
		{
			max = y;
			maxFlag = false;
		}
	}

	return max;
}

void Image::getExtremums(std::vector<int>& maxes) const
{
	int absExtremum   = getAbsExtremum();
	int localExtremum = 0;
	bool extremumFlag = true;
	
	for (const auto& point : graphics_)
	{
		int y = std::get<1>(point);

		if (y >= absExtremum - MAX_LINE)
		{
			if (extremumFlag || y > localExtremum)
			{
				localExtremum = y;
				extremumFlag = false;
			}
		}
		else
		{
			if (!extremumFlag)
			{
				maxes.push_back(localExtremum);
			}

			extremumFlag = true;
		}
	}
}