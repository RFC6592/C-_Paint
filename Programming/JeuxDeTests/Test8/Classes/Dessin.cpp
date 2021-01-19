#include <stdlib.h>
#include <stdio.h>
#include <iostream>


#include "Ecran.h"
#include "Dessin.h"
#include "./Exception/BaseException.h"

using namespace std;


Dessin::Dessin()
{
	Trace("Constructeur par defaut");
	this->fond = Couleur::VERT;
}

Dessin::Dessin(const Couleur& f)
{
	Trace("Dans le constructeur d'initialisation");
	this->fond = f;
}

Dessin::~Dessin()
{
	Trace("Dans la méthode Dessine()");
	Iterateur<Figure *> it(this->figures);
	for(it.last(); !it.end(); it--)
		delete it;

}

void Dessin::ajouteCouleur(const Couleur& c)
{
	Trace("Dans la méthode ajouteCouleur(const Couleur& c);");
	this->palette.insere(c);
}

/*
* @brief Méthode permettant de récuperer l'adresse de la Couleur qui est dans la palette
* @param const char *nomCouleur, le nom de la Couleur que on cherche
* @return Il faut retourner l'adresse de la Couleur
*/
Couleur* Dessin::recupererCouleur(const char *nomCouleur)
{
	Iterateur<Couleur> it(this->palette);
	for(it.reset(); !it.end(); it++)
	{ 
		if(strcmp( ((Couleur)it).getNom(), nomCouleur) == 0) {
			return &it; // TODO: Il faut retourner l'adresse de la couleur dans la palette
		} 
	}
	return NULL;
}

void Dessin::ajouteFigure(Figure *pf, const char *nomCouleur) // Rectangle -> Lavande
{
	if(isExist(nomCouleur))
	{
		if(!isNameExist(pf->getId())) { 
			pf->setCouleur(recupererCouleur(nomCouleur)); // TODO: Il me faut l'adresse de la couleur qui dans la palette
			this->figures.push(pf);
		} else { throw BaseException("Err : Nous avons déjà une Figure sous cet ID"); }
	} else {
		throw BaseException("Err : Nous n'avons pas trouvé la couleur");
	}
		
}

bool Dessin::isExist(const char *nomCouleur)
{
	Iterateur<Couleur> it(this->palette);
	for(it.reset(); !it.end(); it++)
	{
		if(strcmp( ((Couleur)it).getNom(), nomCouleur) == 0)
			return true;
	}

	return false;	
}


bool Dessin::isNameExist(const char *nomId)
{
	Iterateur<Figure *> it(this->figures);
	for(it.reset(); !it.end(); it++)
	{
		if(strcmp( ((Figure *)it)->getId(), nomId) == 0)
			return true;
	}

	return false;	
}


//================================================

void Dessin::Dessine()
{
	Iterateur<Figure *> it(this->figures);
	for(it.last(); !it.end(); it--)
		((Figure *)it)->Dessine();
	
}

void Dessin::undo()
{
	this->figures.pop();
	
}

void Dessin::affichePalette()
{
	Trace("********* Couleurs ***************");
	int nbCouleurs = 0;
	Iterateur<Couleur> it(this->palette);
	for (it.reset() ; !it.end() ; it++) {
   	((Couleur)it).Affiche();
		nbCouleurs++;
	}
	Trace("************** Nb de couleurs = %d **************", nbCouleurs);

}


void Dessin::afficheFigures()
{
	Trace("********* Figures ***************");
	int nbFigures = 0;
	Iterateur<Figure *> it(this->figures);
	for(it.reset(); !it.end(); it++) {
		((Figure *)it)->Affiche();
		nbFigures++;
	}
	Trace("************** Nb de figures = %d **************", nbFigures);
}


Couleur Dessin::getFond()
{
	return this->fond;
}

void Dessin::setFond(const Couleur& c)
{
	this->fond = c;
}

