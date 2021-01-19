#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Ecran.h"
#include "Dessin.h"
#include "./Exception/BaseException.h"
#include "./WindowSDL/WindowSDL.h"
#include <regex>
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
	this->fond = Couleur::VERT;
}

Dessin::Dessin(const Couleur& f)
{
	this->fond = f;
}

Dessin::~Dessin()
{
	Trace("\x1b[31m\x1b[1mDestructeur de la classe Dessin %d %d\x1b[0m", nbCouleurs, nbFigures);
	Iterateur<Figure *> it(this->figures);
	for(it.last(); !it.end(); it--)
	{
		delete ((Figure *)it);
		nbFigures--;
	}	
	
}

Couleur* Dessin::ajouteCouleur(const Couleur& c)
{
	this->palette.insere(c);
	return recupererCouleur(c.getNom());
	nbCouleurs++;
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

void Dessin::ajouteFigure(Figure *pf, const char *nomCouleur) 
{
	Trace("Nous sommes dans la méthode ajouteFigure de la Classe Dessin - Couleur : %s - ID : %s", nomCouleur, pf->getId());

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
	WindowSDL::fillRectangle(0, 0, 0, 0, 40, 840, 600 - 40);
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
	Trace("\x1b[31m\x1b[1m************** Nb de couleurs = %d **************\x1b[0m", getNbCouleurs());
	Iterateur<Couleur> it(this->palette);
	for (it.reset() ; !it.end() ; it++) {
   	((Couleur)it).Affiche();
	}

}


void Dessin::afficheFigures()
{
	Trace("\x1b[31m\x1b[1m************** Nb de figures = %d **************\x1b[0m", getNbFigures());
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


void Dessin::Save(const char *nomFichier)
{
	std::ofstream fichier(nomFichier, ios::out);

	// --- Déclaration des variables de travail ---
	Rectangle *pRectangle;
	Ligne *pLigne;
	Pixel *pPixel;
	int tailleNom;

	// --- Traitement ---
	if(!fichier.rdbuf()->is_open())
	{
		cout << "\x1b[31m\x1b[1m[-]Err : Le fichier n'est pas ouvert !\x1b[0m" << endl;
		exit(1);
	}
	else
	{
		// ======== Encodage du fond ========
		this->fond.Save(fichier);	

		// ======== Encodage du nombre de Couleurs  ========
		fichier.write((char *)&nbCouleurs, sizeof(int)); 

		Iterateur<Couleur> itC(this->palette); 
		for (itC.reset() ; !itC.end() ; itC++) {
			((Couleur)itC).Save(fichier);
		}

		// ======== Encodage du nombre de Figures  ========
		fichier.write((char *)&nbFigures, sizeof(int)); 
		
		
		Iterateur<Figure *> itF(this->figures);
		for(itF.last(); !itF.end(); itF--)
		{
			if( (pRectangle = dynamic_cast<Rectangle *>( ((Figure *)itF) )))
				fichier.write("R", sizeof(char));

			if( (pLigne = dynamic_cast<Ligne *>( ((Figure *)itF) )))
				fichier.write("L", sizeof(char));

			if( (pPixel = dynamic_cast<Pixel *>( ((Figure *)itF) )))
				fichier.write("P", sizeof(char));


			// ======== Enregistrer d'abord la taille de la couleur && Enregistrer le nom de la couleur ==========
			tailleNom = strlen(((Figure *)itF)->getCouleur()->getNom());
			fichier.write((char*)&tailleNom, sizeof(int));
			fichier.write((char *)((Figure *)itF)->getCouleur()->getNom(), tailleNom);

			// ======== Save de la figure ========
			((Figure *)itF)->Save(fichier);


		}

	 	fichier.close(); // Fermeture du fichier
	}



}

void Dessin::Load(const char *nomFichier)
{
	std::ifstream fichier(nomFichier, ios::in);

	int nbC = 0;
	int nbF = 0;
	Couleur c1;


	char pLettreTmp;
	int tailleNom;
	Figure* figure;

	// ==============================
	// ========= Traitement =========
	// ==============================
	if(!fichier.rdbuf()->is_open())
	{
		cout << "\x1b[31m\x1b[1m[-]Err : Le fichier n'est pas ouvert !\x1b[0m" << endl;
	}
	else
	{
		// ========== Lecture du fond ==========
		this->fond.Load(fichier);

		// ========== Lecture du nombre de Couleurs ==========
		fichier.read((char *)&nbC, sizeof(int));

		for(int i = 0; i < nbC; i++) // (2) remplir la palette
		{
			c1.Load(fichier);
			this->palette.insere(c1);
		}

		// ========== Lecture du nombre de Figures ==========
		fichier.read((char *)&nbF, sizeof(int));

		// ===================== Lecture de la taille du caractère =====================

		for(int i = 0; i < nbF; i++) // (2) remplir la pile de figures
		{
			fichier.read((char*)&pLettreTmp, sizeof(char));

			if(pLettreTmp == 'R') { figure = new Rectangle; }
			if(pLettreTmp == 'L') { figure = new Ligne;     }
			if(pLettreTmp == 'P') { figure = new Pixel;     }

			fichier.read((char*)&tailleNom, sizeof(int)); // Taille Nom Couleur
			char *pNomCouleur = new char[tailleNom + 1];
			fichier.read((char*)pNomCouleur, tailleNom); // Nom de la Couleur			 

			// ======== Load de la figure ========
			figure->Load(fichier);

			ajouteFigure(figure, pNomCouleur);

			
			delete pNomCouleur; // Destruction suite à l'allocation
		}



		fichier.close(); // Fermeture du fichier
	}
}

