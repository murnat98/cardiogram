#pragma once

#include <include.h>
#include <string>
#include <SFML\Graphics.hpp>

#define TYPE_CONTROL(type) type == 1 || type == 2 || type == 5 || type == 10 || type == 11
#ifdef DEBUGMODE

#define IMAGE_DUMP(image) image.dump(#image);
#define IMAGE_OK_DUMP(image) if (!image.ok()) { IMAGE_DUMP(image); assert(!"image not ok"); }

#else

#define IMAGE_DUMP(image)
#define IMAGE_OK_DUMP(image)

#endif // DEBUGMODE

class Image// : public sf::Image
{
public:
	enum errors
	{
		LOADFILE_ERROR,
		R_NOT_RIGHT
	};

	Image(int type);
	Image(const std::string& fileName, int type);

	bool loadFromFile(const std::string& fileName);
	
	void setType(int type);

	int getType() const;
	Pixels getGraph();
	
	int getIsoline();
	int get_R_Char();
	std::vector<int> get_RR_Char();
	//int get_S_Char()   const;
	//int get_QRS_Char() const;
	//int get_P_Char()   const;
	//int get_T_Char()   const;

#ifdef DEBUGMODE
	bool ok()							  const;
	void dump(const std::string& varName) const;
#endif // DEBUGMODE

private:
	int  getAbsExtremum()                                 const;
	void getExtremes   (Pixels& maxes)                    const; // return to maxes(it's more efficient)
	bool compare       (int a, int b)                     const;
	bool compareMaxLine(int y, int extremum, int maxLine) const;


	sf::Image image_;
	std::string fileName_;
	int type_;

	Pixels graphics_;
	Pixels extremes_;
};
