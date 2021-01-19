#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
#include "Rectangle.h"
#include "Ecran.h"

#include "./WindowSDL/WindowSDL.h"


/**
* @brief Constructeur par defaut de la classe Rectangle
*/
Rectangle::Rectangle() : Figure()
{
	Trace("\x1b[37m\x1b[40m Constructeur par defaut de la classe Rectangle\x1b[0m");
	setDimX(0u);
	setDimY(0u);
	setRempli(false);
}


/**
* @brief Constructeur d'initialisation de la classe Rectangle
*/
Rectangle::Rectangle(const char *pId, const Point &p1, int dimX, int dimY, bool rempli, const Couleur *c) : Figure(pId, p1, c)
{
	Trace("\x1b[37m\x1b[40m Dans le constructeur d'initialisation de la classe Rectangle\x1b[0m");
	setDimX(dimX);
	setDimY(dimY);
	setRempli(rempli);
	
}

/**
* @brief Destructeur de la classe Rectangle
*/
Rectangle::~Rectangle()
{
	Trace("\x1b[37m\x1b[41m Destructeur de la classe Rectangle\x1b[0m");
}


/**
* @brief Constructeur de copie de la classe Rectangle
*/
Rectangle::Rectangle(const Rectangle &r) :  Figure(r)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Dans le constructeur de copie de la classe Rectangle\x1b[0m");
	setDimX(r.getDimX());
	setDimY(r.getDimY());
	setRempli(r.isRempli());
}


ostream& operator<<(ostream& s, const Rectangle &r)
{
	s << r.getId() << " [ Rectangle : Position(" << r.getPosition() << "), DimX=" << r.getDimX() << ", DimY=" << r.getDimY() << ", Rempli : " << r.isRempli();
	if(r.getCouleur() != NULL)
	{
		s << ", Couleur(" << r.getCouleur()->getRouge() << ", " << r.getCouleur()->getVert() << ", " << r.getCouleur()->getBleu() << ")]" << endl;
	}
	return s;  
}

/**
* @brief Methode qui permet de dessiner des rectangles
*/
void Rectangle::Dessine(void) const 
{
	Trace("Dans la methode Dessine de la classe Rectangle");
	WindowSDL::drawRectangle(getCouleur()->getRouge(), getCouleur()->getVert(), getCouleur()->getBleu(), getPosition().getX(), getPosition().getY(), getDimX() , getDimY());
	if(!isRempli())
	{
		WindowSDL::fillRectangle(getCouleur()->getRouge(), getCouleur()->getVert(), getCouleur()->getBleu(), getPosition().getX(), getPosition().getY(), getDimX(), getDimY());
	}
}

// ------------ Setters ------------
void Rectangle::setRempli(bool rempli) 
{
	this->rempli = rempli;
}

void Rectangle::setDimX(int dimX)
{
	this->dimX = dimX;
}

void Rectangle::setDimY(int dimY)
{
	this->dimY = dimY;
}

// ------------ Getters ------------
int Rectangle::getDimX(void) const { return this->dimX; }
int Rectangle::getDimY(void) const { return this->dimY; }
bool Rectangle::isRempli(void) const { return this->rempli; }
 

