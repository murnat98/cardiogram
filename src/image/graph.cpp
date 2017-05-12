#include <include.h>
#include <utility>
#include <Image.h>
#include <cmath>

using Distances = std::vector<double>;

void average       (Pixels& graphics);

std::pair<int, int> arithmeticalMeanPair(const Pixels& pixels);

bool isInRange(const sf::Color& color, size_t x, size_t y, uint8_t leftRange, uint8_t rightRange);

Pixels Image::getGraph()
{
	std::string grayCommandLineOpts = "black_white.exe " + fileName_;
	system(grayCommandLineOpts.c_str());

	fileName_ = "gray_" + fileName_;

	if (!loadFromFile(fileName_))
	{
		throw LOADFILE_ERROR;
	}

	sf::Vector2u imageSize = getSize();
	sf::Color color;

	for (size_t x = 0; x < imageSize.x; x++) // TODO: to some function
	{
		for (size_t y = 0; y < imageSize.y; y++)
		{
			color = getPixel(x, y); 
			//std::cout << y << "  -  " << (int)color.r << " " << (int)color.g << " " << (int)color.b << std::endl;

			if (isInRange(color, x, y, 0, 50)) // get graphics
			{
				graphics_.push_back(std::make_pair(x, y));
			}
		}
	}

	std::vector<int> pointCountPerLine;
	Pixels lines;

	for (size_t y = 0; y < imageSize.y; y++) // TODO: to some function
	{
		for (size_t x = 0; x < imageSize.x; x++)
		{
			color = getPixel(x, y);

			if (isInRange(color, x, y, 120, 170))
			{
				lines.push_back(std::make_pair(x, y));
			}
		}

		pointCountPerLine.push_back(lines.size());
		lines.clear();
	}
	for (const auto& count : pointCountPerLine)
	{
		std::cout << count << std::endl;
	}

	average(graphics_);

	return graphics_;
}

//This function averages by x:
//the only y matches to one x (the arithmetical mean)
void average(Pixels& graphics)
{
	Pixels result;
	Pixels average;

	int prev_x = 0;
	for (auto& point : graphics)
	{
		int x = std::get<0>(point);
		int y = std::get<1>(point);

		if (x != prev_x)
		{
			result.push_back(arithmeticalMeanPair(average));

			average.clear();
			prev_x = x;
		}
		else
		{
			average.push_back(std::make_pair(x, y));
		}
	}
	graphics.clear();
	graphics = result;

	//TODO: return Pixels
}

int operator -(const std::pair<int, int>& pair1, const std::pair<int, int>& pair2)
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
}

std::pair<int, int> arithmeticalMeanPair(const Pixels& pixels)
{
	int sum_x = 0, sum_y = 0, counter = 0;
	for (const auto& point : pixels)
	{
		sum_x += std::get<0>(point);
		sum_y += std::get<1>(point);

		++counter;
	}

	if (counter)
		return std::make_pair(sum_x / counter, sum_y / counter);
	else
		return std::make_pair(0, 0);
}

bool isInRange(const sf::Color& color, size_t x, size_t y, uint8_t leftRange, uint8_t rightRange)
{
#define IN_RANGE(color) color >= leftRange && color <= rightRange

	if (IN_RANGE(color.r) && IN_RANGE(color.g) && IN_RANGE(color.b))
	{
		return true;
	}
	else
	{
		return false;
	}

#undef IN_RANGE
}

bool isNearPoint(int distance)
{
	if (distance < 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}