#pragma once

#include <include.h>
#include <string>
#include <SFML\Graphics.hpp>

#ifdef DEBUGMODE

#define IMAGE_DUMP(image) image.dump(#image);
#define IMAGE_OK_DUMP(image) if (!image.ok()) { IMAGE_DUMP(image); assert(!"image not ok"); }

#else

#define IMAGE_DUMP(image)
#define IMAGE_OK_DUMP(image)

#endif // DEBUGMODE

class Image : public sf::Image
{
public:
	enum errors
	{
		LOADFILE_ERROR
	};

	Image(int type);
	Image(const std::string& fileName, int type);

	Pixels getGraph();
	
	int get_R_Char()   const;
	int get_RR_Char()  const;
	int get_S_Char()   const;
	int get_QRS_Char() const;
	int get_P_Char()   const;
	int get_T_Char()   const;

#ifdef DEBUGMODE
	bool ok()							  const;
	void dump(const std::string& varName) const;
#endif // DEBUGMODE

private:
	int  getAbsExtremum()                         const;
	void getExtremums  (std::vector<int>& maxes)  const; // return to maxes(it's more efficient)

	Pixels graphics_;
	std::string fileName_;
	int type_;
};
