#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Ecran.h"
#include "Dessin.h"
#include "./Exception/BaseException.h"
#include "./WindowSDL/WindowSDL.h"
using namespace std;

#include <fstream>

/**
* @brief Initialisation des compteurs 
*/
int Dessin::nbCouleurs = 0;
int Dessin::nbFigures = 0;

int Dessin::getNbCouleurs() { return nbCouleurs; }
int Dessin::getNbFigures()  { return nbFigures; }


Dessin::Dessin()
{
	setFond(Couleur(0, 0, 0, "Noir"));
}

Dessin::Dessin(const Couleur& f)
{
	this->fond = f;
}

Dessin::~Dessin()
{
	Iterateur<Figure *> it(this->figures);
	for(it.last(); !it.end(); it--)
	{
		delete ((Figure *)it);
		nbFigures--;
	}	
	
}

Couleur* Dessin::ajouteCouleur(const Couleur& c) throw (BaseException)
{
	
	Iterateur<Couleur> it(this->palette);

	it.reset();
	while (!it.end() && strcmp(c.getNom(), ((Couleur)it).getNom())) { it++; } // Tant que c'est pas les mêmes 

	if(!it.end()) throw BaseException("Err : Couleur deja utilisé");

	this->palette.insere(c);
	nbCouleurs++;

	if(c.getNom() != NULL) return recupererCouleur(c.getNom());
//	return NULL;
}

Couleur* Dessin::recupererCouleur(const char *nomCouleur)
{
	Iterateur<Couleur> it(this->palette);
	for(it.reset(); !it.end(); it++)
	{ 
		if(strcmp( ((Couleur)it).getNom(), nomCouleur) == 0) {
			return &it; 
		} 
	}
	return NULL;
}

void Dessin::ajouteFigure(Figure *pf, const char *nomCouleur) throw(BaseException)
{

	if(isExist(nomCouleur))
	{
		if(!isNameExist(pf->getId())) { 
			pf->setCouleur(recupererCouleur(nomCouleur)); 
			this->figures.push(pf);
			nbFigures++;
		} else { throw BaseException("Err : Nous avons déjà une Figure sous cet ID"); }
	} else {
		throw BaseException("Err : Nous n'avons pas trouvé la couleur");
	}
		
}



bool Dessin::isExist(const char *nomCouleur)
{
	Iterateur<Couleur> it(this->palette);
	for(it.reset(); !it.end(); it++)
	{
		if(strcmp( ((Couleur)it).getNom(), nomCouleur) == 0)
			return true;
	}

	return true;	
}


bool Dessin::isNameExist(const char *nomId)
{
	Iterateur<Figure *> it(this->figures);
	for(it.reset(); !it.end(); it++)
	{
		if(strcmp( ((Figure *)it)->getId(), nomId) == 0)
			return true;
	}

	return false;	
}


//================================================

void Dessin::Dessine()
{
	WindowSDL::fillRectangle(getFond().getRouge(), getFond().getVert(), getFond().getBleu(), 0, 40, 840, 600 - 40);
	if(!this->figures.estVide()) {
		Iterateur<Figure *> it(this->figures);
		for(it.last(); !it.end(); it--)
			((Figure *)it)->Dessine();
	} 
}

void Dessin::undo()
{
	if(!this->figures.estVide()) {
		this->figures.pop();
		nbFigures--;
	}
}

void Dessin::affichePalette()
{
	Iterateur<Couleur> it(this->palette);
	for (it.reset() ; !it.end() ; it++) {
   	((Couleur)it).Affiche();
	}

}


void Dessin::afficheFigures()
{
	Iterateur<Figure *> it(this->figures);
	for(it.reset(); !it.end(); it++) {
		((Figure *)it)->Affiche();
	}
}


Couleur Dessin::getFond()
{
	return this->fond;
}

void Dessin::setFond(const Couleur& c)
{
	this->fond = c;
}

Liste<Couleur>& Dessin::getPalette()
{
	return this->palette;
}


void Dessin::Save(const char* nomFichier) {
	ofstream fichier(nomFichier, ios::out);

	if (!fichier.is_open()) {
		cout << "\x1b[31m[-] Erreur d'ouverture du fichier\x1b[0m" << endl;
		exit(1);
	}

	Iterateur<Couleur> it(this->palette);
	Iterateur<Figure*> it2(this->figures);
	int nbCouleurs;
	int nbFigures;
	
	// --- Enregistrement du fond
	fond.Save(fichier);
	
	// --- Enregistrement des couleurs
	nbCouleurs = this->palette.getNombreElements();
	fichier.write((char*)&nbCouleurs, sizeof(int));


	it.reset();
	for (int i=0; i < nbCouleurs; it++, i++) {
		((Couleur)it).Save(fichier);
	}
	
	//-- Enregistrement des figures
	nbFigures = figures.getNombreElements();
	fichier.write((char*)&nbFigures, sizeof(int));
	it2.last();
	for (int i=0; i< nbFigures; it2--, i++) {
	
		if (dynamic_cast<Pixel*>((Figure*)it2)) 	  {	fichier.write("P", sizeof(char)); }
		if (dynamic_cast<Ligne*>((Figure*)it2)) 	  {	fichier.write("L", sizeof(char)); }
		if (dynamic_cast<Rectangle*>((Figure*)it2)) { 	fichier.write("R", sizeof(char)); }
		
		((Figure*)it2)->Save(fichier);
		short taille = strlen(((Figure*)it2)->getCouleur()->getNom());
		fichier.write((char*)&taille, sizeof(short));
		fichier.write((char*)((Figure*)it2)->getCouleur()->getNom(), taille);
	}

	fichier.close(); // Fermeture

}
void Dessin::Load(const char* nomFichier) {

	// ---
	ifstream fichier(nomFichier, ios::in);
	if (!fichier.is_open()) {
		cout << "\x1b[31m[-]Erreur de lecture\x1b[0m" << endl;
		exit(1);
	}

	// -- Déclaration des variables de travail --
	Iterateur<Couleur> it(palette);
	int nbCouleurs;
	int nbFigures;
	char lettreType;
	Couleur tmp;
	Figure* pFigureType;

	// -- Lecture fond

	fond.Load(fichier);
	// -- Enregistrement palette
	fichier.read((char*)&nbCouleurs, sizeof(int));

	for (int i=0 ; i < nbCouleurs; i++) {
		tmp.Load(fichier);
		ajouteCouleur(tmp);
	}

	// -- Lecture des figures
	fichier.read((char*)&nbFigures, sizeof(int));
	for (int i=0; i < nbFigures; i++) {

		fichier.read((char*)&lettreType, sizeof(char));
		if (lettreType == 'P') pFigureType = new Pixel;
		if (lettreType == 'L') pFigureType = new Ligne;
		if (lettreType == 'R') pFigureType = new Rectangle;
		pFigureType->Load(fichier);
		
		short taille;
		fichier.read((char*)&taille, sizeof(short));
		char* pCouleur = new char[taille + 1];
		fichier.read((char*)pCouleur, taille);
		ajouteFigure(pFigureType, pCouleur);

		delete pCouleur; // Destruction
	}

	fichier.close(); // -- Fermeture 
}





























