/** 
* @author EZZAYRI Sami 2226
* @date 9/10/20
*/
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <ctype.h>
using namespace std;

#include "Ecran.h"
#include "Couleur.h"


int aValidColor(int valeur);


const Couleur Couleur::ROUGE(255, 0, 0, "Rouge");
const Couleur Couleur::VERT(0, 255, 0, "Vert");
const Couleur Couleur::BLEU(0, 0, 255, "Bleu");




/**
* @brief Initialisation du compteur 
*/
int Couleur::compteur = 0;

/** 
* @brief Methode static qui se charge de retourner le nb d'objets de type Couleur 
* @return int compteur
*/
int Couleur::getCompteur(){ return compteur; }




/**
* @brief Constructeur par defaut
*/
Couleur::Couleur():rouge(0u),vert(0u),bleu(0u),pNom(NULL)
{
	Trace("\x1b[37m\x1b[40m Constructeur par defaut de la classe Couleur\x1b[0m");
	
	compteur++;
}



/** 
* @brief Constructeur d'initialisation avec 3 parametres 
* @param int newRouge
* @param int newVert
* @param int newBleu
*/

Couleur::Couleur(int newRouge, int newVert, int newBleu):rouge(newRouge),vert(newVert),bleu(newBleu),pNom(NULL)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation de la classe Couleur 1\x1b[0m");

	compteur++;
}



/** 
* @brief Constructeur d'initialisation avec 4 parametres 
* @param int newRouge
* @param int newVert
* @param int newBleu
* @param const char *pNewNom
*/
Couleur::Couleur(int newRouge, int newVert, int newBleu, const char *pNewNom):rouge(newRouge),vert(newVert),bleu(newBleu),pNom(NULL)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation de la classe Couleur 2\x1b[0m");
	
	if(pNewNom != NULL) setNom(pNewNom);

	compteur++;
}



/** 
* @brief Destructeur de la classe Couleur 
*/
Couleur::~Couleur()
{
	Trace("\x1b[37m\x1b[41m Destructeur de la classe Couleur\x1b[0m");

	if (pNom) delete pNom;
	compteur--;
}



/**
* @brief Methode qui se charge d'afficher les informations sur une couleur 
*/
void Couleur::Affiche() const
{
	Trace("\x1b[34m Affiche() de la classe Couleur\x1b[0m");

	if(getNom() != NULL) 
		cout << "\x1b[33m> Le nom de la couleur : \x1b[0m" << getNom() << endl;

	cout << "\x1b[31m> Rouge : \x1b[0m" << getRouge() << endl;
	cout << "\x1b[32m> Vert : \x1b[0m" << getVert() << endl;
	cout << "\x1b[34m> Bleu : \x1b[0m" << getBleu() << endl;
}



/** 
* @brief Methode qui permet de donner une valeur pour le membre rouge
* @param int valeurRouge
*/
void Couleur::setRouge(int valeurRouge) 
{
	Trace("\x1b[34m setRouge() de la classe Couleur\x1b[0m");

	if(valeurRouge < 0 || valeurRouge > 255)
		this->rouge = abs(valeurRouge % 255);
	else this->rouge = abs(valeurRouge);


}



/** 
* @brief Methode qui permet de donner une valeur pour le membre bleu
* @param int valeurBleu
*/
void Couleur::setBleu(int valeurBleu)
{
	Trace("\x1b[34m setBleu() de la classe Couleur\x1b[0m");

	if(valeurBleu < 0 || valeurBleu > 255)
		this->bleu = abs(valeurBleu % 255);
	else this->bleu = abs(valeurBleu);


}



/** 
* @brief Methode qui permet de donner une valeur pour le membre vert
* @param int valeurVert
*/
void Couleur::setVert(int valeurVert)
{
	Trace("\x1b[34m setVert() de la classe Couleur\x1b[0m");

	if(valeurVert < 0 || valeurVert > 255)
		this->vert = abs(valeurVert % 255);
	else this->vert = abs(valeurVert);

}



