#include <stdio.h>
#include <stdlib.h>

#include "Iterateur.h"

#include "../Couleur.h"
#include "../Ecran.h"


//--- --- ----
#include "../Rectangle.h"
#include "../Ligne.h"
#include "../Pixel.h"

template <class T>
Iterateur<T>::Iterateur(ListeBase<T> &listeCopie) : liste(listeCopie)
{
	this->pCourant = listeCopie.getTete();
}


/**
* @brief Destructeur 
*/
template <class T>
Iterateur<T>::~Iterateur()
{
	Trace("\x1b[31m\x1b[1mDans le destructeur de la Classe \x1b[33mIterateur\x1b[0m");
}


/**
* @brief Méthode qui se charge de réinitialise l'itérateur au debut de la liste
*/
template <class T>
void Iterateur<T>::reset(void)
{
		this->pCourant = liste.getTete();
}


/**
* @brief Méthode qui se charge de positionner l'itérateur sur le dernier élément de la liste
*/
template <class T>
void Iterateur<T>::last(void)
{


	this->pCourant = liste.getTete();
	if(this->pCourant != NULL) {
		while(this->pCourant->pSuivant != NULL) 
			this->pCourant = this->pCourant->pSuivant;
	}
}



/**
* @brief Méthode qui se charge de savoir si l'iterateur est situé au bout de la liste
* @return false ou bien true 
*/
template <class T>
bool Iterateur<T>::end(void) const
{
	if(this->pCourant != NULL) return false;
	else return true;
}



/**
* @brief Méthode qui permet de retirer de la liste et retourne l'element pointe par l'iterateur
* @param T, l'element pointe par l'iterateur
*/
template <class T>
T Iterateur<T>::remove()
{
	// Declaration des variables de travail
	Cellule<T> *pTop = liste.getTete();
	Cellule<T> *pPrecedent = NULL;
	T val;

	if(this->pCourant != NULL)
	{
		if(pTop == this->pCourant)
		{
			liste.setTete(liste.getTete()->pSuivant);
			return pTop->valeur;
		} else {
			while(pTop != this->pCourant)
			{
				pPrecedent = pTop;
				pTop = pTop->pSuivant;
			}
			pPrecedent->pSuivant = pTop->pSuivant;
			val = pTop->valeur;
			delete [] pTop;
				
		}
		return val;
	} else {
		throw invalid_argument("\x1b[0m\x1b[1m[-] pCourant == NULL\x1b[0m");
	}
}	


/**
* @brief Méthode de la classe Iterateur operator++, qui permet de deplacer l'iterateur vers la droite
*/
template <class T>			
void Iterateur<T>::operator++(void)
{
	this->pCourant = this->pCourant->pSuivant;	
}

template <class T>
bool Iterateur<T>::operator++(int unused)
{
	if(this->pCourant != NULL) {
		operator++();
		return true;
	} else { 
		return false;
	}
}



/**
* @brief Méthode de la classe Iterateur operator--, qui permet de deplacer l'iterateur vers la gauche
* @CTT : 0(n)
*/
template <class T>
void Iterateur<T>::operator--(void)
{


	if(this->pCourant != NULL) 
	{
		if(this->pCourant == liste.getTete())
			this->pCourant = NULL; // On stop 
		else {
			Cellule<T> *ptrTete = liste.getTete();	
			while(ptrTete->pSuivant != this->pCourant)
			{
				ptrTete = ptrTete->pSuivant;
			}
			this->pCourant = ptrTete;
		}
	}

}


template <class T>
bool Iterateur<T>::operator--(int unused)
{
	if(this->pCourant != NULL) {
		operator--();
		return true;
	} else { 
		return false;
	}
}

/**
* @brief (Casting) Méthode qui retourne (par valeur) l'element pointé par l'iterateur
* @param T, l'element pointe par l'iterateur
*/
template <class T>
Iterateur<T>::operator T(void) const
{
	return this->pCourant->valeur;
	
}

/**
* @brief Méthode qui se charge de retourner l'adresse de l'élément (objet T) pointé par l'itérateur
* @return T&, l'adresse de l'element
*/

// &it
template <class T>
T* Iterateur<T>::operator&(void)
{	
	return &(this->pCourant->valeur);
}


template <class T>
T& Iterateur<T>::operator*(void) const
{
	return this->pCourant->valeur;
}



/**
* @brief Méthode qui se charge de faire l'operation = 
* Si la méthode std::is_same(valeur, Couleur)::value retourne true
*			 c'est que la valeur est de type int ou bien Couleur
* @source https://en.cppreference.com/w/cpp/types/is_same
*/
template <class T>
void Iterateur<T>::operator=(T valeur)
{	
	Trace("\x1b[34m\x1b[1m Dans la méthode operator=(T valeur) de la Classe Iterateur \x1b[0m");
	if(std::is_same<T, int>::value or std::is_same<T, Couleur>::value)
		this->pCourant->valeur = valeur;
	else
		throw invalid_argument("\x1b[31m\x1b[1m[-] La valeur == NULL \x1b[0m");
}

// =================== Intanciation =================== 
template class Iterateur<int>;
template class Iterateur<Couleur>;
template class Iterateur<Figure *>;
template class Iterateur<Rectangle>;
template class Iterateur<Ligne>;
template class Iterateur<Pixel>;
