#include <stdlib.h>
#include <iostream>
using namespace std;
#include "Dessin.h"
#include "Pixel.h"
#include "Ligne.h"
#include "Rectangle.h"
#include "Couleur.h"
#include <fstream>
// --- 
#include "./WindowSDL/WindowSDL.h"
#include "./Interface/Bouton.h"
#include "./Interface/BoutonCouleur.h"
#include "./Interface/ToolBar.h"
#include "./Exception/BaseException.h"
#include "./Exception/InvalidColorException.h"

//void InitGUI(ToolBar &toolbar);

// ---- Les prototypes ----

char*& readFile(ifstream& fichier, char*& pChaine);
void InitGUI(ToolBar &toolbar, const char *nomFichier);
char nom[5];
int Menu();


//TODO: (OK) Attention lorsque on dessine la même figure => L'ID de la figure est similaire à celle de la précédente.
//TODO: (OK) Faire le Menu
//TODO: (OK) Utiliser les try {} catch


int Menu()
{
	int choix = 1;
	cout << "\x1b[35m\x1b[1m=========================================================\x1b[0m" << endl;
	cout << "\x1b[35m\x1b[1m===================== \x1b[34m\x1b[5mPaint ~ Menu\x1b[35m ======================\x1b[0m" << endl;	
	cout << "\x1b[35m\x1b[1m=========================================================\x1b[0m" << endl;
	cout << "\x1b[34m[0]\x1b[1m 	Quitter le menu  						   \x1b[0m" << endl;
	cout << "\x1b[34m[1]\x1b[1m 	Quitter l'application  									   \x1b[0m" << endl;
	cout << "\x1b[34m[2]\x1b[1m 	Charger un fichier  					   \x1b[0m" << endl;
	cout << "\x1b[34m[3]\x1b[1m	Enregistrer un dessin 					   \x1b[0m" << endl;
	cout << "\x1b[34m[4]\x1b[1m 	Ajouter une nouvelle couleur  		   \x1b[0m" << endl;
	cout << "\x1b[34m[5]\x1b[1m     Creer nouvelle couleur par melange    \x1b[0m" << endl;
	cout << "\x1b[34m[6]\x1b[1m     Eclaircir une couleur existante 	   \x1b[0m" << endl;
	cout << "\x1b[34m[7]\x1b[1m     Assombir une couleur existante  	   \x1b[0m" << endl;
	cout << "\x1b[34m[8]\x1b[1m     Modifier couleur fond 						\x1b[0m" << endl;
	cout << "\x1b[34m[9]\x1b[1m 	Afficher le nombre d'objets  	 	   \x1b[0m" << endl;
	cout << "\x1b[34m[10]\x1b[1m 	Afficher les couleurs  				   \x1b[0m" << endl;
	cout << "\x1b[34m[11]\x1b[1m 	Afficher les figures  					   \x1b[0m" << endl;
	cout << "\x1b[35m\x1b[1m=========================================================\x1b[0m" << endl;
	cout << "\x1b[34m\x1b[1m# \x1b[0m";
	cin >> choix;
	
	return choix;
}

