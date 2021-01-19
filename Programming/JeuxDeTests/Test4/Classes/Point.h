#ifndef POINT_H
#define POINT_H
class Point 
{

	friend std::ostream& operator<<(std::ostream& s, const Point &point);
	private:
		int x;
		int y;

		static int compteur;

	public:
		Point();
		~Point();	

		Point(int, int);
		Point(const Point& p);	
		Point& operator=(const Point& p);


		// Setters - Mutateurs
		void setX(int);
		void setY(int);


		// Getters - Accesseurs
		int getX() const;
		int getY() const;		


		void Affiche() const;
		static int getCompteur();

	};

#endif
