#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
#include "Rectangle.h"
#include "Ecran.h"
#include <fstream>

#include "./WindowSDL/WindowSDL.h"

#include <regex>
#include "./Exception/BaseException.h"

/**
* @brief Constructeur par defaut de la classe Rectangle
*/
Rectangle::Rectangle() : Figure()
{
	setDimX(0u);
	setDimY(0u);
	setRempli(false);
}


/**
* @brief Constructeur d'initialisation de la classe Rectangle
*/
Rectangle::Rectangle(const char *pId, const Point &p1, int dimX, int dimY, bool rempli, const Couleur *c) : Figure(p1, c)
{
	setDimX(dimX);
	setDimY(dimY);
	setRempli(rempli);
	this->setId(pId);
}

/**
* @brief Destructeur de la classe Rectangle
*/
Rectangle::~Rectangle()
{
}


/**
* @brief Constructeur de copie de la classe Rectangle
*/
Rectangle::Rectangle(const Rectangle &r) :  Figure(r)
{
	setDimX(r.getDimX());
	setDimY(r.getDimY());
	setRempli(r.isRempli());
}


ostream& operator<<(ostream& s, const Rectangle &r)
{
	s << r.getId() << " [ Rectangle : Position(" << r.getPosition() << "), DimX=" << r.getDimX() << ", DimY=" << r.getDimY() << ", Rempli" << r.isRempli();
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
	WindowSDL::drawRectangle(getCouleur()->getRouge(), getCouleur()->getVert(), getCouleur()->getBleu(), getPosition().getX(), getPosition().getY(), getDimX() , getDimY());
	if(isRempli())
	{
		WindowSDL::fillRectangle(getCouleur()->getRouge(), getCouleur()->getVert(), getCouleur()->getBleu(), getPosition().getX(), getPosition().getY(), getDimX(), getDimY());
	}
}



void Rectangle::setId(const char *pId) throw (BaseException)
{
	if(pId != NULL)
	{
		if(strlen(pId) > 6) throw BaseException("[-] Le nb de caractères est supérieur à 4");
		if( !regex_match(pId, regex("[R-r][0-9]{1,3}")) ) throw BaseException("[-] Format incorrect ! Exemple : R452 (OK) "); 
		else {
			strcpy(this->pId, pId); 
		}
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
 

void Rectangle::Save(std::ofstream& fichier) const
{
	int tmp = this->dimX;
	fichier.write((char *)&tmp, sizeof(int));
	tmp = this->dimY;
	fichier.write((char *)&tmp, sizeof(int));
	bool tmpBool = this->rempli;
	fichier.write((char *)&tmpBool, sizeof(bool));

	Figure::Save(fichier);

}

void Rectangle::Load(std::ifstream& fichier)
{
	int tmp;
	bool tmpBool;
	fichier.read((char *)&tmp, sizeof(int));
	this->setDimX(tmp);
	fichier.read((char *)&tmp, sizeof(int));
	this->setDimY(tmp);
	fichier.read((char *)&tmpBool, sizeof(bool));
	this->setRempli(tmpBool);

	Figure::Load(fichier);
}

