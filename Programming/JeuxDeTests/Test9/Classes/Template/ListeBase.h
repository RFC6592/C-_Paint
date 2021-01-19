#ifndef LISTE_BASE_H
#define LISTE_BASE_H

#include "Cellule.h"
//#include "Iterateur.h"

// Le mot clé ""template"" prévient le compilateur que la prochaine chose dont on va lui parler
// sera générique

template <class T> class Iterateur;

template <class T> 
class ListeBase 
{
	protected:
		Cellule<T> *pTete;
		
	public:
		// Méthode virtuelle pure donc ListeBase devient une classe abstraite pure, on peut plus instancer ListeBase
		virtual T* insere(const T &valeur) = 0;		
	
		ListeBase(void);
		ListeBase(const ListeBase<T> &listeCopie);
		~ListeBase(void);

		bool estVide(void) const;
		int getNombreElements(void) const;
		void Affiche(void) const;

		ListeBase<T>& operator=(const ListeBase<T> &liste); 		
		Cellule<T>* getTete(void) const;
		void setTete(Cellule<T> *pNewCellule);
		friend class Iterateur<T>;
	
};


#endif
