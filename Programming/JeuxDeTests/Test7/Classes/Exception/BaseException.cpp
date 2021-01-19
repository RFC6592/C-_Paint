#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include "../Ecran.h"
#include "BaseException.h"

BaseException::BaseException(void)
{
	this->setErreur(" ");
}

BaseException::BaseException(const char * pMsg)
{
	Trace("\x1b[37m\x1b[40m (Constructeur) Classe BaseException\x1b[0m");
	if(pMsg != NULL) 
		strncpy(this->pMsg, pMsg, strlen(pMsg)+1);	
	
}

BaseException::~BaseException()
{
	Trace("\x1b[37m\x1b[41m (Destructeur) Classe BaseException\x1b[0m");
}

BaseException::BaseException(const BaseException &b)
{
	Trace("\x1b[34m (Constructeur de copie) Classe BaseException\x1b[0m");
	this->setErreur(b.getErreur());
}


void BaseException::setErreur(const char *pMsg)
{
	Trace("\x1b[34m (setErreur) Classe BaseException\x1b[0m");

	if(pMsg != NULL)
		strncpy(this->pMsg, pMsg, strlen(pMsg)+1);
	
}

const char * BaseException::getErreur() const
{
	Trace("\x1b[34m (getErreur) Classe BaseException\x1b[0m");
	return this->pMsg;
}
