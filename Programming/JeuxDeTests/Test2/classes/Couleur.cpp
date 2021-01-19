
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

#include "Ecran.h"
#include "Couleur.h"


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

	setNom(pNewNom);

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



