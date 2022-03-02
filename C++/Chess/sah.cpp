#include "sah.h"
using namespace std;

//constructor fara parametri
Patrat::Patrat()
	:x(0), y(0)
{
	piesa = GOL;
	culoare = NICIUNA;
}

//setter pentru a atribui piesa si culoarea patratului (ajuta la rocada coordonatelor din mutare in cazul in care e valida)
void Patrat::setSpatiu(Patrat* tabla)
{
	culoare = tabla->getCuloare();
	piesa = tabla->getPiesa();
}

//Golire este un fel de setter in care i se atribuie valorile standard (piesa = GOL, culoare - NICIUNA)
void Patrat::Golire()
{
	piesa = GOL;
	culoare = NICIUNA;
}

//getter pentru a returna piesa 
Tip_Piesa Patrat::getPiesa()
{
	return piesa;
}

//getter pentru a returna culoarea
Tip_Culoare Patrat::getCuloare()
{
	return culoare;
}

//setter pentru a modifica patratul cu piesa si culoarea corespunzatoare, in cazul validarii
void Patrat::setPiesaCuloare(Tip_Piesa p, Tip_Culoare c)
{
	piesa = p;
	culoare = c;
}

//functia de afisare a tablei de joc
//tabla de joc este un tablou bidimensional de 8x8
//piesele trebuie initializate corespunzator, conform regulilor de sah
void Tabla::afisareTabla() {
	//afisare coordonatelor
	cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			Tip_Piesa p = patrat[i][j].getPiesa();
			Tip_Culoare c = patrat[i][j].getCuloare();
			//afisarea pieselor de joc (enum) cu switch
			switch (p)
			{
			case REGE: (c == ALB) ? cout << " K " : cout << " k ";
				break;
			case REGINA: (c == ALB) ? cout << " Q " : cout << " q ";
				break;
			case NEBUN:(c == ALB) ? cout << " N " : cout << " n ";
				break;
			case CAL:(c == ALB) ? cout << " C " : cout << " c ";
				break;
			case TURA: (c == ALB) ? cout << " T " : cout << " t ";
				break;
			case PION: (c == ALB) ? cout << " P " : cout << " p ";
				break;
				// cu \21 se afiseaza un caracter de tip casuta, pentru a vedea spatiile goale ale tablei de joc 
			case GOL: cout << " " << "\21" << " ";
				break;
			default: cout << "---";
				break;
			}
		}
		cout << endl;
	}
}

//functie de realizare 1a unei mutari famutare()
bool Tabla::famutare() {
	string mutare;
	string ajutor;
	int x1, x2, y1, y2;
	//functie de tip bool pentru a se termina mutarea
	bool opreste = false;
	while (!opreste)
	{
		(rand == ALB) ? cout << "MUTA ALB" << endl : cout << "MUTA NEGRU" << endl;
		cout << "Scrieti mutarea ca un sir de 4 caractere, incepand cu pozitia piesei pe care vreti sa o mutati (X1,Y1)(X2,Y2)" << endl;
		cin >> mutare;
		x1 = mutare[0] -48;
		y1 = mutare[1] -48;
		x2 = mutare[2] -48;
		y2 = mutare[3] -48;
		if (retAdresa(x1, y1)->getCuloare() == rand)
		{
			if (realizeazamutare(x1, y1, x2, y2) == false)
			{
				cout << "Ceva este in neregula" << endl;
			}
			else
				opreste = true;
		}
		else
			cout << "Aceasta nu este piesa ta :c" << endl;
	}
	//*********
	//CONDITIA DE CASTIG A JOCULUI = regele adversarului sa dispara
	//am impartit validarea in doua instructiuni if (in functie de culoarea pieselor de sah)
	//a trebuit sa verific daca mutarea se face cu o piesa diferita de regele de culoarea jucatorului 

	/*( altfel se castiga automat meciul si rezulta la probleme de logica, 
	dat fiind ca atunci cand mutam regele, coordonatele patratului in care 
	se face mutarea = coordonatele noi ale regelui => jocul se termina la orice  ) */
	if (retAdresa(x1, y1)->getPiesa() != REGE && retAdresa(x1, x1)->getCuloare() == ALB) {
		if (retAdresa(x2, y2)->getPiesa() == REGE && retAdresa(x2,y2)->getCuloare() == NEGRU)
			{
				cout << "ALB A CASTGAT!" << endl;
				return false;
			}
	}
	 if(retAdresa(x1, y1)->getPiesa() != REGE && retAdresa(x1, x2)->getCuloare() == NEGRU)
			{ if(retAdresa(x2,y2)->getPiesa() == REGE && retAdresa(x2, y2)->getCuloare() == ALB)
				cout << "NEGRU A CASTIGAT" << endl;
				return false;
			}
	
	//dupa ce s-a realizat mutarea corect, randul jucatorului a trecut si trebuie sa vina randul celuilalt jucator
	if (rand == NEGRU)
		rand = ALB;
	else
		rand = NEGRU;
	return true;
}
 
