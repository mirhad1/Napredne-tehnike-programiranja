#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>

//Dinamicka alokacija memorije, enumeracije, strukture, funkcije, uutp
//ifstream == cin
//ofstream == cout

using namespace std;

//Enumeracija za vrstu sporta
enum Sport {
	fudbal = 1, kosarka = 2, tenis = 3, rukomet = 4
};

//Enumeracija za stanje opreme
enum Stanje {
	novo = 1, koristeno = 2
};

//Struktura za artikle opreme
struct Oprema {
	string naziv;
	int id;
	float cijena;
	int kvantitet;
	Sport vrstaSporta;
	Stanje stanjeOpreme;
};

//Struktura za izvjestaj koji se podnosi za opremu
struct Izvjestaj {
	char opis[255];
	string imeOsobe;
};

//Globalni niz za pracenje datoteke u kojoj su pohranjeni artikli
const int maxBrojStavki = 200;	//Maksimalni broj artikala
Oprema* oprema = new Oprema[maxBrojStavki];	//Niz u koje ce se artikli spremiti
int brojStavki = 0;	//Brojac koji prati koliko je arikala ucitano u niz	

//Funkcija koja iz text fajla "oprema.txt" povlaci podatke o artiklima i ucitava ih u globalni niz "oprema"
void ucitavanjeOpreme() {
	ifstream ucitaj;
	ucitaj.open("oprema.txt");
	int vrstaSporta, stanje; //proizvoljna dva integera, koji nam trebaju za povlacenje enumeracija iz text fajla
	while(ucitaj >> oprema[brojStavki].id >> oprema[brojStavki].naziv >> oprema[brojStavki].cijena >> oprema[brojStavki].kvantitet >> vrstaSporta >> stanje) {
		oprema[brojStavki].vrstaSporta = (Sport)vrstaSporta;
		oprema[brojStavki].stanjeOpreme = (Stanje)stanje;
		brojStavki++;
	}
	ucitaj.close();
}

//Funkcija koja ispisuje kratki meni u kojem se nude vrste sporta za opremu koja se unosi u bazu
int odabirVrsteSporta() {
	int vrsta;
	do {
		cout << "Odaberite vrstu sporta: \n";
		cout << "1. Fudbal\n";
		cout << "2. Kosarka\n";
		cout << "3. Tenis\n";
		cout << "4. Rukomet\n\n";
		cout << "Vrsta: "; cin >> vrsta;
		if(vrsta < 1 || vrsta > 4) {
			cout << "Error: Unesite jednu od ponudjenih kategorija \n";
		}
	} while(vrsta < 1 || vrsta > 4);
	return vrsta;
}

//Funkcija koja ispisuje kratki meni u kojem se nudi stanje opreme koja se unosi u bazu
int odabirStanja() {
	int stanje;
	do {
		cout << "Odaberite vrstu sporta: \n";
		cout << "1. Novo\n";
		cout << "2. Koristeno\n\n";
		cout << "Vrsta: "; cin >> stanje;
	} while(stanje < 1 || stanje > 2);
	return stanje;
}

//Niz float vrijednosti od 10 clanova: to znaci da taj niz ima 10 clanova
//Rekurzija krene od 10. clana, pa onda unutar sebe pozove ponovo samu sebe, ali sa brojacem npr. 9
//Rekurzivna funkcija koja racuna ukupnu vrijednost opreme pohranjene u bazi
float vrijednostOpreme(float iznosi[], int brojac) {
		if(brojac == 0) {
			return 0;
		} else {
			return iznosi[brojac-1] + vrijednostOpreme(iznosi, brojac-1);		
	}
}

//Funkcija za unos novog artikla
void unosArtikla() {
	system("cls");
		cout << "::UNOS NOVOG ARTIKLA::\n\n";
		
		//Odabir vrste sporta
		int vrsta = odabirVrsteSporta();
		oprema[brojStavki].vrstaSporta = (Sport)vrsta;
		
		//Odabir stanja opreme
		int stanje = odabirStanja();
		oprema[brojStavki].stanjeOpreme = (Stanje)stanje;
		
		//Unos naziva opreme
		cout << "Unesite naziv opreme: ";
		cin.ignore();
		getline(cin, oprema[brojStavki].naziv);
		
		//Unos ID-a artikla
		if(brojStavki == 0) {
			cout << "Unesite ID: ";
			cin >> oprema[brojStavki].id;
		} else {
			do {
				bool ispravno = false;
				do {
					cout << "Unesite ID: ";
					cin >> oprema[brojStavki].id;
					for(int i=0; i<brojStavki; i++) {
						if(oprema[brojStavki].id == oprema[i].id) {
							cout << "Error: Vec postoji artikal sa tim ID-em!\n";
							ispravno = false;
							break;
						} else ispravno=true;	
					}	
				} while(ispravno==false);
				break;
			} while(1);
		}
		
		//Unos cijene i kvantiteta artikla
		cout << "Unesite kvantitet artikla: "; cin >> oprema[brojStavki].kvantitet;
		cout << "Unesite cijenu artikla: "; cin >> oprema[brojStavki].cijena;
		
		//Dodavanje artikla u text fajl
		//ios::app - ios::append
		//ios::trunc - brise sve sto postoji u datoteci, pise novo
		ofstream upisiArtikal("oprema.txt", ios::app);
		upisiArtikal << oprema[brojStavki].id << " ";
		upisiArtikal << oprema[brojStavki].naziv << " ";
		upisiArtikal << oprema[brojStavki].cijena << " ";
		upisiArtikal << oprema[brojStavki].kvantitet << " ";
		upisiArtikal << oprema[brojStavki].vrstaSporta << " ";
		upisiArtikal << oprema[brojStavki].stanjeOpreme << endl;
		upisiArtikal.close();
		brojStavki++;
}

