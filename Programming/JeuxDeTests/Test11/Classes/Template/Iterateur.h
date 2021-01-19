#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "ListeBase.h"
#include "Cellule.h"

// Source pour operator T() :
// http://stackoverflow.com/questions/44247797/c-operator-parenthesis-operator-type-vs-type-operator

template <class T>
class Iterateur
{
	private:
		ListeBase<T> &liste;
		Cellule<T> *pCourant;

	public:
	
		~Iterateur();
		Iterateur(ListeBase<T> &listeCopie);
		
		// ====================
		void reset(void);
		void last(void);
		bool end(void) const;
		T remove();	
	
		// ====================
		void operator++(void); // Deplacement vers la droite
		bool operator++(int unused);

		void operator--(void); // Deplacement vers la gauche
		bool operator--(int unused);
		
		
		operator T() const; 
		T* operator&(void);
		T& operator*(void) const;
		void operator=(T valeur);

		// T operator T() const; => Call operator 
		// alors que operator T() const; => Conversion operator
		
};
#endif

