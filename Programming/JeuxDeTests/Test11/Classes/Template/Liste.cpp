#include <stdio.h>
#include <stdlib.h>
#include "../Ecran.h"
#include "Liste.h"
#include "../Couleur.h"
#include "../Interface/Bouton.h"
#include "../Interface/BoutonCouleur.h"
#include "../Rectangle.h"
#include "../Ligne.h"
#include "../Pixel.h"

template <class T>
T* Liste<T>::insere(const T& valeur)
{
	Trace("Dans la methode insere de la classe template Liste");
	
	Cellule<T> *pNewCellule = new Cellule<T>;
	Cellule<T> *pTeteTmp = this->getTete();

	pNewCellule->valeur = valeur;
	pNewCellule->pSuivant = NULL;
	
	if(this->estVide() != true)
	{
		while(pTeteTmp->pSuivant != NULL)
		{
			pTeteTmp = pTeteTmp->pSuivant;
		}
		pTeteTmp->pSuivant = pNewCellule;
	}
	else {
		this->setTete(pNewCellule);
	}

	return &pNewCellule->valeur;
	
}


template class Liste<int>;
template class Liste<Couleur>;
template class Liste<Rectangle>;
template class Liste<Ligne>;
template class Liste<Pixel>;

template class Liste<Bouton>;
template class Liste<BoutonCouleur>;

