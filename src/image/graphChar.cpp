#include <Image.h>
#include <algorithm>

const int MAX_LINE   = 100;
const int AREA_COUNT = 50;

int Image::getIsoline()
{
	size_t size = 0;
	std::vector<int> yAreas(size = image_.getSize().y / AREA_COUNT);
	yAreas.assign(size, 0);

	for (const auto& point : graphics_)
	{
		int y = std::get<1>(point);

		++yAreas[y / AREA_COUNT];
	}

	return std::distance(yAreas.begin(), std::max_element(yAreas.begin(), yAreas.end())) * AREA_COUNT;
}

int Image::get_R_Char()
{	
	int sum = 0, counter = 0;

	getExtremes(extremes_);

	std::for_each(extremes_.begin(), extremes_.end(), [&](const auto& max)
	{
		sum += std::get<1>(max);
		++counter;
	});

	int R = counter ? sum / counter : -1;
	if (R == -1)
		throw R_NOT_RIGHT;

	return R - getIsoline(); // TODO: think about returning the errors
}

std::vector<int> Image::get_RR_Char()
{
	if (extremes_.empty())
	{
		getExtremes(extremes_);
	}
	size_t size = extremes_.size();

	std::vector<int> distances(size + 1);
	distances.assign(distances.size(), -1);

	for (size_t i = 1; i < size; ++i)
	{
		distances[i - 1] = abs(std::get<0>(extremes_[i]) - std::get<0>(extremes_[i - 1]));
	}

	return distances;
}

int Image::getAbsExtremum() const
{
	int max = 0;
	bool maxFlag = true;

	for (const auto& point : graphics_)
	{
		int y = std::get<1>(point);

		if (maxFlag || compare(y, max))
		{
			max = y;
			maxFlag = false;
		}
	}

	return max;
}

void Image::getExtremes(Pixels& maxes) const
{
	int absExtremum   = getAbsExtremum();
	int localExtremum_y = 0, localExtremum_x = 0;
	bool extremumFlag = true;
	
	for (const auto& point : graphics_)
	{
		int x = std::get<0>(point);
		int y = std::get<1>(point);

		if (compareMaxLine(y, absExtremum, MAX_LINE))
		{
			if (extremumFlag || compare(y, localExtremum_y))
			{
				localExtremum_y = y;
				localExtremum_x = x;
				extremumFlag = false;
			}
		}
		else
		{
			if (!extremumFlag)
			{
				maxes.push_back(std::make_pair(localExtremum_x, localExtremum_y));
			}

			extremumFlag = true;
		}
	}
}

bool Image::compare(int a, int b) const
{
	if (TYPE_CONTROL(type_))
	{
		return a > b;
	}
	else
	{
		return a < b;
	}
}

bool Image::compareMaxLine(int y, int extremum, int maxLine) const
{
	if (TYPE_CONTROL(type_))
	{
		return y <= extremum - maxLine;
	}
	else
	{
		return y >= extremum + maxLine;
	}
}