#include <include.h>
#include <Image.h>
#include <Cardiogram.h>

int main()
{
	Image image("cardiogram.jpg");
	Pixels graphics;

	try
	{
		graphics = image.getGraph();
	}
	catch (Image::errors error)
	{
		std::cerr << "error code = " << error << std::endl;
	}
	catch (...)
	{
		std::cerr << "some error occured" << std::endl;
	}

	int R = image.get_R_Char();
	std::cout << R << std::endl;
	
	IMAGE_DUMP(image);
	
#ifdef DEBUGMODE

	system("pause");

#endif // DEBUGMODE

	return 0;
}