int main()
{
  ToolBar toolbar;
  InitGUI(toolbar, "config.csv");

  Dessin* dessin = new Dessin();
  toolbar.ajouteCouleur(dessin->ajouteCouleur(Couleur::ROUGE));  // pour l'instant...
  toolbar.ajouteCouleur(dessin->ajouteCouleur(Couleur::VERT));   // pour l'instant...
  toolbar.ajouteCouleur(dessin->ajouteCouleur(Couleur::BLEU));   // pour l'instant...
  toolbar.ajouteCouleur(dessin->ajouteCouleur(Couleur::ORANGE)); // pour l'instant...
  toolbar.SyncroToolBar(dessin->getPalette());

  const char* figure = NULL;   // outil de dessin selectionne
  Couleur*    couleur = NULL;  // couleur selectionnee

  while (true)
  {
    WindowSDLclick clic = WindowSDL::waitClick();
    if (clic.getX() == -1) break;

    const char* nomBouton = toolbar.clic(clic.getX(),clic.getY());
    if (nomBouton) // clic sur un bouton
    {
      cout << "Bouton clique = " << nomBouton << endl;

      // Bouton Undo
      if (strcmp(nomBouton,"B_UNDO") == 0)
      {
        dessin->undo();
        dessin->Dessine();
      }

		// -------------------------- 

		 // Bouton Menu
      // ... a faire
		if (strcmp(nomBouton,"B_MENU") == 0)
      {
			WindowSDL::close();
			int choix = 1, val;
			while(choix) 
			{
				choix = Menu();

				Couleur couleurTmp;
				char nomFichier[36];
				char nomCouleur[36];

				// -- Eclaircir Couleur --
				WindowSDLclick clicTmp;
				const char* nomCouleurFirst;
				const char* nomCouleurSecond;

				Dessin *pDessinTmp;

				Couleur *pCouleurTmp1, *pCouleurTmp2;
				Couleur *pCouleurTmp;

				switch(choix)
				{
					case 0:
						cout << "Vous allez quitter le menu !" << endl;
						break;
					case 1:
						cout << "Vous quitter l'application !" << endl;
						return 0;
						break;

					case 2: // --- Chargement d'un dessin ---
						cout << "\x1b[33m[+]\x1b[34m\x1b[1m Entrez le nom du fichier : \x1b[0m" << endl;
						cin >> nomFichier;
//						pDessinTmp = new Dessin();
						try {
							dessin->Load(nomFichier);
						}
						catch(BaseException &e) { cout << e.getErreur() << endl; } 
						 
//						dessin = pDessinTmp; // Pour avoir une dessin au propre, pas de doublon
						cout << "\x1b[32m[+]\x1b[1m Nous avons bien charge le dessin !\x1b[0m" << endl;
						break;

					case 3:
						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Entrez le nom du fichier : \x1b[0m" << endl;
						cin >> nomFichier;
						dessin->Save(nomFichier);
						cout << "\x1b[32m[+]\x1b[1m Nous avons bien enregistre le Dessin !\x1b[0m" << endl;
						break;

					case 4: // --- Ajout d'une nouvelle couleur
						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Entrez le nom de la couleur : \x1b[0m" << endl;
						cin >> nomCouleur;

						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Entrez la valeur pour le Rouge (0->255) : \x1b[0m" << endl;
						cin >> val;
						try {
							couleurTmp.setRouge(val);
						} catch(InvalidColorException& e) {
						 	 e.Affiche();
						} catch(BaseException &e) {
							 std::cout << e.getErreur() << std::endl;
						} 

						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Entrez la valeur pour le Vert (0->255) : \x1b[0m" << endl;
						cin >> val;
						try {
							couleurTmp.setVert(val);
						} catch(InvalidColorException& e) {
						 	 e.Affiche();
						} catch(BaseException &e) {
							 std::cout << e.getErreur() << std::endl;
						}


						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Entrez la valeur pour le Bleu (0->255) : \x1b[0m" << endl;
						cin >> val;
						try {
							couleurTmp.setBleu(val);
						} catch(InvalidColorException& e) {
						 	 e.Affiche();
						} catch(BaseException &e) {
							 std::cout << e.getErreur() << std::endl;
						}

						dessin->ajouteCouleur(couleurTmp);
						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Nous avons bien ajouté la couleur dans la palette !\x1b[0m" << endl;
						break;

					case 5: // --- Melanger les couleurs ---
						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Cliquer sur les couleurs que vous-voulez mélanger \x1b[0m" << endl;
						WindowSDL::open(840,600);
 						WindowSDL::importFromBMP("imageFond.bmp");
						toolbar.SyncroToolBar(dessin->getPalette());

						// --- Couleur 1 ---
						do {
						   clicTmp = WindowSDL::waitClick();
							if (clicTmp.getX() == -1) break;
							nomCouleurFirst = toolbar.clic(clicTmp.getX(), clicTmp.getY());
							pCouleurTmp1 = toolbar.getCouleur(nomCouleurFirst); 
						} while(pCouleurTmp1 == NULL);
						cout << "\x1b[33m[+] Vous avez fait un clic sur la Couleur \x1b[0m" << pCouleurTmp1->getNom() << endl;

						// --- Couleur 2 ---
						do {
						   clicTmp = WindowSDL::waitClick();
							if (clicTmp.getX() == -1) break;
							nomCouleurSecond = toolbar.clic(clicTmp.getX(), clicTmp.getY());
							pCouleurTmp2 = toolbar.getCouleur(nomCouleurSecond); 
						} while(pCouleurTmp2 == NULL);
						cout << "\x1b[33m[+] Vous avez fait un clic sur la Couleur \x1b[0m" << pCouleurTmp2->getNom() << endl;

						pCouleurTmp = new Couleur();
						*pCouleurTmp = *pCouleurTmp1 + *pCouleurTmp2;
						dessin->ajouteCouleur(*pCouleurTmp);
		
						WindowSDL::close();
						break;

					case 6: // --- Eclaircir une couleur existante ---
						cout << "Selectionner la couleur que vous-voulez eclaircir" << endl;
						WindowSDL::open(840, 600);
						WindowSDL::importFromBMP("imageFond.bmp");

						toolbar.SyncroToolBar(dessin->getPalette());
						do {
							clicTmp = WindowSDL::waitClick();
							if (clicTmp.getX() == -1) break;
							nomCouleurFirst = toolbar.clic(clicTmp.getX(), clicTmp.getY());
							pCouleurTmp1 = toolbar.getCouleur(nomCouleurFirst);
						} while(pCouleurTmp1 == NULL);

						WindowSDL::close();

						cout << "Eclaircir de combien la Couleur ? " << pCouleurTmp1->getNom() << endl;
						cin >> val;
						*pCouleurTmp1 = *pCouleurTmp1 + val;
						break;

					case 7: // --- Assombir une couleur existante ---
						cout << "Selectionner la couleur que vous voulez assombrir :" << endl;
						WindowSDL::open(840, 600);
						WindowSDL::importFromBMP("imageFond.bmp");

						toolbar.SyncroToolBar(dessin->getPalette());
						do {
							clicTmp = WindowSDL::waitClick();
							if (clicTmp.getX() == -1) break;
							nomCouleurFirst = toolbar.clic(clicTmp.getX(), clicTmp.getY());
							pCouleurTmp2 = toolbar.getCouleur(nomCouleurFirst);
						} while(pCouleurTmp2 == NULL);

						WindowSDL::close();

						cout << "Entrez de combien vous voulez assombrir la Couleur : " << pCouleurTmp2->getNom() << endl;
						cin >> val;
						*pCouleurTmp2 = *pCouleurTmp2 - val;
						break;
					case 8: // --- Modifier la couleur de fond ---
						cout << "Entrez la Couleur de fond" << endl;
						couleurTmp.setNom("");

						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Entrez la valeur pour le Rouge (0->255) : \x1b[0m" << endl;
						cin >> val;
						try {
							couleurTmp.setRouge(val);
						} catch(InvalidColorException& e) {
						 	 e.Affiche();
						} catch(BaseException &e) {
							 std::cout << e.getErreur() << std::endl;
						} 


						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Entrez la valeur pour le Vert (0->255) : \x1b[0m" << endl;
						cin >> val;
						try {
							couleurTmp.setVert(val);
						} catch(InvalidColorException& e) {
						 	 e.Affiche();
						} catch(BaseException &e) {
							 std::cout << e.getErreur() << std::endl;
						}
						


						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Entrez la valeur pour le Bleu (0->255) : \x1b[0m" << endl;
						cin >> val;
						try {
							couleurTmp.setBleu(val);
						} catch(InvalidColorException& e) {
						 	 e.Affiche();
						} catch(BaseException &e) {
							 std::cout << e.getErreur() << std::endl;
						}
						

						dessin->setFond(couleurTmp);
						break;
					case 9:
						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Nombre de Figures : " <<  Figure::getCompteur() << "\x1b[0m" << endl;
						break;
					case 10:
						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Notre palette de couleurs : \x1b[0m" << endl;
						dessin->affichePalette();
						break;

					case 11:
						cout << "\x1b[31m[+]\x1b[34m\x1b[1m Nos figures : \x1b[0m" << endl;
						dessin->afficheFigures();
						break;
				
				}
			}
			WindowSDL::open(840, 600);	
			WindowSDL::importFromBMP("imageFond.bmp");
			toolbar.SyncroToolBar(dessin->getPalette());
			dessin->Dessine();
		}
		// ---------------------------
     continue;
	 }
	 
    // Clic dans la zone de dessin
    figure = toolbar.getFigureSelectionnee();
    if (figure == NULL)  { cout << "Vous devez selectionner un outil de dessin !" << endl; continue; }
    couleur = toolbar.getCouleurSelectionnee();
    if (couleur == NULL) { cout << "Vous devez selectionner une couleur !" << endl; continue; }
    
    if (strcmp(figure,"B_PIXEL") == 0)
    {
      cout << "Dessin d'un PIXEL ok" << endl;

		sprintf(nom, "P%d", Figure::getCompteur());
		try {     
			dessin->ajouteFigure(new Pixel(nom, Point(clic.getX(),clic.getY()),NULL),couleur->getNom());
		} 
		catch(BaseException e) { cout << e.getErreur() << endl; }
		catch(invalid_argument &e) { std::cout << "Argument invalide" << e.what() << std::endl; }
      dessin->Dessine();
    }

    if (strcmp(figure,"B_LIGNE") == 0)
    {
      cout << "Dessin d'une ligne... cliquez sur l'extremite !" << endl;
      WindowSDLclick clic2 = WindowSDL::waitClick();

		sprintf(nom, "L%d", Figure::getCompteur());
		try { 
  	 		dessin->ajouteFigure(new Ligne(nom, Point(clic.getX(),clic.getY()),Point(clic2.getX(),clic2.getY()),NULL),couleur->getNom());
		} catch(BaseException e) { cout << e.getErreur() << endl; } 
		catch(invalid_argument &e) { std::cout << "Argument invalide" << e.what() << std::endl; }
 
		dessin->Dessine();
      cout << "Dessin d'une LIGNE ok" << endl;
    }

    if (strcmp(figure,"B_RECTANGLE_CREUX") == 0)
    {
      cout << "Dessin d'un rectangle creux... cliquez sur l'autre coin !" << endl;
      WindowSDLclick clic2 = WindowSDL::waitClick();
      int largeur = clic2.getX() - clic.getX();
      int hauteur = clic2.getY() - clic.getY();

		sprintf(nom, "R%d", Figure::getCompteur());
		try { 
	      dessin->ajouteFigure(new Rectangle(nom, Point(clic.getX(),clic.getY()),largeur,hauteur,false,NULL),couleur->getNom());
		} catch(BaseException e) { cout << e.getErreur() << endl; }
		catch(invalid_argument &e) { std::cout << "Argument invalide" << e.what() << std::endl; }

      dessin->Dessine();
      cout << "Dessin d'un RECTANGLE CREUX ok" << endl;
    }

    if (strcmp(figure,"B_RECTANGLE_PLEIN") == 0)
    {
      cout << "Dessin d'un rectangle plein... cliquez sur l'autre coin !" << endl;
      WindowSDLclick clic2 = WindowSDL::waitClick();
      int largeur = clic2.getX() - clic.getX();
      int hauteur = clic2.getY() - clic.getY();

		sprintf(nom, "R%d", Figure::getCompteur());
		try { 
	      dessin->ajouteFigure(new Rectangle(nom, Point(clic.getX(),clic.getY()),largeur,hauteur,true,NULL),couleur->getNom());
		} catch(BaseException e) { cout << e.getErreur() << endl; }
		catch(invalid_argument &e) { std::cout << "Argument invalide" << e.what() << std::endl; }

      dessin->Dessine();
      cout << "Dessin d'un RECTANGLE PLEIN ok" << endl;
    }
  }

  cout << "Fin de l'application..." << endl;
  WindowSDL::close();

  return 0;
}



//void InitGUI(ToolBar &toolbar)
//{

//  WindowSDL::open(840,600);
//  WindowSDL::importFromBMP("imageFond.bmp");

//  toolbar.ajouteBoutonFigure(Bouton("B_PIXEL",Point(0,0),Point(39,39)));
//  toolbar.ajouteBoutonFigure(Bouton("B_LIGNE",Point(40,0),Point(79,39)));
//  toolbar.ajouteBoutonFigure(Bouton("B_RECTANGLE_CREUX",Point(80,0),Point(119,39)));
//  toolbar.ajouteBoutonFigure(Bouton("B_RECTANGLE_PLEIN",Point(120,0),Point(159,39)));

//  toolbar.setBoutonUndo(Bouton("B_UNDO",Point(200,0),Point(239,39)));
//  toolbar.setBoutonMenu(Bouton("B_MENU",Point(240,0),Point(279,39)));

//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR1",Point(320,0),Point(359,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR2",Point(360,0),Point(399,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR3",Point(400,0),Point(439,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR4",Point(440,0),Point(479,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR5",Point(480,0),Point(519,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR6",Point(520,0),Point(559,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR7",Point(560,0),Point(599,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR8",Point(600,0),Point(639,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR9",Point(640,0),Point(679,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR10",Point(680,0),Point(719,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR11",Point(720,0),Point(759,39)));
//  toolbar.ajouteBoutonCouleur(BoutonCouleur("B_COULEUR12",Point(760,0),Point(799,39)));

//}





char*& readFile(ifstream& fichier, char*& pChaine)
{

	while( (std::getline(fichier, pChaine, ';')) && !fichier.eof())
	{
		return pChaine;
	}
//	char tmp[50] = {0};
//	char lu = 0;
//	int compteur = 0;
//	while(lu != ';' && lu != '\n' && !fichier.eof())
//   {
// 		fichier.get(lu);
//		tmp[compteur] = lu;
//		compteur++;
//   }
//	if(fichier.eof())
//	{
//		pChaine = NULL;
//		return pChaine;
//	}	
//		
//	pChaine = new char[compteur];
//	strcpy(pChaine, tmp);
//	pChaine[compteur - 1] = 0;
//	return pChaine;

}


void InitGUI(ToolBar &toolbar, const char *nomFichier) // config.csv
{
  int windowX, windowY;
  char *pChaine, *pType, *pNom;
  char *pPointX1, *pPointY1, *pPointX2, *pPointY2;

  ifstream fichier(nomFichier, ios::in);
  if(!fichier.is_open())
  {
 		cout << "\x1b[31m[-]\x1b[1m Erreur de lecture \x1b[0m" << endl;
//		exit(1);
  }

  // ---- La fenêtre ----
  readFile(fichier, pChaine);
  windowX = atoi(pChaine); // Conversion ASCII to Integer
  readFile(fichier, pChaine);
  windowY = atoi(pChaine);
  WindowSDL::open(windowX, windowY); // Ouverture
  // ----      ----- 
 
  // --- Le nom du fichier ---
  readFile(fichier, pChaine);
  WindowSDL::importFromBMP(pChaine);
  
  // --- Type de figure ---
  readFile(fichier, pType);

  do {
      readFile(fichier, pNom);
		readFile(fichier, pPointX1);
		readFile(fichier, pPointY1);
		readFile(fichier, pPointX2);
		readFile(fichier, pPointY2);
		if( (strcmp(pType, "B_FIGURE") == 0) )
      {
			cout << "Nom : " << pNom << " Point X1 : " << pPointX1 << " Point X2 " << endl;
			toolbar.ajouteBoutonFigure(BoutonCouleur(pNom, Point(atoi(pPointX1), atoi(pPointY1)), Point(atoi(pPointX2), atoi(pPointY2))));
      }	
	
		if( (strcmp(pType, "B_COULEUR") == 0) )
      {
			cout << "Nom : " << pNom << " Point X1 : " << pPointX1 << " Point X2 " << endl;
			toolbar.ajouteBoutonCouleur(BoutonCouleur(pNom, Point(atoi(pPointX1), atoi(pPointY1)), Point(atoi(pPointX2), atoi(pPointY2))));
      }		
				
		if( (strcmp(pType, "B_UNDO") == 0) )
      {
			cout << "Nom : " << pNom << " Point X1 : " << pPointX1 << " Point X2 " << endl;
			toolbar.setBoutonUndo(BoutonCouleur(pNom, Point(atoi(pPointX1), atoi(pPointY1)), Point(atoi(pPointX2), atoi(pPointY2))));
      }		
		
		if( (strcmp(pType, "B_MENU") == 0) )
      {
			cout << "Nom : " << pNom << " Point X1 : " << pPointX1 << " Point X2 " << endl;
			toolbar.setBoutonMenu(BoutonCouleur(pNom, Point(atoi(pPointX1), atoi(pPointY1)), Point(atoi(pPointX2), atoi(pPointY2))));
      }		

		readFile(fichier, pType);

  } while(pType != NULL);
 
}

