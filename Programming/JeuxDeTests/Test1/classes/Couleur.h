// 24/09 : 
// Les méthodes de type const sont des méthodes de << lecture seule >>. 
// Elles possèdent le mot-clé const à la fin de leur prototype et de la déclaration 

#ifndef COULEUR_H
#define COULEUR_H
class Couleur
{
public:
	
	Couleur();
	Couleur(const int, const int, const int, const char *pNewNom);
	Couleur(const int, const int, const int);
	Couleur(const Couleur& c); // Constructeur de copie
	~Couleur();
	
	void Affiche() const;
	void setNom(const char *);
	const char* getNom() const;
	
	// Setters
	void setRouge(int);
	void setBleu(int);
	void setVert(int);
	
	
	// Getters 
	int getRouge() const;
	int getVert() const;
	int getBleu() const;
private:
	int rouge;
	int vert;
	int bleu;
 	char *pNom; 
};
#endif