//Funkcija za brisanje artikla prema njegovom ID-u
void brisanjeArtikla() {
	cout << endl;
	
	//Ispis svih dostupnih artikala
	for(int i=0; i<brojStavki; i++) {
		string vrsta;
		if(oprema[i].vrstaSporta == 1) {
			vrsta = "Fudbal";
		} else if(oprema[i].vrstaSporta == 2) {
			vrsta = "Kosarka";
		} else if(oprema[i].vrstaSporta == 3) {
			vrsta = "Tenis";
		} else if(oprema[i].vrstaSporta == 4) {
			vrsta = "Rukomet";
		};
		cout << setw(5) << left << oprema[i].id << setw(15) << left << oprema[i].naziv << setw(15) << left << oprema[i].cijena << setw(15) << left 
		<< oprema[i].kvantitet << setw(15) << left << vrsta << endl;
	}
	
	//Unos ID-a artikla koji se zeli izbrisati
	int id;
	cout << "\nUnesite ID artikla koji zelite izbrisati: "; cin >> id;
	
	//Provjera postojanja unesenog ID-a (artikla)
	int i = 0;
	bool postoji = false;
	for (int i=0; i<brojStavki; i++) {
		if (oprema[i].id == id) {
			postoji = true;
			break;
		}
		postoji = false;
	}
	
	//Ukoliko artikal postoji, izbrisat ce se, te ce se clanovi globalnog niza "oprema" pomjerati za jedno mjesto kako bi popunili "supljinu"
	if(postoji) {
		for(i=0; i<brojStavki; i++) {
			if (oprema[i].id == id) {
				break; 
			}
		}
   		if (i < brojStavki) { 
     		brojStavki--;
     		for (int j=i; j<brojStavki; j++) {
     			oprema[j] = oprema[j+1]; 
			}
   		}
   		cout << "Artikal sa ID-em " << id << " uspjesno izbrisan! \n";
   		
   		//Novonastali niz se prepisuje u datoteku "oprema.txt"
		ofstream upisiArtikal("oprema.txt", ios::trunc);
		for(int i=0; i<brojStavki; i++) {
			upisiArtikal << oprema[i].id << " ";
			upisiArtikal << oprema[i].naziv << " ";
			upisiArtikal << oprema[i].cijena << " ";
			upisiArtikal << oprema[i].kvantitet << " ";
			upisiArtikal << oprema[i].vrstaSporta << " ";
			upisiArtikal << oprema[i].stanjeOpreme << endl;	
		}	
		upisiArtikal.close();	
	} else {
		//Ako uneseni ID ne pripada nijednom od artikala u bazi, ispisuje se error
		cout << "Artikal sa unesenim ID-em ne postoji!\n";	
	}
}

//Glavni meni koji se prikazuje prilikom pokretanja programa
int meni() {
	int odabirPanela;
	do {
		cout << "\t::MENI::\n\n";
		cout << "1. Pregled artikala" << endl;
		cout << "2. Unos novog artikla" << endl;
		cout << "3. Brisanje artikla" << endl;
		cout << "4. Vrijednost artikala" << endl;
		cout << "5. Izvjestaj stanja artikala" << endl;
		cout << "6. Napusti" << endl;
		cout << "\nUnesite izbor: ";
		cin >> odabirPanela;
	} while (odabirPanela<1 || odabirPanela>6);
	return odabirPanela;
}

//Podmeni za pregled artikala, koji nudi vise opcija
int podmeni() {
	int odabirPanela;
	do {
		cout << "::PODMENI ZA PREGLED ARTIKALA::\n\n";
		cout << "1. Pregled svih artikala" << endl;
		cout << "2. Pregled artikala po sportovima" << endl;
		cout << "3. Napusti" << endl;
		cout << "\nUnesite izbor: ";
		cin >> odabirPanela;
	} while (odabirPanela<1 || odabirPanela>3);
	return odabirPanela;
}

