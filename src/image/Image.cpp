#include <Image.h>
#include <fstream>

Image::Image(int type) :
	type_(type)
{}

Image::Image(const std::string& fileName, int type) :
	type_(type)
{
	image_.loadFromFile(fileName);
	fileName_ = fileName;
}

bool Image::loadFromFile(const std::string& fileName)
{
	return image_.loadFromFile((fileName_ = fileName));
}

void Image::setType(int type)
{
	type_ = type;
}

int Image::getType() const
{
	return type_;
}

#ifdef DEBUGMODE

bool Image::ok() const
{
	return true;
}

void Image::dump(const std::string& varName) const
{
	std::ofstream fout("Imagedump.dmp", std::ofstream::out);

	fout << "VarName = " << varName << std::endl;

	fout << "graphics_[0x" << &graphics_ << "]\n{" << std::endl;
	for (const auto& point : graphics_)
	{
		fout << "\t" << std::get<0>(point) << ", " << std::get<1>(point) << std::endl;
	}
	fout << "}" << std::endl;

	fout.close();

	/*std::ofstream fout("for_excel.csv", std::ofstream::out);

	for (const auto &point : graphics_)
	{
		fout << std::get<0>(point) << ";" << std::get<1>(point) << "\n";
	}

	fout.close();*/
}

#endif // DEBUGMODE