//functie de tip void pentru a seta tabla de joc corect la inceputul fiecarui meci
void Tabla::setTabla()
{ //initializarea pieselor albe pe tabla de sah
	patrat[0][0].setPiesaCuloare(TURA, ALB);
	patrat[1][0].setPiesaCuloare(CAL, ALB);
	patrat[2][0].setPiesaCuloare(NEBUN, ALB);
	patrat[3][0].setPiesaCuloare(REGINA, ALB);
	patrat[4][0].setPiesaCuloare(REGE, ALB);
	patrat[5][0].setPiesaCuloare(NEBUN, ALB);
	patrat[6][0].setPiesaCuloare(CAL, ALB);
	patrat[7][0].setPiesaCuloare(TURA, ALB);

	//initializarea pieselor negre pe tabla de sah
	patrat[0][7].setPiesaCuloare(TURA, NEGRU);
	patrat[1][7].setPiesaCuloare(CAL, NEGRU);
	patrat[2][7].setPiesaCuloare(NEBUN, NEGRU);
	patrat[3][7].setPiesaCuloare(REGINA, NEGRU);
	patrat[4][7].setPiesaCuloare(REGE, NEGRU);
	patrat[5][7].setPiesaCuloare(NEBUN, NEGRU);
	patrat[6][7].setPiesaCuloare(CAL, NEGRU);
	patrat[7][7].setPiesaCuloare(TURA, NEGRU);

	//pionii se situeaza pe toata coloana 1 si 6, fiind 16 pioni 
	for (int i = 0; i < 8; i++)
	{
		patrat[i][1].setPiesaCuloare(PION, ALB);
		patrat[i][6].setPiesaCuloare(PION, NEGRU);
	}
	//la inceput de meci, nu exista nicio piesa in coloanele 2-6
	//le initializam ca fiind fara piese (GOL) si fara nicio culoare (NICIUNA)
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			patrat[j][i].setPiesaCuloare(GOL, NICIUNA);
	}
	//setter pentru coordonatele X,Y
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			patrat[i][j].setX(i);
			patrat[i][j].setY(j);
		}
}

//functie bool incepeJocul()
//in momentul in care se incepe jocul, se afiseaza tabla de joc si se cere scrierea unei mutari
bool Tabla::incepeJocul()
{	//initial o sa se introduca in consola informatii precum zone de ajutor, legenda etc
	//pentru a afisa doar tabla de sah si a da clear consolei am uitilizat:
	//system("cls"); - sterge consola pentru a afisa doar tabla de sah nou modificata  
	system("cls");
	afisareTabla();
	return famutare();
}
//functie de mutare a regelui
//*regele se muta o casuta, indiferent de sens
//singura conditie e sa nu se pozitioneze pe o piesa din aceeasi trupa
bool Tabla::mutaRege(Patrat* rege, Patrat* spatiu) {
	//abs = modul, functie din bilioteca cmath
	/*am folosit abs() in cazul in care regele se muta o casuta "in spate" si astfel
	pozitia in care vrea sa se deplaseze - pozitia in care se situeaza deja = |-1| = 1 */
	if ((abs(spatiu->getX() - rege->getX()) == 1)||(abs(spatiu->getY() - rege->getY()) == 1))
		{
			spatiu->setSpatiu(rege);
			rege->Golire();
			return true;
		}
		else return false;
}

