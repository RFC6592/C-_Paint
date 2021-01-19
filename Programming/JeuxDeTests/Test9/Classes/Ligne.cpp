#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Ligne.h"
#include "Ecran.h"
#include "./WindowSDL/WindowSDL.h"

#include <regex>
#include "./Exception/BaseException.h"


#include <fstream>

using namespace std;

Ligne::Ligne() : Figure()
{
	Trace("Constructeur par defaut de la classe Ligne");
}


Ligne::~Ligne() 
{
	Trace("\x1b[37m\x1b[41m Destructeur de la classe Ligne\x1b[0m");
}


Ligne::Ligne(const char *pId, const Point &p1, const Point &p2, const Couleur *pCouleur) : Figure(pId, p1, pCouleur)
{
	setExtremite(p2);
	this->setId(pId);
}


Ligne::Ligne(const Ligne& ligne) : Figure(ligne)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Constructeur de copie\x1b[0m");
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
	WindowSDL::drawLine(pCouleur->getRouge(), pCouleur->getVert(), pCouleur->getBleu(), position.getX(), position.getY(), extremite.getX(), extremite.getY());
}


void Ligne::setId(const char *pId)
{
	Trace("\x1b[34m setId() de la classe Ligne\x1b[0m");	
	if(pId != NULL)
	{
		if(strlen(pId) > 6) throw BaseException("[-] Le nb de caractères est supérieur à 4");
		if( !regex_match(pId, regex("[L-l][0-9]{1,3}")) ) throw BaseException("[-] Format incorrect ! Exemple : L452 (OK) "); 
		else {
			strcpy(this->pId, pId); 
		}
	}
}



ostream& operator<<(ostream& s, const Ligne& ligne)
{
	s << ligne.getId() << " [Position : " << ligne.getExtremite().getX() << ", " << ligne.getExtremite().getY() << "]";
	s << " [Position : " << ligne.getPosition().getX() << ", " << ligne.getPosition().getY() << "]";
	if(ligne.getCouleur() != NULL) {
		if(ligne.getCouleur()->getNom() != NULL) {
			s << "[Couleur : " << ligne.getCouleur()->getNom();
		} 
		s << " : " << ligne.getCouleur()->getRouge() << ", " << ligne.getCouleur()->getVert() << ", " << ligne.getCouleur()->getBleu() << "]"; 
	}
	return s;
}



void Ligne::Save(std::ofstream& fichier) const
{
	extremite.Save(fichier);
	Figure::Save(fichier);
}

void Ligne::Load(std::ifstream& fichier)
{
	extremite.Load(fichier);
	Figure::Load(fichier);
}

