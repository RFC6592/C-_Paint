#include <stdio.h>
#include <stdlib.h>

#include "Iterateur.h"

#include "../Couleur.h"
#include "../Ecran.h"




template <class T>
Iterateur<T>::Iterateur(ListeBase<T> &listeCopie) : liste(listeCopie)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Dans le constructeur de copie de la classe Iterateur\x1b[0m");
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
		Trace("\x1b[34m\x1b[1mDans la méthode reset() de la Classe Iterateur\x1b[0m"); 
		this->pCourant = liste.getTete();
}


/**
* @brief Méthode qui se charge de positionner l'itérateur sur le dernier élément de la liste
*/
template <class T>
void Iterateur<T>::last(void)
{

	Trace("\x1b[34m\x1b[1m Dans la méthode last() de la Classe Iterateur\x1b[0m");

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
	Trace("\x1b[34m\x1b[1m Dans la méthode end() de la Classe Iterateur\x1b[0m");
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
	Trace("\x1b[34m\x1b[1m Dans la méthode remove() de la Classe Iterateur\x1b[0m");
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
	Trace("\x1b[34m\x1b[1m Dans la méthode operator++(void) \x1b[0m");
	this->pCourant = this->pCourant->pSuivant;	
}

template <class T>
bool Iterateur<T>::operator++(int unused)
{
	Trace("\x1b[34m\x1b[1m Dans la méthode operator++(int unused) \x1b[0m");
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

	Trace("\x1b[34m\x1b[1m Dans la méthode de la classe Iterateur operator--(void)\x1b[0m");

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
			Trace("\x1b[35m pCourant->valeur = %d\x1b[0m", pCourant->valeur);
			this->pCourant = ptrTete;
		}
	}

}


template <class T>
bool Iterateur<T>::operator--(int unused)
{
	Trace("\x1b[34m\x1b[1m Dans la méthode operator--(int unused) \x1b[0m");
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
	Trace("\x1b[34m\x1b[1m (Casting) Méthode operator T(void) de la Classe Iterateur\x1b[0m");
	return this->pCourant->valeur;
	
}

/**
* @brief Méthode qui se charge de retourner l'adresse de l'élément (objet T) pointé par l'itérateur
* @return T&, l'adresse de l'element
*/

// &it
template <class T>
Iterateur<T>& Iterateur<T>::operator&(void)
{	
	Trace("\x1b[34m\x1b[1m (Casting) Méthode operator&(void) de la Classe Iterateur \x1b[0m");
	return (*this);
}

template <class T>
T& Iterateur<T>::operator*(void) const
{
	Trace("\x1b[34m\x1b[1m Dans la méthode operator*(void) de la Classe Iterateur \x1b[0m");
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
