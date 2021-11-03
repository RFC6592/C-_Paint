#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>
using namespace std;


/** 30-10-20 
* Nous avons une structure Cellule qui est template
* 1> Cette Cellule est composée d'une valeur de type T
* 2> Cette Cellule est composée également d'un pointeur pSuivant, pointant sur une Cellule de type T
*/

template <class T> 
struct Cellule
{
	T valeur;
	Cellule<T> *pSuivant; // Un pointeur qui pointe sur le Cellule de type T
};

#endif
