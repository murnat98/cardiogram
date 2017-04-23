#pragma once

#include <include.h>
#include <string>
#include <SFML\Graphics.hpp>

#ifdef DEBUGMODE

#define IMAGE_DUMP(image) image.dump(#image);
#define IMAGE_OK_DUMP(image) if (!image.ok()) IMAGE_DUMP(image);

#else

#define IMAGE_DUMP(image)
#define IMAGE_OK_DUMP(image)

#endif // DEBUGMODE

class Image : public sf::Image
{
public:
	Image();
	Image(const::std::string& fileName);

	Pixels getGraph();
	Chars  getGraphChar() const;

#ifdef DEBUGMODE
	bool ok()							  const;
	void dump(const std::string& varName) const;
#endif // DEBUGMODE

private:
	Pixels result_;
};
