#include <Cardiogram.h>

Cardiogram::Cardiogram() {}

Cardiogram::Cardiogram(const std::string& fileName) :
	image_(fileName)
{}

Cardiogram::~Cardiogram()
{}

#ifdef DEBUGMODE

bool Cardiogram::ok() const
{
	return true;
}

void Cardiogram::dump(const std::string& varName) const
{

}

#endif // DEBUGMODE