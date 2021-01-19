#ifndef TOOLBAR_H
#define TOOLBAR_H
#include "../Couleur.h"
#include "../Template/Iterateur.h"
#include "../Template/Liste.h"
#include "../Template/Pile.h"


#include "../Point.h"
#include "Bouton.h"
#include "BoutonCouleur.h"

class ToolBar
{

	private:
		Liste<Bouton> 				boutonsFigures;
		Liste<BoutonCouleur>		boutonsCouleur;
		Bouton 						boutonUndo;
		Bouton 						boutonMenu;

	public:
		ToolBar();
		ToolBar(const ToolBar& f);
		~ToolBar();		
		void ajouteBoutonCouleur(const BoutonCouleur &b);
		void ajouteBoutonFigure(const Bouton &b);
		void setBoutonUndo(const Bouton &b);
		void setBoutonMenu(const Bouton &b);
	
		void ajouteCouleur(Couleur* c);
		const char* clic(int x, int y);
		const Couleur* getCouleurSelectionnee();
		const char* getNomCouleur(const char* nomBoutonCouleur);
		const Couleur* getCouleur(const char* nomBoutonCouleur);
		const char* getFigureSelectionnee();
	private:
		void undoSelectionFigure();
		void undoSelectionCouleur();
};


#endif
