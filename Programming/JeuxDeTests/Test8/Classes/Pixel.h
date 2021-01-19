#ifndef PIXEL_H
#define PIXEL_H

#include "Figure.h"
#include "./Exception/BaseException.h"

class Pixel : public Figure
{
	friend std::ostream& operator<<(std::ostream& s, const Pixel &pixel);
	
	public:
		Pixel();
		~Pixel();
		Pixel(const char pId[5], const Point &p);
		Pixel(const char pId[5], const Point &p, const Couleur *pCouleur);
		Pixel(const Pixel& p);

		virtual void Dessine(void) const;

		virtual void setId(const char pId[5]);
};

#endif


