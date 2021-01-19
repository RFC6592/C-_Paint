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


#include <fstream>
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
	compteur++;
}



/** 
* @brief Constructeur de copie de la classe Point
*/
Point::Point(const Point& p)
{
	
	this->x = p.getX();
	this->y = p.getY();
	
	compteur++;
}



/**
* @brief Destructeur de la classe Point
*/
Point::~Point()
{
	compteur--;
}



/** 
* @brief Constructeur d'initialisation avec 2 parametres 
* @param int coordX
* @param int coordY
*/

Point::Point(int coordX, int coordY):x(coordX),y(coordY)
{
	compteur++;
}



/**
* @brief Methode qui se charge d'afficher les informations sur un Point 
*/
void Point::Affiche() const
{
	std::cout << "\x1b[33m> x : " << getX() << "\x1b[0m" << std::endl;
	std::cout << "\x1b[33m> y : " << getY() << "\x1b[0m" << std::endl;
}



/** 
* @brief Methode qui permet de donner un nouveau x
* @param int coordX
*/
void Point::setX(int coordX)
{
	this->x = coordX;
}



/** 
* @brief Methode qui permet de donner un nouveau y
* @param int coordY
*/
void Point::setY(int coordY)
{
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



void Point::Save(std::ofstream& fichier) const
{

	
	int tmp = this->getX();
	fichier.write((char *)&tmp, sizeof(int));
	tmp = this->getY();
	fichier.write((char *)&tmp, sizeof(int));
		


}

void Point::Load(std::ifstream& fichier)
{

	int tmp;
	fichier.read((char *)&tmp, sizeof(int));
	this->setX(tmp);
	fichier.read((char *)&tmp, sizeof(int));
	this->setY(tmp);

}


