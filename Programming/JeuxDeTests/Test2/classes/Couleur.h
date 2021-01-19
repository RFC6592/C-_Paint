// 24/09 : 
// Les méthodes de constantes sont des méthodes de << lecture seule >>. 
// Elles possèdent le mot-clé const à lafin de leur prototype et de leur déclaration 

#ifndef COULEUR_H
#define COULEUR_H
class Couleur
{

private:
	int rouge;
	int vert;
	int bleu;
 	char *pNom;

	static int compteur;
	

public:
	
	Couleur();
	Couleur(int, int, int, const char *pNewNom);
	Couleur(int, int, int);
	Couleur(const Couleur& c); // Constructeur de copie
	~Couleur();
	
	void Affiche() const;
	void setNom(const char *);
	char* getNom() const;
	
	// Setters
	void setRouge(int);
	void setBleu(int);
	void setVert(int);
	
	
	// Getters 
	int getRouge() const;
	int getVert() const;
	int getBleu() const;

	static int getCompteur();
	

	// Slide 2 ~ Classes et les objets | 3 objets de type Couleur
	static const Couleur ROUGE; 
	static const Couleur VERT;
	static const Couleur BLEU;

};
#endif