//Podmeni za pregled artikala po sportovima
int vrsteSportova() {
	int odabirPanela;
	do {
		cout << "::ODABIR SPORTA::\n\n";
		cout << "1. Fudbal" << endl;
		cout << "2. Kosarka" << endl;
		cout << "3. Tenis" << endl;
		cout << "4. Rukomet" << endl;
		cout << "\nUnesite izbor: ";
		cin >> odabirPanela;
	} while (odabirPanela<1 || odabirPanela>4);
	return odabirPanela;
}

//Funkcija za pravljenje izvjestaja
void napraviIzvjestaj() {
	
	Izvjestaj noviIzvjestaj;	//Definisanje novog izvjestaja na osnovu strukture "Izvjestaj"
	
	//Unos nekih osnovnih informacija koje ce se ispisati na izvjestaju
	cout << "::NOVI IZVJESTAJ STANJA ARTIKALA::\n\n";
	cout << endl;
	cin.ignore();
	cout << "Unesite Vase ime (operator): ";
	getline(cin, noviIzvjestaj.imeOsobe);
	cout << "Unesite opis izvjestaja (namjena): ";
	cin.getline(noviIzvjestaj.opis, 255);
	cout << "Izvjestaj uspjesno ispisan!\n";
	
	//Ispis izvjestaja u datoteku "Izvjestaj-Stanje Opreme.txt"
	ofstream ispisiIzvjestaj;
	ispisiIzvjestaj.open("Izvjestaj-Stanje Opreme.txt", ios::app);
	ispisiIzvjestaj << "----- IZVJESTAJ O STANJU OPREME -----" << "\n\n";
	ispisiIzvjestaj << "Namjena ovog izvjestaja: " << noviIzvjestaj.opis << "\n\n\n";
	ispisiIzvjestaj << "Popis informacija o artiklima za vrijeme izvjestaja: \n";
	ispisiIzvjestaj << "------------------------------------------------------------------\n";
	
	//Ispis svih artikala iz baze u izvjestaj
	ispisiIzvjestaj << setw(5) << left << "ID" << setw(15) << left << "Naziv" << setw(15) << left << "Cijena" << setw(15) << left << "Kvantitet" 
	<< setw(15) << left << "Vrsta sporta" << endl << endl; 
		for(int i=0; i<brojStavki; i++) {
			string vrsta;
			if(oprema[i].vrstaSporta == 1) {
				vrsta = "Fudbal";
			} else if(oprema[i].vrstaSporta == 2) {
				vrsta = "Kosarka";
			} else if(oprema[i].vrstaSporta == 3) {
				vrsta = "Tenis";
			} else if(oprema[i].vrstaSporta == 4) {
				vrsta = "Rukomet";
			};
			ispisiIzvjestaj << setw(5) << left << oprema[i].id << setw(15) << left << oprema[i].naziv << setw(15) << left << oprema[i].cijena << setw(15) << left 
			<< oprema[i].kvantitet << setw(15) << left << vrsta << endl;
		}
	ispisiIzvjestaj << "\n\n\n";
	
	//Ispis ukupne vrijednosti artikala u izvjestaj
	float iznosi[brojStavki];
	int brojacIznosa = 0;
	for(int i=0; i<brojStavki; i++) {
		iznosi[brojacIznosa] = oprema[i].cijena;
		brojacIznosa++;
	}
	ispisiIzvjestaj << "Trenutna vrijednost opreme u skladistu iznosi: " << vrijednostOpreme(iznosi, brojStavki) << "\n\n";
	ispisiIzvjestaj << "\t\t\t\tIzvjestaj podnio: " << noviIzvjestaj.imeOsobe << endl;
	ispisiIzvjestaj.close();
}

