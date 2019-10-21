#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void zapisanieDanychDoPliku(Adresat osoba) {
    fstream plik;
    // otwarcie pliku do zapisu i dolaczenie nowych danych
    plik.open("kontakty.txt", ios::out  |  ios::app); // pokieruj strumien danych z naszego programu do pliku
    // zapisanie danych do pliku
    if(plik.good() == true) {
        plik << osoba.id << "|";
        plik << osoba.imie << "|";
        plik << osoba.nazwisko << "|";
        plik << osoba.numerTelefonu << "|";
        plik << osoba.email << "|";
        plik << osoba.adres << "|";
        plik << endl;
        // zamkniecie pliku
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst) {
    if (!tekst.empty()) {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

void dodawanieOsoby(vector<Adresat> &adresaci) {
    system("cls");
    Adresat osoba;
    cout << "***DODAWANIE ADRESATA***" << endl << endl;
    cout << "Podaj dane: " << endl;
    cout << " - imie: " ;
    cin >> osoba.imie;
    osoba.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(osoba.imie);
    cout << " - nazwisko: ";
    cin >> osoba.nazwisko;
    osoba.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(osoba.nazwisko);
    cout << " - numer telefonu: ";
    cin.sync();  //oczyszczanie buforu
    getline(cin, osoba.numerTelefonu);
    cout << " - email: ";
    cin >> osoba.email;
    cout << " - adres: ";
    cin.sync();
    getline(cin, osoba.adres);
    cout << endl;
    if (adresaci.empty() == true) {
        osoba.id = 1;
    } else {
        osoba.id = adresaci.back().id + 1;
    }

    adresaci.push_back(osoba);
    zapisanieDanychDoPliku(osoba);
    cout << "Kontakt dodany!" << endl << endl;
    cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
    getch();
}

void wyswietlKontakt(vector<Adresat> adresaci, int i) {
    cout << "Numer ID: " << adresaci[i].id << endl;
    cout << adresaci[i].imie << " " << adresaci[i].nazwisko << endl;
    cout << "Telefon: " << adresaci[i].numerTelefonu << endl;
    cout << "Email: " << adresaci[i].email << endl;
    cout << "Adres: " << adresaci[i].adres << endl;
    cout << endl;
}

void znajdywaniePoImieniu(vector<Adresat> adresaci) {
    system("cls");
    string imie;
    cout << "***SZUKANIE ADRESATA***" << endl << endl;
    cout << "Podaj imie szukanej osoby: ";
    cin >> imie;
    imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imie);
    system("cls");
    cout << "***SZUKANIE ADRESATA***" << endl << endl;
    cout << "Wszystkie osoby o imieniu " << "' " << imie << " ':" << endl << endl;
    for(int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].imie == imie) {
            wyswietlKontakt(adresaci, i);
        }
    }
    cout << endl;
    cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
    getch();
}

void znajdywaniePoNazwisku(vector<Adresat> adresaci) {
    string nazwisko;
    system("cls");
    cout << "***SZUKANIE ADRESATA***" << endl << endl;
    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> nazwisko;
    nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwisko);
    system("cls");
    cout << "***SZUKANIE ADRESATA***" << endl << endl;
    cout << "Wszystkie osoby o nazwisku " << "' " << nazwisko << " ':" << endl << endl;
    for(int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].nazwisko == nazwisko) {
            wyswietlKontakt(adresaci, i);
        }
    }
    cout << endl;
    cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
    getch();
}

