#pragma once

#include <include.h>
#include <string>
#include <Image.h>

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
	Cardiogram(int type);
	Cardiogram(const std::string& fileName, int type);

	~Cardiogram();

	void analyze() const; // now it is void, then it will be changed (may be some class Result)
	void saveResult() const;

#ifdef DEBUGMODE
	bool ok  ()							  const;
	void dump(const std::string& varName) const;
#endif // DEBUGMODE

private:
	Image image_;
	int type_;
};