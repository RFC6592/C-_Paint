/** 
* @author EZZAYRI Sami 2226
* @date 9/10/20
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "Ecran.h"
#include "Figure.h"
#include "Couleur.h"
#include "Point.h"

using namespace std;

#include <regex>
#include "./Exception/BaseException.h"


/**
* @brief Initialisation du compteur 
*/
int Figure::compteur = 0; // Initialisation c'est à ce stade que l'emplacement memoire est reserve

/** 
* @brief Methode static qui se charge de retourner le nb d'objets de type Couleur 
* @return int compteur
*/
int Figure::getCompteur(){ return compteur; }
	




/**
* @brief Constructeur par defaut
* @param void
* @return void 
*/
Figure::Figure()
{
	Trace("\x1b[37m\x1b[40m Constructeur par defaut de la classe Figure\x1b[0m");

	setId("0");
	setPosition(Point());

	this->pCouleur = NULL;

	compteur++;
}



/** 
* @brief Constructeur d'initialisation avec 3 parametres 
* @param const char *pId
* @param const Point &position
* @param const Couleur *pCouleur
*/
Figure::Figure(const char *pId, const Point &position, const Couleur *pCouleur)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation de la classe Figure 1\x1b[0m");

	setId(pId);
	setPosition(position);

	this->pCouleur = NULL;
	setCouleur(pCouleur);

	compteur++;
}



/** 
* @brief Constructeur d'initialisation avec 2 parametres 
* @param const char *newPid
* @param const Point &position
*/
Figure::Figure(const char *newPid, const Point &position)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation de la classe Figure 2\x1b[0m");

	if(newPid == NULL) {
		throw invalid_argument("Erreur pId !");
	} else {

		setId(newPid);	
		setPosition(position);
		this->pCouleur = NULL;
		compteur++;
	}
	
}



/**
* @brief Constructeur de copie de la classe Figure 
*/
Figure::Figure(const Figure &f) 
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Constructeur de copie de la classe Figure\x1b[0m");	
	
	setId(f.getId());
	setPosition(f.getPosition());
	setCouleur(f.getCouleur());

	compteur++;
}



/** 
* @brief Destructeur de la classe Figure 
*/
Figure::~Figure()
{
	Trace("\x1b[37m\x1b[41m Destructeur de la classe Figure\x1b[0m");

	compteur--;
}



/** 
* @brief Setters 
*/
void Figure::setId(const char *newpId)
{
	Trace("\x1b[34m setId() de la classe Figure\x1b[0m");	
}


Figure::Figure(const Point &p, const Couleur *pCouleur)
{
	this->pCouleur = NULL;
	setCouleur(pCouleur);
	setPosition(p);
}

Figure::Figure(const Point &p)
{
	setPosition(p);
}


/** 
* @brief Methode qui permet de donner une nouvelle position
* @param const Point& pos
*/
void Figure::setPosition(const Point &pos)
{
	Trace("\x1b[34m setPosition() de la classe Figure\x1b[0m");

	this->position = pos;
}



/** 
* @brief Methode qui permet de donner une nouvelle Couleur
* @param const Couleur *pCouleur
*/
void Figure::setCouleur(const Couleur *pCouleur)
{
	Trace("\x1b[34m setCouleur() de la classe Figure\x1b[0m");	
	this->pCouleur = pCouleur;
}



/** 
* @brief Getters
*/
const char* Figure::getId() const { return pId; }
Point Figure::getPosition() const { return this->position; }
const Couleur* Figure::getCouleur() const { return this->pCouleur; }



/** 
* @brief Afficher l'Id, la position(x,y) et la couleur 
*/
void Figure::Affiche() const
{
	Trace("\x1b[34m Affiche() de la classe Figure\x1b[0m");

	cout << "\x1b[33m> Id : " << getId() << endl;

	getPosition().Affiche();

	if(getCouleur() != NULL) 
		getCouleur()->Affiche();
}



/**
* @brief Methode qui permet de modifier l'objet courant par une autre Figure
* @param const Figure& f
* @return retourne l'objet courant
*/
Figure& Figure::operator=(const Figure& f)
{
	Trace("\x1b[35m\x1b[1m Dans la methode operator=() de la classe Figure\x1b[0m");

	setId(f.pId);
	setPosition(f.position);
	setCouleur(f.pCouleur);
	
	return (*this); // Retourne l'objet courant
}


ostream& operator<<(ostream& s, const Figure& f)
{
	s << f.getId() << " [Position : " << f.position.getX() << ", " << f.position.getY() << "]";
	if(f.pCouleur != NULL) {
		s << "[Couleur : " << f.pCouleur->getRouge() << ", " << f.pCouleur->getVert() << ", " << f.pCouleur->getBleu() << "]"; 
	}
	return s;
}

