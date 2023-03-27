#include <iostream>
using namespace std;


struct Roba{ // Deklaracija strukture 
	char naziv[50];// Deklaracija char niza koji prima 50 karaktera
	int br_skladista; // Deklaracija varijable za unos broja skladista
	int kolicina; // Deklaracija varijable za unos trenutne kolicine robe
	int min_kolicina; // Deklaracija varijable  za unos minimalne kolicine robe
	double cijena; // Deklaracija varijable za unos cijene robe
	char ime_dobavljaca[50]; // Deklaracija char niza koji prima 50 karaktera
};

int main (){
	setlocale(LC_ALL,"");
	int n; //Deklaracija varijable za unos robe
	
	cout << "Unesite za koliko robe zelite unijeti podatke: ";
	cin >> n; // Unos broj robe
	cin.ignore();
	cout << endl;
	Roba niz[n]; // Deklaracija niza za unos podataka
	cout << "PODACI O ROBI\n"; // ispis teksta
	cout << endl; // novi red
	for(int i=0; i<n; i++){ // For petlja za unos podataka
		cout << "Unesite naziv robe: ";
		cin.getline(niz[i].naziv,50); // Unos naziva robe
		cout << "Unesite broj skladista u kojem se nalazi roba: ";
		cin >> niz[i].br_skladista; // Unos broja skladista
		cout << "Unesite minimalnu kolicinu roba koja moze da bude u skladistu: ";
		cin >> niz[i].min_kolicina;// Unos minimalne kolicine
		cout << "Unesite trenutnu kolicinu robe: ";
		cin >> niz[i].kolicina; // Unos trenutne kolicine robe u skladistu
		cin.ignore(); // ignorisanje linije
		if(niz[i].kolicina<=niz[i].min_kolicina){ // Ukoliko je trenutna kolicina robe manja ili jednaka onoj u skladistu unosi se ime dobavljaca
			cout << "Kolicina robe je manja od dozvoljene.\n"; // Ispis poruke ako je uvijet tacan
			cout << "Unesite dobavljaca: "; // ispis teksta
			cin.getline(niz[i].ime_dobavljaca,50); // Unos dobavljaca
		}
		cout << "Unesite cijenu robe: ";
		cin >> niz[i].cijena; // Unos cijene robe
		cin.ignore(); // ignorisanje linije
		cout << endl; // novi red
	}
	cout << "----------------------------------------------------\n"; // ispist teksta
	cout << "I Z V J E S T A J" << endl; // ispis teksta
	cout << endl; // novi red
	for(int i=0; i<n; i++){ // Klasicna for petlja za ispis podataka
		cout << "Naziv robe: " << niz[i].naziv << endl; // ispis naziva robe
		cout << "Broj skladista u kojem se nalazi roba: " << niz[i].br_skladista << endl; // ispis broja skladista
		cout << "Minimalna kolicina: " << niz[i].min_kolicina << endl; // ispis minimalne kolicine
		cout << "Trenutna kolicina: " << niz[i].kolicina << endl; // ispis kolicine
			if(niz[i].kolicina<=niz[i].min_kolicina){ // uslov da li postoji dovoljno robe
				cout << "Ime dobavljaca: " << niz[i].ime_dobavljaca << endl; // ispis dobavljaca u slucaju da nema dovoljne kolicine robe
			}
			
		cout << "Cijena robe: " << niz[i].cijena << " KM" << endl; // ispis cijene robe
		cout << endl; // novi red
	}
	

return 0; //vracanje nule
}


