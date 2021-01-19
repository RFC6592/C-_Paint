// 24/09 : 
// Les méthodes de constantes sont des méthodes de << lecture seule >>. 
// Elles possèdent le mot-clé const à lafin de leur prototype et de leur déclaration 
#ifndef COULEUR_H
#define COULEUR_H

#include "./Exception/BaseException.h"
#include "./Exception/InvalidColorException.h"

class Couleur
{


friend Couleur operator+(int valCouleur, const Couleur& couleur);

friend std::ostream& operator<<(std::ostream& s, const Couleur& c);
friend std::istream& operator>>(std::istream& s, Couleur& c);


private:
	int rouge;
	int vert;
	int bleu;
 	char *pNom;

	static int compteur;

public:
	
	Couleur(); // Constructeur par defaut
	Couleur(int, int, int, const char *pNewNom);
	Couleur(int, int, int);
	Couleur(const Couleur& c); // Constructeur de copie
	~Couleur(); // Destructeur
	
	void Affiche() const;
	void setNom(const char *);
	const char* getNom() const;
	

	// Setters - Mutateurs
	void setRouge(int) throw(InvalidColorException);
	void setBleu(int) throw(InvalidColorException);
	void setVert(int) throw(InvalidColorException);
	

	
	// Getters - Accesseurs
	int getRouge() const;
	int getVert() const;
	int getBleu() const;

	static int getCompteur();
	
	// Slide 2 ~ Classes et les objets | 3 objets de type Couleur
	static const Couleur ROUGE; 
	static const Couleur VERT;
	static const Couleur BLEU;
	static const Couleur ORANGE;

	// Les operateurs 
	Couleur operator+(int valCouleur) const;
	Couleur operator-(int valCouleur) const;
	

	Couleur& operator=(const Couleur& c);
	Couleur operator+(const Couleur& couleur) const;


	int& operator[](const char* couleur);

	Couleur operator++(int);
	Couleur operator++();
	 
	Couleur operator--(int);
	Couleur operator--();	



	void Save(std::ofstream& fichier) const;
	void Load(std::ifstream& fichier);
	
};
#endif
