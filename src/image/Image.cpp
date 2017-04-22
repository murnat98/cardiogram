#include <Image.h>

Image::Image()
{}

Image::Image(const std::string& fileName)
{
	loadFromFile(fileName);
}

#ifdef DEBUGMODE

bool Image::ok() const
{
	return true;
}

void Image::dump(const std::string& varName) const
{

}

#endif // DEBUGMODE