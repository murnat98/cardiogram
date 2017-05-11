#include <iostream>
#include <opencv\cv.hpp>
#include <opencv\highgui.h>

void getGrayImage(const std::string& fileName);

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		std::cout << "program must get inly 1 parameter(file name)" << std::endl;

		return -1;
	}

	std::string colorFileName = argv[1];
	getGrayImage(colorFileName);

#ifdef DEBUG_MODE
	system("pause");
#endif // DEBUG_MODE

	return 0;
}

void getGrayImage(const std::string& fileName)
{
	cv::Mat image = cv::imread(fileName, CV_LOAD_IMAGE_COLOR);
	if (!image.data)
	{
		return;
	}

	cv::Mat grayScale;
	cv::cvtColor(image, grayScale, cv::COLOR_BGR2GRAY);

	std::string outFileName = "gray_" + fileName;
	cv::imwrite(outFileName, grayScale);
}