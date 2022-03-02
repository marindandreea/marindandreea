//header pentru a implementa functiile si clasele necesare jocului de sah
#pragma once
#include <iostream>
#include <cmath>
#include <string>
//enum pentru a facilita listarea pieselor 
enum Tip_Piesa { REGE, REGINA, NEBUN, CAL, TURA, PION, GOL }; 
enum Tip_Culoare { ALB, NEGRU, NICIUNA };

/*o tabla de sah necesita o tabela bidimensionala de patrate de joc
* am implementat o clasa denumita Tabla, derivata din clasa Patrat ( relatie has a)
* pe fiecare patrat se poate situa cate o piesa de sah, altfel GOL
*/
class Patrat
{
	Tip_Piesa piesa;
	Tip_Culoare culoare;
	int x, y;
public:
	// implementare functii de acces (set + get)
	void setSpatiu(Patrat*);
	void Golire();
	void setPiesaCuloare(Tip_Piesa piesa, Tip_Culoare culoare);
	Tip_Piesa getPiesa();
	Tip_Culoare getCuloare();

	void setX(int xnou) { x = xnou; }
	void setY(int ynou) { y = ynou; }
	int getX() { return x; }
	int getY() { return y; }
	Patrat(); //constructor
};

class Tabla
{
//tabla de sah are dimensiune de 8x8 intodeauna, astfel am alocat static un tablou bidimensional de tip clasa Patrat 
	Patrat patrat[8][8];
	Tip_Culoare rand = ALB;
//dat fiind ca avem 8 tipuri de piese de joc cu reguli diferite de deplasare, am implementat 8 functii diferite specifice
	bool mutaRege(Patrat* thisKing, Patrat* thatSpace);
	bool mutaRegina(Patrat* thisQueen, Patrat* thatSpace);
	bool mutaNebun(Patrat* thisBishop, Patrat* thatSpace);
	bool mutaCal(Patrat* thisKnight, Patrat* thatSpace);
	bool mutaTura(Patrat* thisRook, Patrat* thatSpace);
	bool mutaPion(Patrat* thisPawn, Patrat* thatSpace);
//functie generala de mutare cu parametrii coordonate
	bool realizeazamutare(int x1, int y1, int x2, int y2);
	void afisareTabla();
public:
	//functie de returnare a adresei de memorie unde sunt situate coordonatele patratului cu parametrii coordonatele patratului
	//POSIBIL PROBLEMA AICI
	Patrat* retAdresa(int x, int y) {
		return &patrat[x][y];
	}

	void setTabla();
	void setTabla(Patrat* p, int x, int y) {
		patrat[x][y] = *p;
	}
	bool famutare();
	bool incepeJocul();
	bool erege();
};
