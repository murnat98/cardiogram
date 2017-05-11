#include <include.h>
#include <utility>
#include <Image.h>
#include <cmath>

using Distances = std::vector<double>;

void average       (Pixels& graphics);
Pixels scaleAverage(const Pixels& graphics);

template <typename T>
T arithmeticalMean(const std::vector<T>& values);
std::pair<int, int> arithmeticalMeanPair(const Pixels& pixels);

bool isInRange(const sf::Color& color, size_t x, size_t y, uint8_t leftRange, uint8_t rightRange);
bool isNearPoint(int distance);

Distances getDistances(const Pixels& pixels);

Pixels Image::getGraph()
{
	std::string grayCommandLineOpts = "black_white.exe " + fileName_;
	system(grayCommandLineOpts.c_str());

	fileName_ = "gray_" + fileName_;

	if (!loadFromFile(fileName_))
	{
		throw LOADFILE_ERROR;
	}

	Distances y_scale; // millivoltage
	Pixels scalePoints;       // points in the image, where are light gray lines(for scale)

	sf::Vector2u imageSize = getSize();
	sf::Color color;

	for (size_t x = 0; x < imageSize.x; x++)
	{
		for (size_t y = 0; y < imageSize.y; y++)
		{
			color = getPixel(x, y); 
			//std::cout << y << "  -  " << (int)color.r << " " << (int)color.g << " " << (int)color.b << std::endl;

			if (isInRange(color, x, y, 0, 50)) // get graphics
			{
				graphics_.push_back(std::make_pair(x, y));
			}
			
			if (isInRange(color, x, y, 120, 170))
			{
				scalePoints.push_back(std::make_pair(x, y));
			}
		}
		//TODO: debug
		/*for (const auto& scale : scalePoints)
		{
			std::cout << std::get<0>(scale) << " " << std::get<1>(scale) << std::endl;
		}*/
		std::cout << "---------------------------------------------" << std::endl;
		scalePoints = scaleAverage(scalePoints);
		for (const auto& scale : scalePoints)
		{
			std::cout << std::get<0>(scale) << " " << std::get<1>(scale) << std::endl;
		}
		y_scale = getDistances(scalePoints);
		std::cout << "============================================" << std::endl;
		/*for (const auto& distance : y_scale)
		{
			std::cout << distance << std::endl;
		}*/
		throw LOADFILE_ERROR;
		//y_scale.push_back(getDistances(scalePoints));
	}
	
	//average(y_scale);
	average(graphics_);

	return graphics_;
}

//This function averages by x:
//the only y matches to one x (the arithmetical mean) (the result)
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
}

int operator -(const std::pair<int, int>& pair1, const std::pair<int, int>& pair2)
{
#define PAIR(name, number) std::get<number>(name)
#define x0 PAIR(pair1, 0)
#define x1 PAIR(pair1, 1)
#define y0 PAIR(pair2, 0)
#define y1 PAIR(pair2, 1)

	//return sqrt((x0 - x1) * (x0 - x1) - (y0 - y1) * (y0 - y1));
	return y0 - y1;

#undef y1
#undef y0
#undef x1
#undef x0
#undef PAIR
}

//this function assumes that x components of each point equal
//it averages the near points
Pixels scaleAverage(const Pixels& graphics)
{
	Pixels result;

	std::vector<int> nearPoints;
	int distance = 0;

	for (size_t i = 1; i < graphics.size(); i++)
	{
		distance = graphics[i] - graphics[i - 1];
		if (isNearPoint(distance))
		{
			nearPoints.push_back(std::get<1>(graphics[i])); // the y component
		}
		else
		{
			//nearPoints.push_back(arithmeticalMean<int>(nearPoints));
			result.push_back(std::make_pair(std::get<0>(graphics[0]), arithmeticalMean(nearPoints)));

			nearPoints.erase(nearPoints.begin(), nearPoints.end());
		}
	}

	return result;
}

template <typename T>
T arithmeticalMean(const std::vector<T>& values)
{
	int counter = 0;
	T sum = 0;

	for (const auto& value : values)
	{
		sum += value;

		++counter;
	}

	return counter ? sum / counter : sum;
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

Distances getDistances(const Pixels& pixels)
{
	Distances result(pixels.size());
	size_t counter = 0;

	std::pair<int, int> prevPoint;
	bool prevPointInit = false;
	for (const auto& point : pixels)
	{
		if (!prevPointInit)
		{
			prevPoint = point;

			prevPointInit = true;
			continue;
		}

		result[counter] = point - prevPoint;

		prevPoint = point;
		++counter;
	}

	return result;
}