void wyswietlanieListyKontaktow(vector<Adresat> adresaci) {
    system("cls");
    if(!adresaci.empty()) {
        cout << "Lista zapisanych kontaktow" << endl << endl << "***" << endl << endl;
        for(int i = 0; i < adresaci.size(); i++) {
            wyswietlKontakt(adresaci, i);
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
    getch();
}

vector <string> wydzielenieWyrazow(string linia) {
    string bufor;
    char separator = '|';
    vector <string> wektorCzasowy;
    int ostatniaPozycja = 0;
    for( int i = 0; i < linia.length(); i++ ) {
        if( linia[i] == separator ) {
            bufor = linia.substr(ostatniaPozycja, i - ostatniaPozycja);
            wektorCzasowy.push_back(bufor);
            ostatniaPozycja = i + 1;
        }
    }
    return wektorCzasowy;
}

void wczytywanieDanychZPliku(vector<Adresat> &adresaci) {
    string linia;
    vector<string> wydzieloneDane;
    Adresat osoba;
    int numerLinii = 1;
    fstream plik;
    plik.open("kontakty.txt", ios::in);
    if(plik.good() == true) {
        while(getline(plik,linia)) {
            wydzieloneDane = wydzielenieWyrazow(linia);
            osoba.id = atoi(wydzieloneDane[0].c_str());
            osoba.imie = wydzieloneDane[1];
            osoba.nazwisko = wydzieloneDane[2];
            osoba.numerTelefonu = wydzieloneDane[3];
            osoba.email = wydzieloneDane[4];
            osoba.adres = wydzieloneDane[5];
            adresaci.push_back(osoba);
        }
        plik.close();
    }
}

bool sprawdzCzyUsunietoAdresata(vector<Adresat> &adresaci, int numer) {
    char znak;
    for(int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].id == numer) {
            cout << "Jezeli napewno chcesz usunac kontakt '" << adresaci[i].imie << " " << adresaci[i].nazwisko << "' wcisnij 't', w przeciwnym razie wcisnij klawisz 'f'." << endl;
            cout << "Twoj wybor: ";
            cin >> znak;
            cout << endl;
            if(znak == 't') {
                cout << "Adresat: '" << adresaci[i].imie << " " << adresaci[i].nazwisko << "' zostal usuniety z listy kontaktow." << endl;
                adresaci.erase(adresaci.begin()+ i);
            } else if (znak == 'f') {
                cout << "Nie usunieto kontaktu." << endl;
            }
            return true;
        }
    }
}

void usuwanieAdresata(vector <Adresat> &adresaci) {
    system("cls");
    int numer;
    cout << "***USUWANIE ADRESATA***" << endl << endl;
    cout << "Podaj numer wpisu(ID) adresata, ktorego chcesz usunac: ";
    cin >> numer;
    cout << endl;
    if (sprawdzCzyUsunietoAdresata(adresaci, numer) != true ) {
        cout << "Ups... nie ma wpisu o takim numerze." << endl;
    }
    cout << endl << endl;
    cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
    getch();
}

void edytowanieAdresata(vector <Adresat> &adresaci) {
    system("cls");
    cout << "***EDYTOWANIE ADRESATA***" << endl<<endl;
    cout << "Podaj numer wpisu(ID) adresata, ktorego chcesz edytowac: ";
    int numer;
    cin >> numer;
    while(numer > adresaci.size()) {
        cout << endl << "Nie ma osoby o takim numerze. Wprowadz go ponownie: ";
        cin >> numer;
    }
    cout << endl << "Dane kontaktowe: " << endl;
    wyswietlKontakt(adresaci,numer-1);
    char wybor;
    string imie, nazwisko, numerTelefonu, email, adres;
    cout << "Wskaz informacje, ktore chcesz edytowac: " << endl;
    cout << "1. Imie." << endl;
    cout << "2. Nazwisko." << endl;
    cout << "3. Numer telefonu." << endl;
    cout << "4. Email." << endl;
    cout << "5. Adres." << endl;
    cout << "Aby zrezygnowac z edycji nacisnij 6." << endl << endl;
    cout << "Twoj wybor: ";
    cin >> wybor;
    system("cls");
    cout << "***EDYTOWANIE ADRESATA***" << endl<<endl;
    switch(wybor) {
        case '1': {
            cout << "Wpisz nowe imie: ";
            cin >> imie;
            imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imie);
            for(int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == numer) {
                    adresaci[numer-1].imie = imie;
                }
            }
            cout << endl << "Dane zostaly zmienione." << endl << endl;
            cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
            getch();
            break;
        }
        case '2': {
            cout << "Wpisz nowe nazwisko: ";
            cin >> nazwisko;
            nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwisko);
            for(int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == numer) {
                    adresaci[numer-1].nazwisko = nazwisko;
                }
            }
            cout << endl << "Dane zostaly zmienione." << endl << endl;
            cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
            getch();
            break;
        }
        case '3': {
            cout << "Wpisz nowy numer telefonu: ";
            cin >> numerTelefonu;
            for(int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == numer) {
                    adresaci[numer-1].numerTelefonu = numerTelefonu;
                }
            }
            cout << endl << "Dane zostaly zmienione." << endl << endl;
            cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
            getch();
            break;
        }
        case '4': {
            cout << "Wpisz nowy email: ";
            cin >> email;
            for(int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == numer) {
                    adresaci[numer-1].email = email;
                }
            }
            cout << endl << "Dane zostaly zmienione." << endl << endl;
            cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
            getch();
            break;
        }
        case '5': {
            cout << "Wpisz nowy adres: ";
            cin >> adres;
            for(int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == numer) {
                    adresaci[numer-1].adres = adres;
                }
            }
            cout << endl << "Dane zostaly zmienione." << endl << endl;
            cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
            getch();
            break;
        }
        case '6': {
            break;
        }
    }
}

