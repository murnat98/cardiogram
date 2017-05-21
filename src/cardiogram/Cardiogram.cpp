#include <Cardiogram.h>

Cardiogram::Cardiogram(int type) :
	image_(type),
	type_(type)
{}

Cardiogram::Cardiogram(const std::string& fileName, int type) :
	image_(fileName, type),
	type_(type)
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