//functia muta regina
bool Tabla::mutaRegina(Patrat* regina, Patrat* spatiu) {
	//declarare variabilele coordonatelor
	//coordonatele reginei
	int reginaX = regina->getX();
	int reginaY = regina->getY();
	//coordonatele casutei in care se vrea mutarea
	int spatiuX = spatiu->getX();
	int spatiuY = spatiu->getY();
	int y;
	int x;
	//bool daca mutarea este invalida
	bool invalid = false;
	//se verifica daca cel putin o coordonata este diferita
	if (reginaX != spatiuX || reginaY != spatiuY)
	{   //in cazul in care se deplaseaza "tot inainte", se modifica doar coordonatele coloanei (Y)
			//si se realizeaza modificarea reginei pe tabla
		if (reginaX == spatiuX)
		{
			y = (spatiuY - reginaY) / (abs(spatiuY - reginaY));
			for (int i = reginaY + y; i != spatiuY; i += y)
			{
				if (patrat[spatiuX][i].getCuloare() != NICIUNA)
					return false;
			}
		}
		else
			//in cazul in care regina se deplaseaza "pe laterale", mutarea se face doar cu modificare de X
			if (reginaY == spatiuY)
			{
				x = (spatiuX - reginaX) / (abs(spatiuX - reginaX));
				for (int i = reginaX + x; i != spatiuX; i += x)
				{ //se verifica daca regina nu "a sarit" peste alte piese
					if (patrat[i][spatiuY].getCuloare() != NICIUNA)
						return false;
				}
			}
			else
				if (abs(reginaX - spatiuX) == abs(reginaY - spatiuY))
				{
					x = (spatiuX - reginaX) / (abs(spatiuX - reginaX));
					y = (spatiuY - reginaY) / (abs(spatiuY - reginaY));
					//se verifica daca regina nu "a sarit" peste alte piese
					for (int i = 1; i < abs(reginaX - spatiuX); i++)
					{
						if (patrat[reginaX + x * i][reginaY + y * i].getCuloare() != NICIUNA)
							return false;
					}
				}
				else
					return false;
	}
	if (invalid == false)
	{
		spatiu->setSpatiu(regina);
		regina->Golire();
		return true;
	}
	else
	{
		cout << "Mutare invalida( Regina )";
		return false;
	}
}
//functia de mutare a nebunului
//nebunul se deplaseaza pe diagonale
bool Tabla::mutaNebun(Patrat* nebun, Patrat* spatiu) { 
	int nebunX = nebun->getX();
	int nebunY = nebun->getY();
	int spatiuX = spatiu->getX();
	int spatiuY = spatiu->getY();
	bool invalid = false;
	if (abs(nebunX - spatiuX) == abs(nebunY - spatiuY))
	{ 
	//chiar daca coordonatele spatiului - coordonatele nebunului pot da negativ; 
	//de ex pozitia (3,0) in (1,2), unde 0-2 < 0
	//Astfel, am creat 2 variabile X,Y pentru a sti daca ne deplasam "in stanga" sau "in dreapta"
	//variabilele X, Y pot avea valorile -1 sau 1, fiind impartite la valoarea in modul a aceleiasi diferente
		int x = (spatiuX - nebunX) / (abs(spatiuX - nebunX));
		int y = (spatiuY - nebunY) / (abs(spatiuY - nebunY));
	//|nebunX - spatiuX| == |nebunY - spatiuY| (regula diagonalei)
		for (int i = 1; i < abs(nebunX - spatiuX); i++)
		{
			//aici se verifica daca in drumul pe care "bate" nebunul se afla vreo piesa de joc
			//nebunul nu poate "sa sara" peste piese deja existente
			if (patrat[nebunX + x * i][nebunY + y * i].getCuloare() != NICIUNA)
				return false;
		}
	}
	else
		return false;
	//verificare daca mutarea a fost valida
	//daca se indeplineste conditia, se realizeaza rocada intre coordonatele initiale si finale
	if (invalid == false)
	{
		spatiu->setSpatiu(nebun);
		nebun->Golire();
		return true;
	}
	else
	{
		cout << "Mutare invalida(Nebun)";
		return false;
	}
}
//functia muta cal
bool Tabla::mutaCal(Patrat* cal, Patrat* spatiu)
{	//coordonatele de care avem nevoie
	int calX = cal->getX();
	int calY = cal->getY();
	int spatiuX = spatiu->getX();
	int spatiuY = spatiu->getY();

	//conditia de validare a mutarii
	//calul se poate deplasa 2 spatii in fata, una lateral sau un spatiu in fata, 2 lateral
	//in cazul in care conditia este indeplinita, se goleste spatiul in care a fost calul si se atribuie valoarea lui in spatiul ales
	if ((abs(calX - spatiuX) == 2 && abs(calY - spatiuY) == 1) || (abs(calX - spatiuX) == 1 && abs(calY - spatiuY) == 2))
	{
		spatiu->setSpatiu(cal);
		cal->Golire();
		return true;
	}
	else
	{
		cout << "Mutare inalida(Cal)";
		return false;
	}
}
//functia muta tura
bool Tabla::mutaTura(Patrat* tura, Patrat* spatiu)
{
	int turaX = tura->getX();
	int turaY = tura->getY();
	int spatiuX = spatiu->getX();
	int spatiuY = spatiu->getY();
	bool invalid = false;
	//tura se deplaseaza in linie dreapta
	if (turaX != spatiuX || turaY != spatiuY)
	{	//intram in cazul in care tura se deplaseaza pe axa OY
		if (turaX == spatiuX)
		{
			int y = (spatiuY - turaY) / (abs(spatiuY - turaY));
			for (int i = turaY + y; i != spatiuY; i += y)
			{ //se verifica daca tura nu "a sarit" peste alte piese
				if (patrat[spatiuX][i].getCuloare() != NICIUNA)
					return false;
			}
		}
		else
			//intram in cazul in care tura se deplaseaza pe axa OX
			if (turaY == spatiuY)
			{

				int x = (spatiuX - turaX) / (abs(spatiuX - turaX));
				for (int i = turaX + x; i != spatiuX; i += x)
				{
					if (patrat[i][spatiuY].getCuloare() != NICIUNA)
						return false;
				}
			}
			else
				return false;
	}
	//verificare daca mutarea a fost valida
	//daca se indeplineste conditia, se realizeaza rocada intre coordonatele initiale si finale
	if (invalid == false)
	{
		spatiu->setSpatiu(tura);
		tura->Golire();
		return true;
	}
	else
	{//mesaj eroare
		cout << "Mutare invalida (tura)";
		return false;
	}
}

