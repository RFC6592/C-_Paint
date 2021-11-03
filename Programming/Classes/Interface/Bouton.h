#ifndef BOUTON_H
#define BOUTON_H
#include "../Point.h"
#include <iostream>

#include "../Template/Iterateur.h"
#include "../Template/Liste.h"
#include "../Template/Pile.h"

class Bouton
{
	friend std::ostream& operator<<(std::ostream& s, const Bouton& c);
	protected:
		Point p1;
		Point p2;
		char *pNom;		
		bool selected;

	public:
		Bouton();
		Bouton(const Point &p1, const Point &p2);
		Bouton(const char *pNom, const Point &p1, const Point &p2);
		Bouton(const Bouton &b);
		~Bouton();

		bool clic(int x, int y);

		// --- Setters | Getters
		virtual void setSelected(bool s);
		void setP1(const Point &newp1);
		void setP2(const Point &newp2);
		void setNom(const char *newNom);

		bool getSelected() const;
		Point getP1() const;
		Point getP2() const;
		const char* getNom() const;

		
};


#endif
