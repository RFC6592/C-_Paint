#ifndef INVALID_COLOR_EXCEPTION_H
#define INVALID_COLOR_EXCEPTION_H
#include "BaseException.h"

class InvalidColorException : public BaseException
{
	private:
		int valeur;
		
	public:
		InvalidColorException(void);
		InvalidColorException(int valeur);
		InvalidColorException(int valeur, const char pMsg[80]);
		InvalidColorException(const InvalidColorException& c);
		~InvalidColorException();

		void setValeur(int valeur);
		int getValeur(void) const;
		void Affiche(void) const; 
};
#endif
