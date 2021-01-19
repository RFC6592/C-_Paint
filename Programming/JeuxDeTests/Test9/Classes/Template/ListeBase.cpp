#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../Ecran.h"
#include "ListeBase.h"
#include "../Couleur.h"
// --
#include "../Figure.h"
#include "../Rectangle.h"
#include "../Ligne.h"
#include "../Pixel.h"

using namespace std;


template <class T>
ListeBase<T>::ListeBase(void) : pTete(NULL)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Dans le constructeur par defaut de la Classe template ListeBase\x1b[0m");
}

template <class T>
ListeBase<T>::ListeBase(const ListeBase<T> &listeCopie) : pTete(NULL)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Dans le constructeur de copie de la classe template ListeBase\x1b[0m");
	
	Cellule<T> *pNewCellule = this->getTete();
	Cellule<T> *pCellulePrecedent = NULL;
	Cellule<T> *pListeCopie = listeCopie.getTete();		

	while(pListeCopie != NULL) // Tant qu'il pointe sur une Cellule
	{
		// On copie la valeur 
		pNewCellule = new Cellule<T>; 
		pNewCellule->valeur = pListeCopie->valeur;
		pNewCellule->pSuivant = NULL;
		
		if(pCellulePrecedent == NULL)  
		{
			this->setTete(pNewCellule); // Note pTete pointe maintenant sur la pNewCellule

		} else {
			pCellulePrecedent->pSuivant = pNewCellule;
		}

		pCellulePrecedent = pNewCellule;
		// On passe à la suite
		pListeCopie = pListeCopie->pSuivant;
		pNewCellule = pNewCellule->pSuivant;
	}

	
}


template <class T>
ListeBase<T>::~ListeBase(void)
{
	Trace("\x1b[37m\x1b[41m Dans le destructeur de la classe template ListeBase\x1b[0m");
	
	
	Cellule<T> *pNewCellule = this->getTete();
	Cellule<T> *pCellulePrecedent = NULL;
	
	if(this->getTete() != NULL) // Si notre pointeur tête pointe effectivement sur une Cellule
	{
		while(pNewCellule != NULL) // Tant que notre pNewCellule pointe sur une Cellule 
		{
			pCellulePrecedent = pNewCellule; // Notre pCellulePrecedent désormais pointe également sur la même Cellule
			pNewCellule = pNewCellule->pSuivant; // On passe à l'autre Cellule
			if(pCellulePrecedent != NULL)
			{
				delete pCellulePrecedent; // On libere la mémoire
			}		
		}
	}	
	
}


template <class T>
bool ListeBase<T>::estVide(void) const
{
	Trace("\x1b[34m Dans la methode estVide() de la classe template ListeBase\x1b[0m");
	return (getNombreElements() == 0) ? true : false;
}


template <class T>
int ListeBase<T>::getNombreElements(void) const
{
	Trace("\x1b[34m Dans la methode getNombreElements() de la classe template ListeBase\x1b[0m");

	int nbElements = 0;
	Cellule<T> *pNewCellule = this->getTete(); // le pNewCellule pointe également sur ce qui est pointé par pTete

	if(this->getTete() != NULL) {
		while(pNewCellule != NULL) // Tant qu'il pointe sur une Cellule
		{
			pNewCellule = pNewCellule->pSuivant; // Notre pNewCellule désormais pointe sur la Cellule suivante
			nbElements++;			
		}
	}
	return nbElements;
	
}


template <class T>
void ListeBase<T>::Affiche(void) const
{
	Trace("\x1b[34m Dans la methode Affiche() de la classe template ListeBase\x1b[0m");
	
	Cellule<T> *pNewCellule = this->getTete();
	int idCellule = 1;	

	if(this->getTete() != NULL)
	{
		while(pNewCellule != NULL)
		{
			
			cout << "\x1b[36m\x1b[7m[+] Cellule : " << idCellule << "\x1b[0m" << endl; 
			cout << "\x1b[35m\x1b[1m> Valeur : \x1b[31m" << pNewCellule->valeur << "\x1b[0m" << endl;
			cout << "-------------------------------------" << endl;
 
			pNewCellule = pNewCellule->pSuivant; // On passe à la Cellule suivante
			idCellule++;
			
		}
		
		
	}

}

template <class T>
ListeBase<T>& ListeBase<T>::operator=(const ListeBase<T> &liste)
{
	Trace("Dans la methode operator=() de la classe template ListeBase");
	
	Cellule<T> *pNewCellule = NULL;
	// [+] On vide notre liste 
	while(this->pTete != NULL)
	{
		pNewCellule = this->pTete->pSuivant; // Il pointe sur la Cellule suivante
		delete this->pTete; 
		this->pTete = pNewCellule;
	}	

	// [+] On va remplir
	Cellule<T> *pListeCopie = liste.getTete();
	Cellule<T> *pCellulePrecedent = NULL;
	Cellule<T> *pListe = new Cellule<T>;
	
	pListe->valeur = pListeCopie->valeur;
	pListe->pSuivant = NULL;

	this->pTete = pListe;
	pCellulePrecedent = pListe; 
	pListeCopie = pListeCopie->pSuivant; // Desormais il pointe sur la Cellule suivante 
	
	while(pListeCopie != NULL)
	{
		Cellule<T> *pNewCellule = new Cellule<T>;
		pNewCellule->valeur = pListeCopie->valeur;
		pNewCellule->pSuivant = NULL;

		pCellulePrecedent->pSuivant = pNewCellule;
		pCellulePrecedent = pNewCellule;

		pListeCopie = pListeCopie->pSuivant;
	}

	return (*this); // Retourne l'objet courant
}


template <class T>
Cellule<T>* ListeBase<T>::getTete(void) const 
{
	return this->pTete;
}


template <class T>
void ListeBase<T>::setTete(Cellule<T> *pNewCellule)
{
	Trace("\x1b[34m Dans la methode setTete() de la classe template ListeBase\x1b[0m");
	if(pNewCellule != NULL)
		this->pTete = pNewCellule;
}



// Instanciation 
template class ListeBase<int>;
template class ListeBase<Couleur>;
template class ListeBase<Rectangle>;
template class ListeBase<Ligne>;
template class ListeBase<Pixel>;
template class ListeBase<Figure *>;
