#include <stdlib.h>
#include <stdio.h>
using namespace std;
#include "Bouton.h"
#include "../Ecran.h"
#include "../WindowSDL/WindowSDL.h"
#include <fstream>


Bouton::Bouton() : pNom(NULL), selected(false)
{
	setNom("B_0");
	setP1(Point());
	setP2(Point());
}

Bouton::Bouton(const Bouton &b)
{
	setP1(b.getP1());
	setP2(b.getP2());
	setNom(b.getNom());
	setSelected(b.getSelected());
}


Bouton::Bouton(const Point &p1, const Point &p2): pNom(NULL), selected(false)
{
	setNom("B_0");
	setP1(p1);
	setP2(p2);
}

Bouton::Bouton(const char *pNewNom, const Point &p1, const Point &p2): pNom(NULL), selected(false)
{
	setNom(pNewNom);
	setP1(p1);
	setP2(p2);
}



Bouton::~Bouton()
{
}



bool Bouton::clic(int x, int y)
{
	return ( x >= getP1().getX() && x <= getP2().getX() && y >= getP1().getY() && y <= getP2().getY()) ? true : false;
}


// ---- Setters ----

void Bouton::setNom(const char* newNom)
{
	if(pNom) delete pNom;

	if(newNom != NULL) 
	{
		pNom = new char[strlen(newNom)+1];
		strcpy(pNom, newNom);
	} 
	else {
		pNom = NULL;
	}

}


void Bouton::setP1(const Point &newp1)
{
	this->p1.setX(newp1.getX());
	this->p1.setY(newp1.getY());
}

void Bouton::setP2(const Point &newp2)
{
	this->p2.setX(newp2.getX());
	this->p2.setY(newp2.getY());
}


void Bouton::setSelected(bool newSelected)
{
	this->selected = newSelected;
	if(newSelected)
		WindowSDL::drawRectangle(0, 255, 0, getP1().getX(), getP1().getY(), (getP2().getX() - getP1().getX()), (getP2().getY() - getP1().getY()));
	else 
		WindowSDL::drawRectangle(195, 195, 195, getP1().getX(), getP1().getY(),  (getP2().getX() - getP1().getX()), (getP2().getY() - getP1().getY()));
}


std::ostream &operator<<(std::ostream &s, const Bouton &b)
{
	s << "Nom: " << b.getNom() << "\n" << b.getP1() << " " << b.getP2() << std::endl;
	s << "Selected: " << b.getSelected() << std::endl;
	return s;
}



// ---- Getters ----
const char* Bouton::getNom() const { return this->pNom; } 
Point Bouton::getP1() const { return this->p1; }
Point Bouton::getP2() const { return this->p2; }
bool  Bouton::getSelected() const { return this->selected; }

