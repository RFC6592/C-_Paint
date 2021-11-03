#ifndef LISTE_H
#define LISTE_H
#include "ListeBase.h"

template <class T>
class Liste : public ListeBase<T>
{
	public:
		T* insere(const T &valeur);		
		
};

#endif
