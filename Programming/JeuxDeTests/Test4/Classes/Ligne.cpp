#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Ligne.h"
#include "Ecran.h"
#include "./WindowSDL/WindowSDL.h"
using namespace std;

Ligne::Ligne() : Figure()
{
	Trace("Constructeur par defaut de la classe Ligne");
}


Ligne::~Ligne() 
{
	Trace("Destructeur de la classe Ligne");
}


Ligne::Ligne(const char *pId, const Point &p1, const Point &p2, const Couleur *pCouleur) : Figure(pId, p1, pCouleur)
{
	setExtremite(p2);
}


Ligne::Ligne(const Ligne& ligne) : Figure(ligne)
{
	Trace("Constructeur de copie");
	extremite.setX(ligne.getExtremite().getX());
	extremite.setY(ligne.getExtremite().getY());
}


Point Ligne::getExtremite(void) const
{
	return extremite;
}


void Ligne::setExtremite(const Point &p)
{
	extremite.setX(p.getX());
	extremite.setY(p.getY());
}


void Ligne::Dessine(void) const {
	Trace("Dans la methode Dessine de la classe Ligne");
	WindowSDL::drawLine(pCouleur->getRouge(), pCouleur->getVert(), pCouleur->getBleu(), position.getX(), position.getY(), 		extremite.getX(), extremite.getY());
}



ostream& operator<<(ostream& s, const Ligne& ligne)
{
	s << ligne.getId() << " [Position : " << ligne.getExtremite() << "]";
	s << " [Position : " << ligne.getPosition() << "]";
	if(ligne.getCouleur() != NULL) {
		if(ligne.getCouleur()->getNom() != NULL) {
			s << "[Couleur : " << ligne.getCouleur()->getNom();
		} 
		s << " : " << ligne.getCouleur() << "]"; 
	}
	return s;
}
