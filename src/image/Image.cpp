#include <Image.h>
#include <fstream>

Image::Image() :
	graphics_()
{}

Image::Image(const std::string& fileName)
{
	loadFromFile(fileName);
	fileName_ = fileName;
}

#ifdef DEBUGMODE

bool Image::ok() const
{
	return true;
}

void Image::dump(const std::string& varName) const
{
	/*std::ofstream fout("Imagedump.dmp", std::ofstream::out);

	fout << "VarName = " << varName << std::endl;

	fout << "graphics_[0x" << &graphics_ << "]\n{" << std::endl;
	for (const auto& point : graphics_)
	{
		fout << "\t" << std::get<0>(point) << ", " << std::get<1>(point) << std::endl;
	}
	fout << "}" << std::endl;

	fout.close();*/

	std::ofstream fout("for_excel.txt", std::ofstream::out);

	for (const auto &point : graphics_)
	{
		fout << std::get<1>(point) << ", ";
	}

	fout.close();
}

#endif // DEBUGMODE