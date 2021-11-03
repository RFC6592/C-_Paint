#include <stdlib.h>
#include <stdio.h>
using namespace std;
#include "Bouton.h"
#include "BoutonCouleur.h"
#include "../Ecran.h"
#include "../WindowSDL/WindowSDL.h"
#include <fstream>


BoutonCouleur::BoutonCouleur() : Bouton()
{
	setCouleur(NULL);
}


BoutonCouleur::BoutonCouleur(const Point &p1, const Point &p2) : Bouton(p1, p2)
{
	setCouleur(NULL);
}

BoutonCouleur::BoutonCouleur(const char *pNewNom, const Point &p1, const Point &p2) : Bouton(pNewNom, p1, p2)
{
	setCouleur(NULL);
}

BoutonCouleur::BoutonCouleur(const BoutonCouleur &b) : Bouton(b)
{
	setCouleur(b.getCouleur());
}

BoutonCouleur::~BoutonCouleur()
{
}

/**
* @override
*/  
void BoutonCouleur::setSelected(bool newSelected)
{
	this->selected = newSelected;

	if(getSelected() == true) {
		if(pCouleur) {
			WindowSDL::drawRectangle(0, 255, 0, getP1().getX(), getP1().getY(), (getP2().getX() - getP1().getX()), (getP2().getY() - getP1().getY()));
		} else { cout << "\x1b[31mPas de couleurs\x1b[0m" << endl;  }	
	} else {
		WindowSDL::drawRectangle(195, 195, 195, getP1().getX(), getP1().getY(), (getP2().getX() - getP1().getX()), (getP2().getY() - getP1().getY()));
	}
}


Couleur* BoutonCouleur::getCouleur() const 
{ 
	return this->pCouleur; 
}

void BoutonCouleur::setCouleur(Couleur *newCouleur)
{
	this->pCouleur = newCouleur;
	if(this->pCouleur) 
		WindowSDL::fillRectangle(pCouleur->getRouge(), pCouleur->getVert(), pCouleur->getBleu(), (getP1().getX() + 10), (getP1().getY() + 10), (getP2().getX() - getP1().getX() - 20) , (getP2().getY() - getP1().getY() - 20));
	

}


std::ostream &operator<<(std::ostream &s, const BoutonCouleur &b)
{
	s << "Nom: " << b.getNom() << "\n" << b.getP1() << " " << b.getP2() << std::endl;
	s << "Selected: " << b.getSelected() << std::endl;
	return s;
}

