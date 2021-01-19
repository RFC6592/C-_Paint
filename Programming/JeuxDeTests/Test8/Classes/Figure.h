#ifndef FIGURE_H  
#define FIGURE_H
#include "Couleur.h"
#include "Point.h"
class Figure 
{
	friend std::ostream& operator<<(std::ostream& s, const Figure &f);

	protected:
		char pId[5];
		Point position;
		const Couleur* pCouleur;
	
		static int compteur; 

	public:

//		 Méthode virtuelle pure d'ou le = 0 / Classe abstraite
		virtual void Dessine(void) const = 0;


		Figure();
		virtual ~Figure();
		
		Figure(const Point &p, const Couleur *pCouleur);
		Figure(const Point &p);	
	
		Figure(const char pId[5], const Point &position, const Couleur *pCouleur);
		Figure(const char pId[5], const Point &position);
		Figure(const Figure &f);	
		Figure& operator=(const Figure& f);
	

		// Setters - Mutateurs
		virtual void setId(const char pId[5]);
		void setPosition(const Point &position);
		void setCouleur(const Couleur *pCouleur);
	

	 	// Getters - Accesseurs
	 	const char* getId() const;
		Point getPosition() const;
		const Couleur* getCouleur() const;

	
		void Affiche() const;	
		static int getCompteur();	
		
		void Save(std::ofstream& fichier) const;
		void Load(std::ifstream& fichier);
};

#endif