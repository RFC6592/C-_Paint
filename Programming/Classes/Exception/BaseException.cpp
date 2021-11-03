#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include "../Ecran.h"
#include "BaseException.h"

BaseException::BaseException(void)
{
	this->pMsg = NULL;
}

BaseException::BaseException(const char * pMsg)
{
	setErreur(pMsg);
}

BaseException::~BaseException()
{
	delete this->pMsg;
}

BaseException::BaseException(const BaseException &b)
{
	this->setErreur(b.getErreur());
}


void BaseException::setErreur(const char *pMsg)
{

	if(this->pMsg != NULL) delete this->pMsg;
	this->pMsg = new char[strlen(pMsg) + 1];
	strcpy(this->pMsg, pMsg); 
}

const char * BaseException::getErreur() const
{
	return this->pMsg;
}
