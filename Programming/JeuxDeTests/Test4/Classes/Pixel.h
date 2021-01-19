#ifndef PIXEL_H
#define PIXEL_H

#include "Figure.h"


class Pixel : public Figure
{
	friend std::ostream& operator<<(std::ostream& s, const Pixel &pixel);

	
	public:
		Pixel();
		virtual ~Pixel();
		Pixel(const char pId[5], const Point &p);
		Pixel(const char pId[5], const Point &p, const Couleur *pCouleur);
		Pixel(const Pixel& p);

		virtual void Dessine(void) const;
};

#endif


