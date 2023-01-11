#include <iostream>
#include <fstream>
#include <map>

using namespace std;

//struktura wezla
struct Wezel{
    Wezel* lewy;
    Wezel* prawy;
    char znak;
    long ilosc;

    Wezel(char znak, long ilosc){
        lewy=nullptr;
        prawy=nullptr;

    }
};

void zbudujDrzewo(Wezel * & root){

}

//funckja kodujaca
void zmienTekst(){
    string linia;
    int dlugosc;
    int licznikZnakow[256]={0};
    ifstream plik("tekst.txt");

    if(!plik){
        cout<<"Blad danych"<<endl;
    }

    //przetworzenie kazdej linii tekstu
    while(getline(plik, linia)){
        dlugosc=linia.size();

        for(int i=0; i<dlugosc; i++){
            char litera = linia[i];
            licznikZnakow[(int)litera]++;
        }
    }

    //stworzenie mapy charow i ilosci ich wystapien
    map <char, int> m;

    for(int i=0; i<255; i++){
        if(licznikZnakow[i]>0){
            m[(char)i] = licznikZnakow[i];
        }
    }

    //sortowanie

    //zapis szyfrowania

    //zapis zaszyfrowanego pliku
}

//funkcja dekodujaca
void odczytajTekst(){

}

int main(){
    zmienTekst();
    odczytajTekst();
    return 0;
}