bool Tabla::mutaPion(Patrat* pion, Patrat* spatiu) {
	using namespace std;
	bool invalid = false;
	int pionX = pion->getX();
	int pionY = pion->getY();
	int spatiuX = spatiu->getX();
	int spatiuY = spatiu->getY();


	if (pion->getCuloare() == ALB)
	{
		if (pionX == spatiuX && spatiuY == pionY + 1 && spatiu->getCuloare() == NICIUNA)
		{
			spatiu->setSpatiu(pion);
			pion->Golire();
			return true;
		}
		else
			if ((pionX + 1 == spatiuX || pionX - 1 == spatiuX) && pionY + 1 == spatiuY && spatiu->getCuloare() == NEGRU)
			{
				spatiu->setSpatiu(pion);
				pion->Golire();
				return true;
			}
			else
				return false;
	}
	else
		if (pion->getCuloare() == NEGRU)
		{
			if (pionX == spatiuX && spatiuY == pionY - 1 && spatiu->getCuloare() == NICIUNA)
			{
				spatiu->setSpatiu(pion);
				pion->Golire();
				return true;
			}
			else
				if ((pionX + 1 == spatiuX || pionX - 1 == spatiuX) && pionY - 1 == spatiuY && spatiu->getCuloare() == ALB)
				{
					spatiu->setSpatiu(pion);
					pion->Golire();
					return true;
				}
				else
					return false;
		}
		else
			return false;
}
//VALIDARI GENERAL VALABILE
//functia de verificare in vederea mutarii cu parametrii coordonatele (x1, y1) (x2, y2)
//aici se verifica lucrurile generale, in ciuda piesei utilizate
bool Tabla::realizeazamutare(int x1, int y1, int x2, int y2) {
	//se verifica daca coordonatele sunt cuprinse intre 0 si 7
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		cout << "Nu se poate, este in afara suprafetei de joc :C" << std::endl;
		return false;
	}
	//declararea pozitiilor de joc: pozitie initiala, pozitie finala ca pointer Patrat
	Patrat* pozinitiala = retAdresa(x1, y1);
	Patrat* pozfinala = retAdresa(x2, y2);

	//aici se verifica daca pozitia finala respecta conditia de a fi pe un spatiu gol sau inamic 
	if (pozinitiala->getCuloare() == pozfinala->getCuloare() && pozfinala->getCuloare() != NICIUNA)
	{
		cout << "Mutare invalida! Nu te poti muta pe o alta piesa care iti apartine! :C" << endl;
		return false;
	}
	//apelarea functiilor specifice fiecarei piese de joc
	switch (pozinitiala->getPiesa())
	{
	case REGE: return mutaRege(pozinitiala, pozfinala);
		break;
	case REGINA: return mutaRegina(pozinitiala, pozfinala);
		break;
	case NEBUN: return mutaNebun(pozinitiala, pozfinala);
		break;
	case CAL: return mutaCal(pozinitiala, pozfinala);
		break;
	case TURA: return mutaTura(pozinitiala, pozfinala);
		break;
	case PION: return mutaPion(pozinitiala, pozfinala);
		break;
	case GOL: cout << "Nu ai piesa aici, incearca alta mutare:" << endl;  return false;
		break;
	default: cerr << "Ceva nu e bine" << endl;
		break;
	}
	return false;
}
