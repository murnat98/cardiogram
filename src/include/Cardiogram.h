#pragma once

#include <include.h>
#include <string>
#include <Image.h>
#include <array>

#ifdef DEBUGMODE

#define CARDIOGRAM_DUMP(cardiogram) cardiogram.dump(#cardiogram);
#define CARDIOGRAM_OK_DUMP(cardiogram) if (!cardiogram.ok()) CARDIOGRAM_DUMP(cardiogram);

#else

#define CARDIOGRAM_DUMP(cardiogram)
#define CARDIOGRAM_OK_DUMP(cardiogram)

#endif // DEBUGMODE

class Cardiogram
{
public:
	static const int IMAGES_COUNT = 12;

	Cardiogram();
	explicit Cardiogram(const std::array<std::string, IMAGES_COUNT>& fileName);
	explicit Cardiogram(const std::array<Image, IMAGES_COUNT>&       images);

	~Cardiogram();

	std::string analyze();

#ifdef DEBUGMODE
	bool ok  ()							  const;
	void dump(const std::string& varName) const;
#endif // DEBUGMODE

private:
	std::array<Image, IMAGES_COUNT> images_;
};