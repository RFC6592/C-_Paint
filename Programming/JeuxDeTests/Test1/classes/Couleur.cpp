
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

#include "Couleur.h"



Couleur::Couleur()
{
	std::cout << "[1] ------- Constructeur -------" << std::endl;
	#ifdef DEBUG
		std::cout << "\x1b[32m[[ DEBUG \x1b[31m" << __FILE__ << ":" <<__LINE__ << "]]\x1b[0m" << std::endl; 
	#endif	
	setRouge(0u);
	setVert(0u);
	setBleu(0u);
	pNom = NULL;
}


Couleur::~Couleur()
{
	std::cout << "[+] ------- Destructeur -------" << std::endl;
	#ifdef DEBUG
		std::cout << "\x1b[32m[[ DEBUG \x1b[31m" << __FILE__ << ":" <<__LINE__ << "]]\x1b[0m" << std::endl; 
	#endif	
	if (this->pNom) 
		delete this->pNom;
}

Couleur::Couleur(const int newRouge, const int newVert, const int newBleu)
{
	std::cout << "[3] ------- Constructeur -------" << std::endl;
	#ifdef DEBUG
		std::cout << "\x1b[32m[[ DEBUG \x1b[31m" << __FILE__ << ":" <<__LINE__ << "]]\x1b[0m" << std::endl; 
	#endif	
	setRouge(newRouge);
	setVert(newVert);
	setBleu(newBleu);
	pNom = NULL;
}

Couleur::Couleur(const int newRouge, const int newVert, const int newBleu, const char *pNewNom)
{
	std::cout << "[2] ------- Constructeur -------" << std::endl;
	#ifdef DEBUG
		std::cout << "\x1b[32m[[ DEBUG \x1b[31m" << __FILE__ << ":" <<__LINE__ << "]]\x1b[0m" << std::endl; 
	#endif		
	setRouge(newRouge);
	setVert(newVert);
	setBleu(newBleu);
	if(pNewNom != NULL)
		setNom(pNewNom);


}

void Couleur::Affiche() const
{
	std::cout << "---------------------------------------" << std::endl;
	std::cout << "\x1b[33m> Le nom de la couleur : \x1b[0m" << pNom << std::endl;
	std::cout << "\x1b[31m> Rouge : \x1b[0m" << rouge << std::endl;
	std::cout << "\x1b[32m> Vert : \x1b[0m" << vert << std::endl;
	std::cout << "\x1b[34m> Bleu : \x1b[0m" << bleu << std::endl;
	std::cout << "---------------------------------------" << std::endl; 
}

// ===== Setters =====

void Couleur::setRouge(const int valeurRouge) 
{
	
	if(valeurRouge < 0 || valeurRouge > 255)
		throw invalid_argument("\x1b[31mValeur invalide !\x1b[0m");
		
	this->rouge = valeurRouge;
}
void Couleur::setBleu(const int valeurBleu)
{
	if(valeurBleu < 0 || valeurBleu > 255)
		throw invalid_argument("\x1b[31mValeur invalide !\x1b[0m");
	
	this->bleu = valeurBleu;

}
void Couleur::setVert(const int valeurVert)
{
	if(valeurVert < 0 || valeurVert > 255)
		throw invalid_argument("\x1b[31mValeur invalide !\x1b[0m");
		
	this->vert = valeurVert;
}
void Couleur::setNom(const char *newNom)
{
	
	if(newNom != NULL) {
		pNom = new char[strlen(newNom)+1];
		strcpy(pNom, newNom);
	} else {
		throw invalid_argument("\x1b[ 31mChaine vide !\x1b[0m");
	}
}

Couleur::Couleur(const Couleur& c)
{
	#ifdef DEBUG
		std::cout << "\x1b[32m[[ DEBUG \x1b[31m" << __FILE__ << ":" <<__LINE__ << "]]\x1b[0m" << std::endl; 
	#endif	
	setBleu(c.getBleu());
	setVert(c.getVert());
	setBleu(c.getBleu());
	pNom = NULL;
	setNom(c.getNom());
}


// ===== Getters =====
int Couleur::getRouge() const
{
	return this->rouge;
}
int Couleur::getBleu() const 
{
	return this->bleu;
}

int Couleur::getVert() const
{
	return this->vert;
}
 
const char* Couleur::getNom() const
{
	return this->pNom;
} 

