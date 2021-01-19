#ifndef FIGURE_H  
#define FIGURE_H
#include "Couleur.h"
#include "Point.h"
class Figure 
{

private:
	char pId[5];
	Point position;
	const Couleur* pCouleur;
	
	static int compteur; 


public:
	Figure();
	~Figure();
	
	Figure(const char pId[5], const Point &position, const Couleur *pCouleur);
	Figure(const char pId[5], const Point &position);
	Figure(const Figure &f);	
	Figure& operator=(const Figure& f);
	

	// Setters - Mutateurs
	void setId(const char pId[5]);
	void setPosition(const Point &position);
	void setCouleur(const Couleur *pCouleur);
	

 	// Getters - Accesseurs
 	const char* getId() const;
	Point getPosition() const;
	const Couleur* getCouleur() const;

	
	void Affiche() const;	
	static int getCompteur();	

};

#endif