int main() {
	
	//Definisanje niza cijena artikala i brojaca za racunanje vrijednosti artikala
	float iznosi[brojStavki];
	int brojacIznosa = 0;
	
	//Povlacenje svih artikala iz baze u globalni niz uz pomoc funkcije ucitavanjeOpreme()
	ucitavanjeOpreme();
	
	//Pokretanje glavnog menija kroz do while petlju
		do {
			int ucitajMeni = meni();
			
			//Switch statement za opcije u glavnom meniju
			switch(ucitajMeni){
			//Opcija 1 u glavnom meniju: Pregled artikala
			case 1:
				system("cls");
				//Pokrece se podmeni koji nudi dvije opcije: Pregled svih artikala i pregled artikala prema sportovima
				do {
					int izbor;
					izbor = podmeni();
					if(izbor == 3) {
						//Ukoliko se odabere 3. opcija u podmeniju za pregled artikala, podmeni ce se zatvoriti, tj. vratit ce se na glavni meni
						system("cls");
						break;
					} else if(izbor == 1) {
						//Ukoliko se odabere 1. opcija u podmeniju za pregled artikala, izlistat ce se svih artikli iz baze
						system("cls");
						cout << setw(5) << left << "ID" << setw(15) << left << "Naziv" << setw(15) << left << "Cijena" << setw(15) << left << "Kvantitet" 
						<< setw(15) << left << "Vrsta sporta" << setw(15) << left << "Stanje artikla" << endl << endl; 
						for(int i=0; i<brojStavki; i++) {
							string vrsta;
							if(oprema[i].vrstaSporta == 1) {
								vrsta = "Fudbal";
							} else if(oprema[i].vrstaSporta == 2) {
								vrsta = "Kosarka";
							} else if(oprema[i].vrstaSporta == 3) {
								vrsta = "Tenis";
							} else if(oprema[i].vrstaSporta == 4) {
								vrsta = "Rukomet";
							};
							string stanje;
							if(oprema[i].stanjeOpreme == 1) {
								stanje = "Novo";
							} else if(oprema[i].stanjeOpreme == 2) {
								stanje = "Koristeno";
							}
							cout << setw(5) << left << oprema[i].id << setw(15) << left << oprema[i].naziv << setw(15) << left << oprema[i].cijena << setw(15) << left 
							<< oprema[i].kvantitet << setw(15) << left << vrsta << setw(15) << left << stanje << endl;
						}
						system("PAUSE");
						system("cls");
					} else if(izbor == 2) {
						//Ukoliko se odabere 2. opcija u podmeniju za pregled artikala, otvorit ce se podmeni za odabir vrste sporta, a zatim ce se izlistati svi artikli vezani za taj sport
						system("cls");
						int vrstaSporta = vrsteSportova();
						
						//Provjera da li postoji bar jedan artikal vezan za odabrani sport
						bool postoji = false;
						for (int i=0; i<brojStavki; i++) {
							if (oprema[i].vrstaSporta == (Sport)vrstaSporta) {
								postoji = true;
								break;
							}
							postoji = false;
						}
						
						//Ukoliko postoji, ispisat ce se
						if(postoji) {
							cout << endl;
							cout << setw(5) << left << "ID" << setw(15) << left << "Naziv" << setw(15) << left << "Cijena" << setw(15) << left << "Kvantitet" << endl; 
							for(int i=0; i<brojStavki; i++) {
								if(oprema[i].vrstaSporta == vrstaSporta) {
									cout << setw(5) << left << oprema[i].id << setw(15) << left << oprema[i].naziv << setw(15) << left << oprema[i].cijena << setw(15) << left 
									<< oprema[i].kvantitet << endl;
								}
							}
						} else {
							//U suprotnom, ispisuje se error
							cout << "Ne postoji nijedan artikal u odabranoj kategoriji!\n";
						}
						system("PAUSE");
						system("cls");
					}	
				} while(1);
				break;
			case 2: 
				//Opcija 2 u glavnom meniju: Unos novog artikla
				system("cls");
				//Poziva se funkcija za unos novog artikla
				unosArtikla();
				system("PAUSE");
				system("cls");
				break;
			case 3:
				//Opcija 3 u glavnom meniju: Brisanje artikla
				system("cls");
				//Poziva se funkcija za brisanje artikla
				brisanjeArtikla();
				system("PAUSE");
				system("cls");
				break;
			case 4: 
				//Opcija 4 u glavnom meniju: Ispis trenutne vrijednosti opreme u bazi
				system("cls");
				//Kroz for petlju dodajemo iznos svakog artikla posebno u niz "iznosi", koji smo definisali na pocetku int main() funkcije
				for(int i=0; i<brojStavki; i++) {
					iznosi[brojacIznosa] = oprema[i].cijena;
					brojacIznosa++;
				}
				
				//Ispis trenutne vrijednosti opreme uz poziv rekurzivne funkcije "vrijednostOpreme()"
				cout << "Trenutna vrijednost opreme u skladistu iznosi: " << vrijednostOpreme(iznosi, brojStavki) << endl;
				system("PAUSE");
				system("cls");
				break;
			case 5: 
				//Opcija 5 u glavnom meniju: Pravljenje izvjestaja za artikle
				system("cls");
				//Poziva se funkcija za pravljenje izvjestaja artikala
				napraviIzvjestaj();
				system("PAUSE");
				system("cls");
				break;
			case 6:
				//Opcija 6 u glavnom meniju: Zatvaranje glavnog menija, a ujedno i programa
				system("PAUSE");
				return 0;	
			}			
		} while(1);
	system("PAUSE");
	return 0;
};
