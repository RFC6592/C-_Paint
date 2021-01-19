#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Pixel.h"
#include "Ecran.h"

#include "./WindowSDL/WindowSDL.h"
using namespace std;

Pixel::Pixel() : Figure()
{
	Trace("\x1b[37m\x1b[40m Constructeur par defaut de Pixel\x1b[0m");
}

Pixel::Pixel(const char *pId, const Point &p) : Figure(pId, p)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation de Pixel\x1b[0m");
}

Pixel::Pixel(const char *pId, const Point &p, const Couleur *pCouleur) : Figure(pId, p, pCouleur)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation 1 de Pixel\x1b[0m");
}


Pixel::~Pixel() 
{
	Trace("\x1b[37m\x1b[41m Destructeur de la classe Pixel\x1b[0m");
}


Pixel::Pixel(const Pixel& p) : Figure(p)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Constructeur de copie de la classe Pixel\x1b[0m");
}

void Pixel::Dessine(void) const {
	Trace("\x1b[36mDans Dessine de la classe Pixel\x1b[0m");
	WindowSDL::drawPixel(pCouleur->getRouge(), pCouleur->getVert(), pCouleur->getBleu(), position.getX(), position.getY());
}

ostream& operator<<(ostream& s, const Pixel& pixel)
{
	s << pixel.getId() << " [Position : " << pixel.position.getX() << ", " << pixel.position.getY() << "]";
	if(pixel.pCouleur != NULL) {
		if(pixel.pCouleur->getNom() != NULL) {
			s << "[Couleur : " << pixel.pCouleur->getNom();
		} 

		s << pixel.pCouleur->getRouge() << ", " << pixel.pCouleur->getVert() << ", " << pixel.pCouleur->getBleu() << "]"; 
	}
	return s;
}
