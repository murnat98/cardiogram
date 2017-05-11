#include <Cardiogram.h>

Cardiogram::Cardiogram() {}

Cardiogram::Cardiogram(const std::string& fileName) :
	image_(fileName)
{}

Cardiogram::~Cardiogram()
{}

void Cardiogram::analyze() const
{

}

void Cardiogram::saveResult() const
{

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