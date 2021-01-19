#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../Ecran.h"
#include <regex>
using namespace std;
#include "ToolBar.h"
#include <fstream>
#include "../Exception/BaseException.h"


ToolBar::ToolBar() {};
ToolBar::ToolBar(const ToolBar& f) {};
ToolBar::~ToolBar() {};		


void ToolBar::ajouteBoutonCouleur(const BoutonCouleur &b)
{
	this->boutonsCouleur.insere(b);
	this->boutonsCouleur.Affiche();
}

void ToolBar::ajouteBoutonFigure(const Bouton &b)
{
	this->boutonsFigures.insere(b);
}

void ToolBar::setBoutonUndo(const Bouton &b)
{
	this->boutonUndo = b;
}

void ToolBar::setBoutonMenu(const Bouton &b)
{
	this->boutonMenu = b;
}



void ToolBar::ajouteCouleur(Couleur* c)
{
	Iterateur<BoutonCouleur> itC(this->boutonsCouleur);
	while(!itC.end() && (&itC)->getCouleur() != NULL) itC++; // Tant que la couleur != NULL

	if((&itC)->getCouleur() == NULL){ // Si la couleur est = à NULL
		this->boutonsCouleur.Affiche();
		(&itC)->setCouleur(c);
	}
}

const char* ToolBar::getNomCouleur(const char* nomBoutonCouleur)
{

	Iterateur<BoutonCouleur> itC(this->boutonsCouleur);
	for(itC.reset(); !itC.end(); itC++)
	{
		BoutonCouleur &bouton = *itC;
		if( strcmp( bouton.getNom(), nomBoutonCouleur) == 0) {
			return bouton.getCouleur()->getNom();
		}
	}
	return NULL;
}



const char* ToolBar::clic(int x, int y)
{
	// --------------- Liste boutons figures ---------------
	Iterateur<Bouton> it(this->boutonsFigures);
	for(it.reset(); !it.end(); it++)
	{
		Bouton &bouton = *it;
		if(bouton.clic(x, y))
		{
			undoSelectionFigure();
			bouton.setSelected(true);
			return bouton.getNom();
		}
	}

	// ---------- Liste boutons couleur ---------------
	Iterateur<BoutonCouleur> itC(this->boutonsCouleur);
	while(!itC.end())
	{
		BoutonCouleur &boutonC = *itC;
		if(boutonC.clic(x, y))
		{
			undoSelectionCouleur();
			boutonC.setSelected(true);
			return boutonC.getNom();
		}
		itC++;
	}

	if(this->boutonUndo.clic(x, y))
	{
		return this->boutonUndo.getNom();
	}
	
	if(this->boutonMenu.clic(x, y))
	{
		return this->boutonMenu.getNom();
	}
	
	return NULL;
}



Couleur* ToolBar::getCouleurSelectionnee()
{
	Iterateur<BoutonCouleur> itC(this->boutonsCouleur);
	for(itC.reset(); !itC.end(); itC++)
	{
		BoutonCouleur &bouton = *itC;
		if(bouton.getSelected())
		{
			return bouton.getCouleur();
		}
	}
	return NULL;
}


const char* ToolBar::getFigureSelectionnee()
{
	Iterateur<Bouton> it(this->boutonsFigures);
	for(it.reset(); !it.end(); it++)
	{
		Bouton &bouton = *it;
		if(bouton.getSelected())
		{
			return bouton.getNom();
		}
	}
	return NULL;
}


Couleur* ToolBar::getCouleur(const char *nom)
{
	Iterateur<BoutonCouleur> itC(this->boutonsCouleur);
	for(itC.reset(); !itC.end(); itC++)
	{
		BoutonCouleur &bouton = *itC;
		if(!strcmp(bouton.getNom(), nom))
		{
			return bouton.getCouleur();

		}
	}
	return NULL;
}


void ToolBar::undoSelectionFigure()
{
	Iterateur<Bouton> it(this->boutonsFigures);
	for(it.reset(); !it.end(); it++)
	{
		Bouton &bouton = *it;
		if(bouton.getSelected()) // Si ça retourne true
		{
			bouton.setSelected(false);
		}
	}
}


void ToolBar::undoSelectionCouleur()
{
	Iterateur<BoutonCouleur> itC(this->boutonsCouleur);
	for(itC.reset(); !itC.end(); itC++)
	{
		BoutonCouleur &bouton = *itC;
		if(bouton.getSelected())
		{
			bouton.setSelected(false);
		}
	}
}