//void Dessin::Save(const char *nomFichier)
//{
//	std::ofstream fichier(nomFichier, ios::out);

//	// --- Déclaration des variables de travail ---
//	Rectangle *pRectangle;
//	Ligne *pLigne;
//	Pixel *pPixel;
//	int tailleNom;

//	// --- Traitement ---
//	if(!fichier.rdbuf()->is_open())
//	{
//		cout << "\x1b[31m\x1b[1m[-]Err : Le fichier n'est pas ouvert !\x1b[0m" << endl;
//		exit(1);
//	}
//	else
//	{
//		// ======== Encodage du fond ========
//		this->fond.Save(fichier);	

//		// ======== Encodage du nombre de Couleurs  ========
//		fichier.write((char *)&nbCouleurs, sizeof(int)); 

//		Iterateur<Couleur> itC(this->palette); 
//		for (itC.reset() ; !itC.end() ; itC++) {
//			((Couleur)itC).Save(fichier);
//		}

//		// ======== Encodage du nombre de Figures  ========
//		fichier.write((char *)&nbFigures, sizeof(int)); 
//		
//		
//		Iterateur<Figure *> itF(this->figures);
//		for(itF.last(); !itF.end(); itF--)
//		{
//			if( (pRectangle = dynamic_cast<Rectangle *>( ((Figure *)itF) )))
//				fichier.write("R", sizeof(char));

//			if( (pLigne = dynamic_cast<Ligne *>( ((Figure *)itF) )))
//				fichier.write("L", sizeof(char));

//			if( (pPixel = dynamic_cast<Pixel *>( ((Figure *)itF) )))
//				fichier.write("P", sizeof(char));


//			// ======== Enregistrer d'abord la taille de la couleur && Enregistrer le nom de la couleur ==========
//			tailleNom = strlen(((Figure *)itF)->getCouleur()->getNom());
//			fichier.write((char*)&tailleNom, sizeof(int));
//			fichier.write((char *)((Figure *)itF)->getCouleur()->getNom(), tailleNom);

//			// ======== Save de la figure ========
//			((Figure *)itF)->Save(fichier);


//		}

//	 	fichier.close(); // Fermeture du fichier
//	}



//}

//void Dessin::Load(const char *nomFichier)
//{
//	std::ifstream fichier(nomFichier, ios::in);

//	int nbC = 0;
//	int nbF = 0;
//	Couleur c1;


//	char pLettreTmp;
//	int tailleNom;
//	Figure* figure;

//	// ==============================
//	// ========= Traitement =========
//	// ==============================
//	if(!fichier.rdbuf()->is_open())
//	{
//		cout << "\x1b[31m\x1b[1m[-]Err : Le fichier n'est pas ouvert !\x1b[0m" << endl;
//	}
//	else
//	{
//		// ========== Lecture du fond ==========
//		this->fond.Load(fichier);

//		// ========== Lecture du nombre de Couleurs ==========
//		fichier.read((char *)&nbC, sizeof(int));

//		for(int i = 0; i < nbC; i++) // (2) remplir la palette
//		{
//			c1.Load(fichier);
//			this->palette.insere(c1);
//		}

//		// ========== Lecture du nombre de Figures ==========
//		fichier.read((char *)&nbF, sizeof(int));

//		// ===================== Lecture de la taille du caractère =====================

//		for(int i = 0; i < nbF; i++) // (2) remplir la pile de figures
//		{
//			fichier.read((char*)&pLettreTmp, sizeof(char));

//			if(pLettreTmp == 'R') { figure = new Rectangle; }
//			if(pLettreTmp == 'L') { figure = new Ligne;     }
//			if(pLettreTmp == 'P') { figure = new Pixel;     }

//			fichier.read((char*)&tailleNom, sizeof(int)); // Taille Nom Couleur
//			char *pNomCouleur = new char[tailleNom + 1];
//			fichier.read((char*)pNomCouleur, tailleNom); // Nom de la Couleur			 

//			// ======== Load de la figure ========
//			figure->Load(fichier);

//			ajouteFigure(figure, pNomCouleur);

//			
//			delete pNomCouleur; // Destruction suite à l'allocation
//		}



//		fichier.close(); // Fermeture du fichier
//	}
//}

