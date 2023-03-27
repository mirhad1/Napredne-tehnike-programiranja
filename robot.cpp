#include <iostream>
#include <cmath>
using namespace std;
const double PI  = 3.141592653589793238463;//Deklaracija konstante pi
class Robot {//Deklaracija klase Robot
    private://Koristimo ovdje private da bi samo mi mogli da vidimo sta se u private nalazi
    
    double x;//Deklaracija varijable x tipa double
    double y;//Deklaracija varijable y tipa double
    double ugao;//Deklaracija varijable ugao tipa double
    
    public:
    void Postavi(double x, double y, double ugao) {//Deklaracija funkcije postavi tipa void sa parametrima x y i ugao
        Robot::x = x;//Deklaracija konstruktora
        Robot::y = y;//Deklaracija konstruktora
        Robot::ugao = ugao;//Deklaracija konstruktora
    }
    
    double DajPozicijuX() const {
        return x;//Vracanje x
    }
    
    double DajPozicijuY() const {
        return y;//Vracanje y
    }
    
    double DajOrjentaciju() const {
        return ugao;//Vracanje zgla
    }
    
    void Ispisi() const {
        std::cout << "Robot se nalazi na poziciji (" << x << "," << y << ") i gleda pod uglom " << ugao << " stepeni u odnosu na x osu."<<endl;
    }
    
    void IdiNaprijed(double pomak){
  	x = x + (pomak * cos(ugao * PI / 180));//Proracun koordinate x za funkciju idi naprijed
	y = y + (pomak * sin(ugao * PI / 180));//Proracun koordinate y za funkciju idi naprijed
    	
	}
    void IdiNazad(double pomak){
    x = x + (-pomak * cos(ugao * PI / 180));//Proracun koordinate x za funkciju idi nazad
	y = y + (-pomak * sin(ugao * PI / 180));//Proracun koordinate y za funkciju idi nazad	
	}
    void OkreniSeNalijevo(double _ugao){
    ugao=_ugao;	
	}
    void OkreniSeNadesno(double _ugao){
    ugao=-_ugao;
	}
};

int main()
{
    Robot robot;
    int opcija;//Deklaracija varijable opcija tipa int
    while(true){//Sve dok je neki uslov zadovoljen trazimo od korisnika da izabere opciju 
	
    cout <<"1.Idi Naprijed"<<endl;
    cout << "2.Idi Nazad"<<endl;
    cout << "3.Okreni se nalijevo "<<endl;
    cout << "4.Okreni se nadesno"<<endl;
    cout << "5.Postavi"<<endl;
    cout <<"Molimo vas da unesete jednu od opcija:"<<endl;
    cin >> opcija;
    if (opcija == 1){//Provjera je li izabrana opcija 1
    	double pomak;//Deklaracija varijable pomak tipa double
    	cout <<"Unesite pomak:"<<endl;//Unos pomka
    	cin >> pomak;
    	robot.IdiNaprijed(pomak);//Poziv funkcije IdiNaprije
		
		
	}
    if (opcija == 2){//Provjera je li izabrana opcija 2
    	double pomak;//Deklaracija varijable pomak tipa double
    	cout <<"Unesite pomak:"<<endl;
    	cin >> pomak;
    	robot.IdiNazad(pomak);//Poziv funkcije IdiNazad
    	
	}
	
	if (opcija==3){//Provjera je li izabrana opcija 3
		double ugao;//Deklaracija varijable ugao tipa double
		cout <<"Unesite ugao:"<<endl;
		cin >>ugao;
		robot.OkreniSeNalijevo(ugao);//Poziv OkreniSeNalijevo
		
	}
	
	if (opcija==4){//Provjera je li izabrana opcija 4
		double ugao;//Deklaracija varijable ugao tipa double
		cout <<"Unesite ugao:"<<endl;//Unos ugla
		cin >>ugao;//Ispis ugla
		robot.OkreniSeNadesno(ugao);//Poziv funkcije OkreniSeNadesno
		
	}
	if (opcija==5){//Provjera je li izabrana opcija5
		double ugao,x,y;//Deklaracija varijabli x y i ugao tipa double
		cout <<"Unesite ugao:"<<endl;//Unos ugla
		cin >>ugao;//Ispis ugla
		cout <<"Unesite x:"<<endl;//Unos x
			cin >>x;//Ispis x
		cout <<"Unesite y:"<<endl;//Unos y
		cin >>y;//Ispis y
		
		robot.Postavi(x,y,ugao);//Poziv funkcije postavi
		
		}
	
	robot.Ispisi();//Poziv funkcije ispisi
	
	}
    
	system ("pause>0");
    return 0;
}
