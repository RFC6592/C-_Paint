/** 
* @author EZZAYRI Sami 2226
* @date 9/10/20
*/
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

#include "Ecran.h"
#include "Point.h"

/**
* @brief Initialisation du compteur 
*/
int Point::compteur = 0;


/** 
* @brief Methode static qui se charge de retourner le nb d'objets de type Point 
* @return int compteur
*/
int Point::getCompteur(){ return compteur; }



/**
* @brief Methode qui permet de modifier l'objet courant par un autre Point
* @param const Couleur& couleur
* @return retourne l'objet courant
*/
Point& Point::operator=(const Point& p)
{
	Trace("\x1b[35m\x1b[1m Dans la methode operator=() de la classe Point\x1b[0m");
	
	setX(p.getX());
	setY(p.getY());
	
	return (*this);
}


/**
* @brief Constructeur par defaut
* @param void
* @return void 
*/
Point::Point():x(0),y(0)
{
	Trace("\x1b[37m\x1b[40m Constructeur par defaut de la classe Point\x1b[0m");
	compteur++;
}



/** 
* @brief Constructeur de copie de la classe Point
*/
Point::Point(const Point& p)
{
	Trace("\x1b[36m\x1b[40m\x1b[7m Constructeur de copie de la classe Point\x1b[0m");
	
	x = p.getX();
	y = p.getY();

	compteur++;
}



/**
* @brief Destructeur de la classe Point
*/
Point::~Point()
{
	Trace("\x1b[37m\x1b[41m Destructeur de la classe Point\x1b[0m");
	compteur--;
}



/** 
* @brief Constructeur d'initialisation avec 2 parametres 
* @param int coordX
* @param int coordY
*/

Point::Point(int coordX, int coordY):x(coordX),y(coordY)
{
	Trace("\x1b[37m\x1b[40m Constructeur d'initialisation de la classe Point\x1b[0m");
	compteur++;
}



/**
* @brief Methode qui se charge d'afficher les informations sur un Point 
*/
void Point::Affiche() const
{
	Trace("\x1b[34m Affiche() de la classe Point\x1b[0m");
	std::cout << "\x1b[33m> x : " << getX() << "\x1b[0m" << std::endl;
	std::cout << "\x1b[33m> y : " << getY() << "\x1b[0m" << std::endl;
}



/** 
* @brief Methode qui permet de donner un nouveau x
* @param int coordX
*/
void Point::setX(int coordX)
{
	Trace("\x1b[34m setX() de la classe Point\x1b[0m");
	this->x = coordX;
}



/** 
* @brief Methode qui permet de donner un nouveau y
* @param int coordY
*/
void Point::setY(int coordY)
{
	Trace("\x1b[34m setY() de la classe Point\x1b[0m");
	this->y = coordY;
}


std::ostream& operator<<(std::ostream& s, const Point &point)
{
	s << point.getX() << ", " << point.getY();
	return s;
}

/** 
* @brief Getters - Accesseurs 
*/
int Point::getX() const { return this->x; }
int Point::getY() const { return this->y; }

