#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "InvalidColorException.h"
#include "../Ecran.h"

InvalidColorException::InvalidColorException() :  BaseException()
{
	Trace("\x1b[37m\x1b[40m Dans le contructeur de la classe InvalidColorException\x1b[0m");
	this->setValeur(0);
}

InvalidColorException::InvalidColorException(int valeur, const char * pMsg) : BaseException(pMsg)
{
	Trace("\x1b[37m\x1b[40m Dans le constructeur de la classe InvalidColorException 2\x1b[0m");
	this->setValeur(valeur);
}


/**
* @brief Constructeur de copie 
*/
InvalidColorException::InvalidColorException(const InvalidColorException& c) : BaseException(c)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Dans le constructeur de copie\x1b[0m");
	setValeur(c.getValeur());
}


/**
* @brief Destructeur de copie 
*/
InvalidColorException::~InvalidColorException(void)
{
	Trace("\x1b[37m\x1b[41m Destructeur de la classe InvalidColorException\x1b[0m");
}

void InvalidColorException::setValeur(int valeur)
{
	Trace("\x1b[34m Dans le setValeur() de la Classe InvalidColorException\x1b[0m");
	this->valeur = valeur;
}

int InvalidColorException::getValeur(void) const
{
	Trace("\x1b[34m Dans le getValeur() de la Classe InvalidColorException\x1b[0m");
	return this->valeur;
}


void InvalidColorException::Affiche(void) const
{
	std::cout << this->pMsg << " (" << this->valeur << ")" << std::endl;
} 
