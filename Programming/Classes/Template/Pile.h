#ifndef PILE_H
#define PILE_H

#include "ListeBase.h"

// 12-11-20
// Classe template Pile qui hérite de la classe ListeBase

template <class T>
class Pile : public ListeBase<T>
{

	public:
		T* insere(const T &);
		void push(const T &);
		T top(void) const;
		T pop(void);

	 	
};

#endif

