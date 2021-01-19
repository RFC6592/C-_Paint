#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Pile.h"
#include "../Ecran.h"
#include "../Couleur.h"

#include "../Rectangle.h"
#include "../Ligne.h"
#include "../Pixel.h"

// --
#include "../Figure.h"

template <class T>
T* Pile<T>::insere(const T &valeur)
{
	Trace("\x1b[33mDans la méthode insere de la Classe Pile\x1b[0m");

	Cellule<T> *pNewCellule = new Cellule<T>;
	pNewCellule->valeur = valeur;

	pNewCellule->pSuivant = this->getTete();
	this->pTete = pNewCellule;

	return &(pNewCellule->valeur);
}


/**
* @brief Méthode qui empile un élément sur la pile
* @param const T &valeur
* @return void 
*/
template <class T>
void Pile<T>::push(const T &valeur)
{
	Trace("\x1b[33mDans la méthode push() de la Classe Pile\x1b[0m");
	insere(valeur);
}


/**
* @brief Méthode qui se charge de retourner l'élément situé au sommet de la pile mais sans altérer la pile
* @param void
* @return T, l'element au sommet de la pile 
*/
template <class T>
T Pile<T>::top(void) const
{
	Trace("\x1b[33mDans la méthode top() de la Classe Pile\x1b[0m");
	return this->getTete()->valeur;
}


/**
* @brief Méthode qui se charge de retourner l'élément situé au sommet de la pile et qui le supprime de la pile
* @param void
* @return T, l'element au sommet de la pile 
*/
template <class T>
T Pile<T>::pop(void)
{
	Trace("\x1b[33mDans la méthode pop() de la classe Pile\x1b[0m");
	
	Cellule<T> *pDel = this->getTete();
	T tmp = this->getTete()->valeur;
	this->pTete = this->pTete->pSuivant;
	delete pDel;
	return tmp;
}



// Instanciation 
template class Pile<int>;
template class Pile<Couleur>;
template class Pile<Rectangle>;
template class Pile<Ligne>;
template class Pile<Pixel>;
template class Pile<Figure *>;