#include "sah.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
	Tabla t;
	string confirmare;
	bool jocnou = true;
	cout << "B I N E   A I   V E N I T!" << endl << endl << endl;
	cout << "Te bagi la un meci de sah?" << endl << endl;
	cout << "**Daca ai semne de intrebare, apasa 1." << endl;
	cout << "Daca nu, apasa orice altceva.** " << endl;
	cout << "Raspuns: ";
	cin >> confirmare;

	if (confirmare == "1")
	{
		cout << "-------------------------------------------------------" << endl << endl;
		cout << "Sectiunea de ajutor a jucatorului:" << endl;
		cout << "PIESELE ALBE SUNT CELE AFISATE CU MAJUSCULE (K,Q,N,C,T,P)" << endl;
		cout<<"piesele negre sunt cele afisate cu litera mica(k,q,n,c,t,p)"<< endl<<endl;
		cout << "---------Legenda----------" << endl;
		cout << "K,k = Rege - se deplaseaza un singur spatiu" << endl;
		cout << "Q,q = Regina - se deplaseaza oricate spatii pe linie, coloana, diagonala" << endl;
		cout << "N,n = Nebun - se deplaseaza pe diagonala" << endl;
		cout << "C,c = Cal - se deplaseaza in forma de L" << endl;
		cout << "T,t = Tura - se deplaseaza pe linie/coloana" << endl;
		cout << "P,p = Pion se deplaseaza inainte cate un spatiu"<< endl << endl<< endl;
		cout << "**Pentru informatii aditionale privind scrierea mutarilor: apasati din nou 1," << endl;
		cout <<"       respectiv orice alta tasta pentru a incepe direct jocul** \1"<<endl;
		cout << "Raspuns: ";
		cin >> confirmare;
		if (confirmare == "1") {
			cout << "-----------------------------------------------------" << endl;
			cout << "Pionul de pe randul 1 este situat initial la coordonatele (1,1)." << endl;
			cout << "Pentru a-l muta un patrat inainte, pionul va ajunge in coordonatele (1,2)" << endl;
			cout << "Astfel, trebuie scris 1112." << endl;
			cout << "Sper ca a fost util \1" << endl;
			cout << "Acum puteti incepe jocul apasand orice tasta aici: ";
		}
		cin >> confirmare;
	}

	while (jocnou==true) {
		t.setTabla();
		while (t.incepeJocul());
		cout << "Vrei sa te joci din nou? Apasa 1 pentru un nou meci \1";
		cin >> confirmare;
		if (confirmare != "0")
			jocnou = false;
		else cout << "Sper ca ti-a placut! \1 ";
	}
	return 0;
}
