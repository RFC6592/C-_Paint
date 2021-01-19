#ifndef DESSIN_H
#define DESSIN_H

#include "Couleur.h"
#include "./Template/Iterateur.h"
#include "./Template/Liste.h"
#include "./Template/Pile.h"

// ---
#include "Figure.h"
#include "Rectangle.h"
#include "Ligne.h"
#include "Pixel.h"

class Dessin
{
	private:
		Couleur fond;
		Liste<Couleur> palette;
		Pile<Figure *> figures;

	public:
		Dessin();
		Dessin(const Couleur& f);
		~Dessin();

		void ajouteCouleur(const Couleur& c);
		void ajouteFigure(Figure *pf, const char *nomCouleur);
		void Dessine();
		void undo();
		Couleur getFond();
		void setFond(const Couleur& c);
		void affichePalette();
		void afficheFigures();
		Couleur* recupererCouleur(const char *nomCouleur);

	private:
		bool isExist(const char *nomCouleur);
		bool isNameExist(const char *nomId);
};

#endif
