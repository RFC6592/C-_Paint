#include "Dessin.h"

Dessin::Dessin() {
	setFond(Couleur(0,0,0,"Noir"));	
}

Dessin::Dessin(const Couleur& c) {
	setFond(c);	
}

Dessin::~Dessin() {
	while (!figures.estVide()) {
		figures.pop();
	}
	
}

Liste<Couleur>& Dessin::getPalette() {
	return palette;
}

Couleur* Dessin::ajouteCouleur(Couleur& c) throw(BaseException) {
	char err[50];
	Iterateur<Couleur> it(palette);
	it.reset();
	while (!it.end() && strcmp(c.getNom(), ((Couleur)it).getNom())) { it++; }
	if (!it.end()) {
		sprintf (err, "Couleur deja utilise ! (%s)", ((Couleur)it).getNom());
		throw (BaseException(err));
	}
	palette.insere(c);
	return &c;
	
}

void Dessin::ajouteFigure(Figure* f, const char* id) throw(BaseException) {		//si figure existe exception, si couleur existe pas aussi
	char err[50];
	Iterateur<Couleur> it(palette);
	Iterateur<Figure *> it2(figures);
	it.reset();
	it2.reset();
	while (!it.end() && strcmp(id, ((Couleur)it).getNom())) { it++;	}
	if (it.end()) {
		sprintf (err, "Couleur inexistante ! (%s)", id);
		throw (BaseException(err));
	}
	
	while (!it2.end() && strcmp(((Figure*)it2)->getId(), f->getId())) { it2++; }
	
	if (!it2.end()) {
		sprintf (err, "Figure deja existante ! (%s)", f->getId());
		throw (BaseException(err));
	}	
	f->setCouleur(&it);
	figures.insere(f);
	

}

void Dessin::Dessine() {
	WindowSDL::fillRectangle(fond.getRouge(), fond.getVert(), fond.getBleu(), 0, 40, 830, 600);
	if (!figures.estVide()) {
		Iterateur<Figure*> it(figures);
		for (it.last() ; !it.end() ; it--)
			((Figure*)it)->Dessine();
	}

}

void Dessin::undo() {
	if (!figures.estVide()) {
		figures.pop();
	}
	else 
		cout << "la pile de figures est vide ! " << endl;
}

void Dessin::affichePalette() {
	Iterateur<Couleur> it(palette);
	cout << "adresse : " << &it << endl;
	palette.Affiche();
}

void Dessin::afficheFigures() {
	Iterateur<Figure*> it(figures);
	for (it.reset();!it.end();it++) {
		
		Pixel* pp = dynamic_cast<Pixel*>((Figure*)it);
		if (pp != NULL) cout << *pp << endl;
		
		Ligne* pl = dynamic_cast<Ligne*>((Figure*)it);
		if (pl != NULL) cout << *pl << endl;
		
		Rectangle* pr = dynamic_cast<Rectangle*>((Figure*)it);
		if (pr != NULL) cout << *pr << endl;
	}	
}
void Dessin::setFond(Couleur c) {
	fond = c;
}

const Couleur& Dessin::getFond() const { return fond; }

void Dessin::Save(const char* c) {
	ofstream fichier(c,ios::out);
	if (!fichier.is_open()) {
		cout << "\x1b[31merreur d'ouverture du fichier\x1b[0m" << endl;
		exit(1);
	}
	Iterateur<Couleur> it(palette);
	Iterateur<Figure*> it2(figures);
	int nbrCouleurs;
	int nbrFigures;
	
	//enregistrement du  fond
	fond.Save(fichier);
	
	//enregistrement des couleurs
	nbrCouleurs = palette.getNombreElements();
	fichier.write((char*)&nbrCouleurs, sizeof(int));
	it.reset();
	for (int i=0; i<nbrCouleurs;it++,i++) {
		((Couleur)it).Save(fichier);
	}
	
	//enregistrement des figures
	nbrFigures = figures.getNombreElements();
	fichier.write((char*)&nbrFigures, sizeof(int));
	it2.last();
	for (int i=0;i<nbrFigures;it2--,i++) {
	
		if (dynamic_cast<Pixel*>((Figure*)it2)) fichier.write("P", sizeof(char));
		
		if (dynamic_cast<Ligne*>((Figure*)it2)) fichier.write("L", sizeof(char));

		if (dynamic_cast<Rectangle*>((Figure*)it2)) fichier.write("R", sizeof(char));
		
		((Figure*)it2)->Save(fichier);
		short taille=strlen(((Figure*)it2)->getCouleur()->getNom());
		fichier.write((char*)&taille, sizeof(short));
		fichier.write((char*)((Figure*)it2)->getCouleur()->getNom(), taille);
	}
	fichier.close();

}
bool Dessin::Load(const char* c) {
	ifstream fichier(c,ios::in);
	if (!fichier.is_open()) {
		cout << "\x1b[31merreur de lecture\x1b[0m" << endl;
		return 1;
	}
	
	Iterateur<Couleur> it(palette);
	int nbrCouleurs;
	int nbrFigures;
	char t;
	Couleur tmp;
	Figure* fig;

	//lecture fond
	fond.Load(fichier);
	//enregistrement palette
	fichier.read((char*)&nbrCouleurs, sizeof(int));
	for (int i=0;i<nbrCouleurs;i++) {
		tmp.Load(fichier);
		ajouteCouleur(tmp);
	}
	//lecture figures
	fichier.read((char*)&nbrFigures, sizeof(int));
	for (int i=0;i<nbrFigures;i++) {
		fichier.read((char*)&t, sizeof(char));
		if (t=='P') fig = new Pixel;
		if (t=='L') fig = new Ligne;
		if (t=='R') fig = new Rectangle;
		fig->Load(fichier);
		
		short taille;
		fichier.read((char*)&taille, sizeof(short));
		char* couleur = new char[taille+1];
		fichier.read((char*)couleur, taille);
		ajouteFigure(fig, couleur);
		delete couleur;
	}
	fichier.close();
	return 0;
}


















