#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "InvalidColorException.h"
#include "../Ecran.h"

InvalidColorException::InvalidColorException() :  BaseException()
{
	this->setValeur(0);
}

InvalidColorException::InvalidColorException(int valeur, const char * pMsg) : BaseException(pMsg)
{
	this->setValeur(valeur);
}


/**
* @brief Constructeur de copie 
*/
InvalidColorException::InvalidColorException(const InvalidColorException& c) : BaseException(c)
{
	setValeur(c.getValeur());
}


/**
* @brief Destructeur de copie 
*/
InvalidColorException::~InvalidColorException(void)
{
}

void InvalidColorException::setValeur(int valeur)
{
	this->valeur = valeur;
}

int InvalidColorException::getValeur(void) const
{
	return this->valeur;
}


void InvalidColorException::Affiche(void) const
{
	std::cout << this->pMsg << " (" << this->valeur << ")" << std::endl;
} 
