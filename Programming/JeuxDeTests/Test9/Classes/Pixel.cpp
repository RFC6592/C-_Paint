#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Pixel.h"
#include "Ecran.h"

#include <regex>
#include "./Exception/BaseException.h"

#include "./WindowSDL/WindowSDL.h"
using namespace std;


Pixel::Pixel() : Figure()
{
	Trace("\x1b[37m\x1b[40m Constructeur par defaut de Pixel\x1b[0m");
}


Pixel::Pixel(const char *pId, const Point &p) : Figure(p)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation de Pixel\x1b[0m");
	this->setId(pId);
}


Pixel::Pixel(const char *pId, const Point &p, const Couleur *pCouleur) : Figure(p, pCouleur)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation 1 de Pixel\x1b[0m");
	this->setId(pId);
}


void Pixel::setId(const char *pId)
{

	if(pId != NULL)
	{
		if(strlen(pId) > 6) throw BaseException("[-] Le nb de caractères est supérieur à 4");
		if( !regex_match(pId, regex("[P-p][0-9]{1,3}")) ) throw BaseException("[-] Format incorrect ! Exemple : P452 (OK) "); 
		else {
			strcpy(this->pId, pId); 
		}
	}

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




void Pixel::Save(std::ofstream& fichier) const
{
	Figure::Save(fichier);
}

void Pixel::Load(std::ifstream& fichier)
{
	Figure::Load(fichier);
}

