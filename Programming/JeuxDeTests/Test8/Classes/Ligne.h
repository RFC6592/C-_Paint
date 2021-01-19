#ifndef LIGNE_H
#define LIGNE_H

#include "Figure.h"

class Ligne : public Figure
{
	friend std::ostream& operator<<(std::ostream& s, const Ligne& ligne);	

	private:
		Point extremite;
		
	public:
		Ligne();
		~Ligne(); // Destructeur
		Ligne(const char pId[5], const Point &p1, const Point &p2, const Couleur *pCouleur); // Constructeur d'initialisation
		Ligne(const Ligne& ligne); // Constructeur de copie	

		Point getExtremite(void) const;
		void	setExtremite(const Point& p);

		virtual void Dessine(void) const;
		virtual void setId(const char pId[5]);

		
		void Save(std::ofstream& fichier) const;
		void Load(std::ifstream& fichier);
};
#endif
