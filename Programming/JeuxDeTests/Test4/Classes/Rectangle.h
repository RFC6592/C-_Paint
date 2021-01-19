#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"


class Rectangle : public Figure
{
	
	friend std::ostream& operator<<(std::ostream& s, const Rectangle &r);
	private:
		int dimX;
		int dimY;
		
		bool rempli;
		
	public:
		Rectangle();
		Rectangle(const char pId[5], const Point &p1, int dimX, int dimY, bool rempli, const Couleur *c);
		Rectangle(const Rectangle &r);
		virtual ~Rectangle();
		

		// ------ Setters ------
    	void setDimX(int dimX);
    	void setDimY(int dimY);
		void setRempli(bool rempli);
	
		// ------ Getters ------	
		int getDimX(void) const;
		int getDimY(void) const;
		bool isRempli(void) const;

		
		virtual void Dessine(void) const;		

};
#endif