/** 
* @brief Methode qui permet de donner un nouveau nom
* @param const char *newNom
*/
void Couleur::setNom(const char *newNom)
{
	Trace("\x1b[34m setNom() de la classe Couleur\x1b[0m");

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



/** 
* @brief Constructeur de copie 
*/
Couleur::Couleur(const Couleur& c):pNom(NULL)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Constructeur de copie de la classe Couleur\x1b[0m");	

	setRouge(c.getRouge());
	setVert(c.getVert());
	setBleu(c.getBleu());
	setNom(c.getNom());

	compteur++;
}



/** 
* @brief Accesseurs 
*/
int Couleur::getRouge() const { return this->rouge; }
int Couleur::getBleu() const { return this->bleu; }
int Couleur::getVert() const { return this->vert; }
char* Couleur::getNom() const { return this->pNom; } 


// =========================== SURCHARGE DES OPERATEURS ===========================


/**
* @brief Methode qui permet de modifier l'objet courant par une autre Couleur
* @param const Couleur& couleur
* @return retourne l'objet courant
*/
Couleur& Couleur::operator=(const Couleur& c) 
{
	Trace("\x1b[35m\x1b[1m Dans la methode operator=() de la classe Couleur\x1b[0m");

	setNom(c.getNom());
	setRouge(c.getRouge());
	setVert(c.getVert());
	setBleu(c.getBleu());
	
	return (*this);
}



/**
* @brief Methode qui permet de realiser une addition entre l'objet courant et une Couleur
* @param const Couleur& couleur
* @return retourne l'objet courant
*/
Couleur Couleur::operator+(const Couleur& couleur) const
{
	Couleur c (*this); // Un objet qui est une copie de l'objet courant

	Trace("\x1b[35m\x1b[1m Dans la methode operator+() de la classe Couleur\x1b[0m");	 

	c.setRouge((c.getRouge() + couleur.getRouge())/2);
	c.setVert((c.getVert() + couleur.getVert())/2);
	c.setBleu((c.getBleu() + couleur.getBleu())/2);
	
	// Si il y a pas de nom de couleur pour l'objet courant 
	if(c.getNom()) c.setNom(couleur.getNom());

	return c;
}



/**
* @brief Méthode qui nous permet de realiser une addition une Couleur + nombre
* @param int valCouleur
*/
Couleur Couleur::operator+(int valCouleur) const
{
	Couleur c(*this); // Objet 'c' qui est une copie de l'objet courant

	Trace("\x1b[35m\x1b[1m Dans la fonction operator+() de la classe Couleur\x1b[0m");	

	c.setRouge((c.getRouge() + valCouleur)/2);
	c.setVert((c.getVert() + valCouleur)/2);
	c.setRouge((c.getRouge() + valCouleur)/2);

	return c;
}



/**
* @brief Fonction libre, cette fonction nous permet de realiser une addition entre un nombre + Couleur
* @param int valCouleur
* @param const Couleur& couleur
*/
Couleur operator+(int valCouleur, const Couleur& couleur)
{
	Couleur c; // Creation d'un objet Couleur 
	Trace("\x1b[35m\x1b[1m Dans la fonction operator+() de la classe Couleur\x1b[0m");	

	c.setRouge((valCouleur + couleur.getRouge())/2);
	c.setVert((valCouleur + couleur.getVert())/2);
	c.setBleu((valCouleur + couleur.getBleu())/2);
	c.setNom(couleur.getNom());

	return c;
}


/**
* @brief Méthode qui nous permet de realiser une soustraction entre une Couleur et un nombre
* @param int valCouleur
*/
Couleur Couleur::operator-(int valCouleur) const
{
	Couleur c(*this); // Copie de l'objet courant
	Trace("\x1b[35m\x1b[1m Dans la fonction operator-() de la classe Couleur\x1b[0m");

	c.setRouge(c.getRouge() - valCouleur);
	c.setVert(c.getVert() - valCouleur);
	c.setBleu(c.getBleu() - valCouleur);

	return c;
}


int& Couleur::operator[](const char* couleur)
{	
	if(couleur != NULL) 
	{
		if(strncmp(couleur, "rouge", 5) == 0) return rouge;
		if(strncmp(couleur, "vert", 4) == 0) return vert;
		if(strncmp(couleur, "bleu", 4) == 0) return bleu;
		else throw invalid_argument("Cette couleur n'existe pas !");
	} 
	else {
		throw invalid_argument("couleur est NULL");
	}
}




/** 
* @brief Post-decrementation / pre-decrementation ET post-incrementation / pre-incrementation
*/
Couleur Couleur::operator++()
{
	(*this) = (*this) + 1;
	return (*this);
}

Couleur Couleur::operator++(int) 
{
	Couleur c(*this); // Copie de l'objet courant
	(*this) = (*this) + 1;
	return c;
}

Couleur Couleur::operator--()
{
	(*this) = (*this) - 1;
	return (*this);
}

Couleur Couleur::operator--(int)
{
	Couleur c(*this); // Copie de l'objet courant
	(*this) = (*this) - 1;
	return c;
}



ostream& operator<<(ostream& s, const Couleur& c)
{
	s << "\nNom: " << c.getNom() << "\nRouge: " << c.getRouge() << "\nVert: " << c.getVert() << "\nBleu: " << c.getBleu();
	return s;
}



istream& operator>>(istream& s, Couleur& c)
{
	// Declaration des variables de travail
	int r, v, b;
	char *c_pNom;
	c_pNom = new char[15];
	
	// Traitement
	cout << "\x1b[33m\nEncodage de la Couleur\x1b[0m" << endl;
	cout << "\x1b[33m> Nom de la couleur: ";
	cin >> c_pNom;
 	cout << "\x1b[33m> Rouge: ";
	cin >> r;
	cout << "\x1b[33m> Vert: ";
	cin >> v;
	cout << "\x1b[33m> Bleu: " << "\x1b[0m";
	cin >> b;
	
	
	if(c_pNom != NULL) c.setNom(c_pNom);
	else throw invalid_argument("Erreur au niveau de p_nom");

	c.setRouge(aValidColor(r));
	c.setVert(aValidColor(v));
	c.setBleu(aValidColor(b));
	
	return s;
}



/**
* @brief Fonction qui se charge de determiner si une couleur (rgb) est correct.
* @param int valeur, la valeur qui doit logiquement se trouver entre 0 -> 255
*/
int aValidColor(int valeur)
{
	if(valeur >= 0 || valeur <= 255) return valeur;
	else return abs(valeur % 255);
}