void wyswietlMenuProgramu() {
    system("cls");
    cout << "KSIAZKA ADRESOWA" << endl << endl << "***" << endl << endl;
    cout << "Wybierz opcje: " << endl << endl;
    cout << "1. Dodaj osobe." << endl;
    cout << "2. Znajdz osobe po imieniu." << endl;
    cout << "3. Znajdz osobe po nazwisku." << endl;
    cout << "4. Wyswietl liste kontaktow." << endl;
    cout << "5. Usun adresata." << endl;
    cout << "6. Edytuj adresata." << endl;
    cout << "9. Zamknij program." << endl << endl;
    cout << "Twoj wybor: ";
}

void nadpisanieDanychWPliku(vector<Adresat> &adresaci) {
    fstream plik;
    // otwarcie pliku do zapisu i zapisanie nowych danych
    plik.open("kontakty.txt", ios::out); // pokieruj strumieñ danych z naszego programu do pliku
    // zapisanie danych do pliku
    if(plik.good() == true) {
        for(int i = 0; i < adresaci.size(); i++) {
            plik << adresaci[i].id << "|";
            plik << adresaci[i].imie << "|";
            plik << adresaci[i].nazwisko << "|";
            plik << adresaci[i].numerTelefonu << "|";
            plik << adresaci[i].email << "|";
            plik << adresaci[i].adres << "|";
            plik << endl;
        }
        // zamkniecie pliku
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

int main() {
    vector<Adresat> adresaci;
    wczytywanieDanychZPliku(adresaci);
    char wyborOpcji;
    do {
        wyswietlMenuProgramu();
        cin >> wyborOpcji;
        switch(wyborOpcji) {
            case '1': {
                dodawanieOsoby(adresaci);
                break;
            }
            case '2': {
                znajdywaniePoImieniu(adresaci);
                break;
            }
            case '3': {
                znajdywaniePoNazwisku(adresaci);
                break;
            }
            case '4': {
                wyswietlanieListyKontaktow(adresaci);
                break;
            }
            case '5': {
                usuwanieAdresata(adresaci);
                nadpisanieDanychWPliku(adresaci);
                break;
            }
            case '6': {
                edytowanieAdresata(adresaci);
                nadpisanieDanychWPliku(adresaci);
                break;
            }
            case '9': {
                exit(0);
            }
            default: {
                cout <<  endl << "Nie istnieje taka opcja! Wcisnij dowolny klawisz, aby powtorzyc wybor.";
                getch();
            }
        }
    } while (wyborOpcji != 9);
    return 0;
}

