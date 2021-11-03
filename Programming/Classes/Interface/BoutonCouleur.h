#ifndef BOUTON_COULEUR_H
#define BOUTON_COULEUR_H
#include "Bouton.h"
#include "../Couleur.h"
#include "../Point.h"
#include <iostream>
#include "../Template/Iterateur.h"
#include "../Template/Liste.h"
#include "../Template/Pile.h"

class BoutonCouleur : public Bouton
{
	friend std::ostream& operator<<(std::ostream& s, const BoutonCouleur& c);
	private:
		Couleur *pCouleur;
		 
	public:
		BoutonCouleur();
		BoutonCouleur(const Point &p1, const Point &p2);
		BoutonCouleur(const char *pNewNom, const Point &p1, const Point &p2);
		BoutonCouleur(const BoutonCouleur &b);
		~BoutonCouleur();

		void setCouleur(Couleur *pCouleur);
		void setSelected(bool newSelected);			
		Couleur* getCouleur() const;
};


#endif
