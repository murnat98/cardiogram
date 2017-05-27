/*#include <include.h>
#include <Image.h>
#include <array>
#include <Cardiogram.h>
#include <fixedfann.h>

int main()
{
	fann* ann = fann_create_from_file("cardiogram.net");
	std::array<std::string, 12> fileNames;
	std::cout << "input fileNames:" << std::endl;
	/*for (auto& fileName : fileNames)
	{
		std::cin >> fileName;
	}
	fileNames[0] = "cardiogram1.jpg";
	fileNames[1] = "cardiogram2.jpg";
	fileNames[2] = "cardiogram3.jpg";
	fileNames[3] = "cardiogram.jpg";
	fileNames[4] = "cardiogram.jpg";
	fileNames[5] = "cardiogram.jpg";
	fileNames[6] = "cardiogram.jpg";
	fileNames[7] = "cardiogram.jpg";
	fileNames[8] = "cardiogram.jpg";
	fileNames[9] = "cardiogram.jpg";
	fileNames[10] = "cardiogram.jpg";
	fileNames[11] = "cardiogram.jpg";

	Cardiogram cardiogram(fileNames);
	float *result = cardiogram.analyze();
	for (size_t i = 0; i < 5; ++i)
	{
		std::cout << result[i] << std::endl;
	}

	system("pause");

	return 0;
}*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fixedfann.h>
#include <fann.h>

int main()
{
	fann* ann = fann_create_from_file("cardiogram.net");
	/*FILE* file = fopen("cardiogram.net", "r");

	char* version = (char*)calloc(13, 1);

	fread(version, 1, strlen("FANN_FLO_2.1" "\n"), file);
	if (strncmp(version, "FANN_FLO_2.1" "\n", strlen("FANN_FLO_2.1" "\n")) != 0)
	{
		std::cout << "NONONON" << std::endl;
	}

	std::cout << version << std::endl;

	free(version);
	fclose(file);*/

	system("pause");

	return 0;
}