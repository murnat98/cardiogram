#include <Cardiogram.h>
#include <fann.h>
#include <algorithm>

Cardiogram::Cardiogram() :
	images_({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12})
{}

Cardiogram::Cardiogram(const std::array<std::string, Cardiogram::IMAGES_COUNT>& fileName) :
	images_({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12})
{
	for (size_t i = 0; i < 12; ++i)
	{
		images_[i].loadFromFile(fileName[i]);
	}
}

Cardiogram::Cardiogram(const std::array<Image, IMAGES_COUNT>& images) :
	images_(images)
{}

Cardiogram::~Cardiogram()
{}

std::string Cardiogram::analyze()
{
	fann* ann = fann_create_from_file("cardiogram.net");

	for (int i = 0; i < 3; i++)
	{
		images_[i].getGraph();
	}

	float input[3] = {};

	int R1 = images_[0].get_R_Char();
	int R2 = images_[1].get_R_Char();
	int R3 = images_[2].get_R_Char();
	std::vector<int> RRs = images_[0].get_RR_Char();

	for (size_t i = 1; i < RRs.size(); ++i)
	{
		int diff = RRs[i] - RRs[i - 1];
		if (diff > 100)
		{
			input[0] = 1;

			break;
		}
		else
		{
			input[0] = 0;
		}
	}

	if (RRs[0] >= 900 && RRs[0] <= 1100)
	{
		input[1] = 0;
	}
	else
	{
		input[1] = 1;
	}

	if (R1 > R2 && R2 > R3)
	{
		input[2] = 1;
	}
	else if (R2 > R1 && R1 > R3)
	{
		input[2] = 0;
	}
	else
	{
		input[2] = 2;
	}

	std::string diagnosis = "norm";
	float * output = fann_run(ann, input);
	if (output[0] == 1) diagnosis = "1";
	if (output[1] == 1) diagnosis = "2";
	if (output[2] == 1) diagnosis = "3";
	if (output[3] == 1) diagnosis = "4";
	if (output[4] == 1) diagnosis = "5";

	return diagnosis;
}

#ifdef DEBUGMODE

bool Cardiogram::ok() const
{
	return true;
}

void Cardiogram::dump(const std::string& varName) const
{

}

#endif // DEBUGMODE