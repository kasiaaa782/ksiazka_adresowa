#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


struct Uzytkownik {
    int idUzytkownika = 0;
    string nazwa = "", haslo = "";
};

struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void zapisanieUzytkownikowDoPliku(Uzytkownik osoba) {
    fstream plik;
    // otwarcie pliku do zapisu i dolaczenie nowych danych
    plik.open("listaUzytkownikow.txt", ios::out  |  ios::app); // pokieruj strumien danych z naszego programu do pliku
    // zapisanie danych do pliku
    if(plik.good() == true) {
        plik << osoba.idUzytkownika << "|";
        plik << osoba.nazwa << "|";
        plik << osoba.haslo << "|" << endl;
        // zamkniecie pliku
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
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

void wczytywanieUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy) {
    string linia;
    vector<string> wydzieloneDane;
    Uzytkownik osoba;
    int numerLinii = 1;
    fstream plik;
    plik.open("listaUzytkownikow.txt", ios::in);
    if(plik.good() == true) {
        while(getline(plik,linia)) {
            wydzieloneDane = wydzielenieWyrazow(linia);
            osoba.idUzytkownika = atoi(wydzieloneDane[0].c_str());
            osoba.nazwa = wydzieloneDane[1];
            osoba.haslo = wydzieloneDane[2];
            uzytkownicy.push_back(osoba);
        }
        plik.close();
    }
}

bool sprawdzCzyIstniejeTakiUzytkownik(vector<Uzytkownik> &uzytkownicy, string nazwa) {
    for(vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (itr -> nazwa == nazwa) {
            return true;
        }
    }
    return false;
}

void rejestracjaUzytkownika(vector<Uzytkownik> &uzytkownicy) {
    system("cls");
    cout << "***REJESTRACJA***" << endl << endl;
    Uzytkownik osoba;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> osoba.nazwa;
    cout << endl;
    while(sprawdzCzyIstniejeTakiUzytkownik(uzytkownicy, osoba.nazwa) == true) {
        cout << "Taki uzytkownik istnieje, wpisz inna nazwe: ";
        cin >> osoba.nazwa;
    }
    system("cls");
    cout << "***REJESTRACJA***" << endl << endl;
    cout << "Podaj nazwe uzytkownika: " << osoba.nazwa << endl << endl;
    cout << "Podaj haslo: ";
    cin >> osoba.haslo;
    if (uzytkownicy.empty() == true) {
        osoba.idUzytkownika = 1;
    } else {
        osoba.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    }
    uzytkownicy.push_back(osoba);
    zapisanieUzytkownikowDoPliku(osoba);
    cout << endl << "Konto zalozone pomyslnie." << endl << endl;
    cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
    getch();
}

void wyswietlOpcjeProgramu() {
    system("cls");
    cout << "***KSIAZKA ADRESOWA DLA KAZDEGO***" << endl << endl;
    cout << "Wybierz opcje: " << endl << endl;
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "3. Zamknij program." << endl << endl;
    cout << "Twoj wybor: ";
}

bool sprawdzCzyHasloJestPoprawne(vector<Uzytkownik> &uzytkownicy, string haslo) {
    for(vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (itr -> haslo == haslo) {
            return true;
        }
    }
    return false;
}

int wyciagnijID(vector<Uzytkownik> uzytkownicy, string nazwa) {
    for(int i = 0; i < uzytkownicy.size(); i++) {
        if(uzytkownicy[i].nazwa == nazwa) {
            return uzytkownicy[i].idUzytkownika;
        }
    }
}

Uzytkownik logowanieUzytkownika(vector<Uzytkownik> uzytkownicy) {
    Uzytkownik osoba, zmiennaPomocnicza;
    char znak;
    system("cls");
    cout << "***LOGOWANIE***" << endl << endl;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> osoba.nazwa;
    cout << endl;
    int i = 0;
    while(sprawdzCzyIstniejeTakiUzytkownik(uzytkownicy, osoba.nazwa) == false) {
        if(i > 2) {
            cout << "Nie udalo sie zalogowac." << endl << endl;
            cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
            getch();
            return zmiennaPomocnicza;
        }
        cout << "Nie ma uzytkownika o takiej nazwie. Sprobuj ponownie: ";
        cin >> osoba.nazwa;
        i++;
    }
    system("cls");
    cout << "***LOGOWANIE***" << endl << endl;
    cout << "Podaj nazwe uzytkownika: " << osoba.nazwa << endl;
    cout << "Podaj haslo: ";
    cin >> osoba.haslo;
    int j = 0;
    while(sprawdzCzyHasloJestPoprawne(uzytkownicy,osoba.haslo) == false) {
        if(j > 2) {
            cout << "Nie udalo sie zalogowac." << endl << endl;
            cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
            getch();
            return zmiennaPomocnicza;
        }
        cout << "Niepoprawne haslo. Sprobuj ponownie: ";
        cin >> osoba.haslo;
        j++;
    }
    cout << endl << "Udalo sie zalogowac. " << endl << endl;
    cout << "Wcisnij dowolny klawisz, aby przejsc do ksiazki adresowej.";
    getch();
    osoba.idUzytkownika = wyciagnijID(uzytkownicy, osoba.nazwa);
    return osoba;
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst) {
    if (!tekst.empty()) {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

void zapisanieDanychDoPliku(Adresat osoba, Uzytkownik zalogowany) {
    fstream plik;
    // otwarcie pliku do zapisu i dolaczenie nowych danych
    plik.open("Adresaci.txt", ios::out  |  ios::app); // pokieruj strumien danych z naszego programu do pliku
    // zapisanie danych do pliku
    if(plik.good() == true) {
        plik << osoba.id << "|";
        plik << zalogowany.idUzytkownika << "|";
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

void zapamietajHasloWPliku(vector<Uzytkownik> &uzytkownicy){
    fstream plik;
    // otwarcie pliku do zapisu i zapisanie nowych danych
    plik.open("listaUzytkownikow.txt", ios::out); // pokieruj strumieñ danych z naszego programu do pliku
    // zapisanie danych do pliku
    if(plik.good() == true) {
        for(int i = 0; i < uzytkownicy.size(); i++) {
            plik << uzytkownicy[i].idUzytkownika << "|";
            plik << uzytkownicy[i].nazwa << "|";
            plik << uzytkownicy[i].haslo << "|";
            plik << endl;
        }
        // zamkniecie pliku
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void zmianaHasla(vector<Uzytkownik> uzytkownicy, Uzytkownik zalogowany) {
    string haslo;
    cout << "***ZMIANA HASLA***" << endl << endl;
    cout << "Podaj nowe haslo: " ;
    cin >> haslo;
    for(int i = 0; i < uzytkownicy.size(); i++) {
        if(uzytkownicy[i].idUzytkownika == zalogowany.idUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            zapamietajHasloWPliku(uzytkownicy);
            cout << endl << "Haslo zostalo zmienione" << endl << endl;
            cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
            getch();
        }
    }
    wczytywanieUzytkownikowZPliku(uzytkownicy);
}

int uzyskanieOstatniegoWpisuID(){
    int ostatniID;
    string linia;
    vector<string> wydzieloneDane;
    Adresat osoba;
    fstream plik;
    //uzyskanie pustej ksiażkdi
    if(ifstream("Adresaci.txt")){
        plik.open("Adresaci.txt", ios::in);
        if(plik.good() == true) {
            while(getline(plik,linia)) {
                wydzieloneDane = wydzielenieWyrazow(linia);
                osoba.id = atoi(wydzieloneDane[0].c_str());
            }
            ostatniID = osoba.id;
        }
        plik.close();
    } else {
        ostatniID = 0;
    }
    return ostatniID;
}

void dodawanieOsoby(vector<Adresat> &adresaci, Uzytkownik zalogowany) {
    system("cls");
    int ostatniID;
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
    ostatniID = uzyskanieOstatniegoWpisuID();
    osoba.id = ostatniID + 1;
    adresaci.push_back(osoba);
    zapisanieDanychDoPliku(osoba, zalogowany);
    cout << "Kontakt dodany!" << endl << endl;
    cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
    getch();
}

void wczytywanieDanychZPliku(vector<Adresat> &adresaci, Uzytkownik zalogowany) {
    string linia;
    vector<string> wydzieloneDane;
    Adresat osoba;
    Uzytkownik uzytkownik;
    int numerLinii = 1;
    fstream plik;
    plik.open("Adresaci.txt", ios::in);
    if(plik.good() == true) {
        while(getline(plik,linia)) {
            wydzieloneDane = wydzielenieWyrazow(linia);
            osoba.id = atoi(wydzieloneDane[0].c_str());
            uzytkownik.idUzytkownika = atoi(wydzieloneDane[1].c_str());
            osoba.imie = wydzieloneDane[2];
            osoba.nazwisko = wydzieloneDane[3];
            osoba.numerTelefonu = wydzieloneDane[4];
            osoba.email = wydzieloneDane[5];
            osoba.adres = wydzieloneDane[6];
            if(uzytkownik.idUzytkownika == zalogowany.idUzytkownika) {
                adresaci.push_back(osoba);
            }
        }
        plik.close();
    }
}

void wyswietlKontakt(vector<Adresat> adresaci, int i) {
    cout << "Numer ID: " << adresaci[i].id << endl;
    cout << adresaci[i].imie << " " << adresaci[i].nazwisko << endl;
    cout << "Telefon: " << adresaci[i].numerTelefonu << endl;
    cout << "Email: " << adresaci[i].email << endl;
    cout << "Adres: " << adresaci[i].adres << endl;
    cout << endl;
}

void wyswietlanieListyKontaktow(vector<Adresat> adresaci) {
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

void wyswietlenieZalogowanego(Uzytkownik zalogowany) {
    cout << "(Zalogowano jako: " << zalogowany.nazwa << ")" << endl << endl;
}

void znajdywaniePoImieniu(vector<Adresat> adresaci) {
    string imie;
    cout << "***SZUKANIE ADRESATA***" << endl << endl;
    cout << "Podaj imie szukanej osoby: ";
    cin >> imie;
    imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imie);
    cout << endl << "Wszystkie osoby o imieniu " << "' " << imie << " ':" << endl << endl;
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
    cout << "***SZUKANIE ADRESATA***" << endl << endl;
    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> nazwisko;
    nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwisko);
    cout << endl << "Wszystkie osoby o nazwisku " << "' " << nazwisko << " ':" << endl << endl;
    for(int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].nazwisko == nazwisko) {
            wyswietlKontakt(adresaci, i);
        }
    }
    cout << endl;
    cout << "Wcisnij dowolny klawisz, aby wrocic do ekranu glownego.";
    getch();
}

void przepisanieDanychPoUsunieciu(int idUsunietego) {
    ifstream plikOryginalny("Adresaci.txt"); //wczytuje plik
    ofstream plikTymczasowy ("Adresaci_tymczasowy.txt"); // przygotowuje plik do zapisu
    vector<string> wydzieloneDane;
    Adresat osoba;
    Uzytkownik uzytkownik;
    string linia;
    if(plikOryginalny.good() == true) {
        while(getline(plikOryginalny,linia)) { //zapis linii z plikuOryginalnego do zmiennej linia
            wydzieloneDane = wydzielenieWyrazow(linia);
            osoba.id = atoi(wydzieloneDane[0].c_str());
            if(osoba.id == idUsunietego) {
                plikTymczasowy << ""; //nie przepisujemy lini usuwaj¹c kontakt
            } else {
                uzytkownik.idUzytkownika = atoi(wydzieloneDane[1].c_str());
                osoba.imie = wydzieloneDane[2];
                osoba.nazwisko = wydzieloneDane[3];
                osoba.numerTelefonu = wydzieloneDane[4];
                osoba.email = wydzieloneDane[5];
                osoba.adres = wydzieloneDane[6];
                plikTymczasowy << osoba.id << '|';
                plikTymczasowy << uzytkownik.idUzytkownika << '|';
                plikTymczasowy << osoba.imie << '|';
                plikTymczasowy << osoba.nazwisko << '|';
                plikTymczasowy << osoba.numerTelefonu << '|';
                plikTymczasowy << osoba.email << '|';
                plikTymczasowy << osoba.adres << '|' << endl;
            }
        }
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    plikOryginalny.close();
    plikTymczasowy.close();
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt","Adresaci.txt");
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
                przepisanieDanychPoUsunieciu(numer);
            } else if (znak == 'f') {
                cout << "Nie usunieto kontaktu." << endl;
            }
            return true;
        }
    }
}

void usuwanieAdresata(vector <Adresat> &adresaci) {
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

void przepisanieDanychPoEdycji(Adresat adresatEdytowany) {
    ifstream plikOryginalny("Adresaci.txt"); //wczytuje plik
    ofstream plikTymczasowy ("Adresaci_tymczasowy.txt"); // przygotowuje plik do zapisu
    vector<string> wydzieloneDane;
    Adresat osoba;
    Uzytkownik uzytkownik;
    string linia;
    if(plikOryginalny.good() == true) {
        while(getline(plikOryginalny,linia)) { //zapis linii z plikuOryginalnego do zmiennej linia
            wydzieloneDane = wydzielenieWyrazow(linia);
            osoba.id = atoi(wydzieloneDane[0].c_str());
            if(osoba.id != adresatEdytowany.id) {
                plikTymczasowy << linia << endl; //zapis ze zmiennej linia do plikuTymczasowego
            } else {
                plikTymczasowy << adresatEdytowany.id << '|';
                uzytkownik.idUzytkownika = atoi(wydzieloneDane[1].c_str());
                plikTymczasowy << uzytkownik.idUzytkownika << '|';
                plikTymczasowy << adresatEdytowany.imie << '|';
                plikTymczasowy << adresatEdytowany.nazwisko << '|';
                plikTymczasowy << adresatEdytowany.numerTelefonu << '|';
                plikTymczasowy << adresatEdytowany.email << '|';
                plikTymczasowy << adresatEdytowany.adres << '|' << endl;
            }
        }
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    plikOryginalny.close();
    plikTymczasowy.close();
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt","Adresaci.txt");
}

bool sprawdzCzyIstniejeTakiAdresat(vector<Adresat> &adresaci, int numer) {
    for(vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if (itr -> id == numer) {
            return true;
        }
    }
    return false;
}

void edytowanieAdresata(vector <Adresat> &adresaci) {
    cout << "***EDYTOWANIE ADRESATA***" << endl<<endl;
    cout << "Podaj numer wpisu(ID) adresata, ktorego chcesz edytowac: ";
    int numer;
    cin >> numer;
    while(sprawdzCzyIstniejeTakiAdresat(adresaci, numer) == false){
        cout << endl << "Nie ma osoby o takim numerze. Wprowadz go ponownie: ";
        cin >> numer;
    }
    cout << endl << "Dane kontaktowe: " << endl;
    for(int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].id == numer) {
            wyswietlKontakt(adresaci, i);
        }
    }
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
    cout << endl;
    switch(wybor) {
    case '1': {
        cout << "Wpisz nowe imie: ";
        cin >> imie;
        imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imie);
        for(int i = 0; i < adresaci.size(); i++) {
            if(adresaci[i].id == numer) {
                adresaci[i].imie = imie;
                przepisanieDanychPoEdycji(adresaci[i]);
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
                adresaci[i].nazwisko = nazwisko;
                przepisanieDanychPoEdycji(adresaci[i]);
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
                adresaci[i].numerTelefonu = numerTelefonu;
                przepisanieDanychPoEdycji(adresaci[i]);
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
                adresaci[i].email = email;
                przepisanieDanychPoEdycji(adresaci[i]);
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
                adresaci[i].adres = adres;
                przepisanieDanychPoEdycji(adresaci[i]);
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
}

void wyswietlMenuKsiazkiAdresowej() {
    cout << "KSIAZKA ADRESOWA" << endl << endl << "***" << endl << endl;
    cout << "Wybierz opcje: " << endl << endl;
    cout << "1. Dodaj osobe." << endl;
    cout << "2. Znajdz osobe po imieniu." << endl;
    cout << "3. Znajdz osobe po nazwisku." << endl;
    cout << "4. Wyswietl liste kontaktow." << endl;
    cout << "5. Usun adresata." << endl;
    cout << "6. Edytuj adresata." << endl;
    cout << "7. Zmien haslo." << endl;
    cout << "8. Wyloguj sie." << endl;
    cout << "9. Zamknij program." << endl << endl;
    cout << "Twoj wybor: ";
}

bool uzytkowanieKsiazkiAdresowej(vector<Uzytkownik> &uzytkownicy, Uzytkownik zalogowany) {
    vector<Adresat> adresaci;
    wczytywanieDanychZPliku(adresaci, zalogowany);
    char wyborOpcji;
    do {
        system("cls");
        wyswietlenieZalogowanego(zalogowany);
        wyswietlMenuKsiazkiAdresowej();
        cin >> wyborOpcji;
        switch(wyborOpcji) {
        case '1': {
            system("cls");
            wyswietlenieZalogowanego(zalogowany);
            dodawanieOsoby(adresaci, zalogowany);
            break;
        }
        case '2': {
            system("cls");
            wyswietlenieZalogowanego(zalogowany);
            znajdywaniePoImieniu(adresaci);
            break;
        }
        case '3': {
            system("cls");
            wyswietlenieZalogowanego(zalogowany);
            znajdywaniePoNazwisku(adresaci);
            break;
        }
        case '4': {
            system("cls");
            wyswietlenieZalogowanego(zalogowany);
            wyswietlanieListyKontaktow(adresaci);
            break;
        }
        case '5': {
            system("cls");
            wyswietlenieZalogowanego(zalogowany);
            usuwanieAdresata(adresaci);
            break;
        }
        case '6': {
            system("cls");
            wyswietlenieZalogowanego(zalogowany);
            edytowanieAdresata(adresaci);
            break;
        }
        case '7': {
            system("cls");
            wyswietlenieZalogowanego(zalogowany);
            zmianaHasla(uzytkownicy,zalogowany);
            break;
        }
        case '8': {
            return false;
        }
        case '9': {
            exit(0);
        }
        default: {
            cout <<  endl << "Nie istnieje taka opcja! Wcisnij dowolny klawisz, aby powtorzyc wybor.";
            getch();
            system("cls");
        }
        }
    } while (wyborOpcji != 9);
}

int main() {
    vector<Uzytkownik> uzytkownicy;
    Uzytkownik zalogowanyUzytkownik;
    wczytywanieUzytkownikowZPliku(uzytkownicy);
    char wybor;
    do {
        wyswietlOpcjeProgramu();
        cin >> wybor;
        switch(wybor) {
        case '1': {
            rejestracjaUzytkownika(uzytkownicy);
            break;
        }
        case '2': {
            zalogowanyUzytkownik = logowanieUzytkownika(uzytkownicy);
            if(zalogowanyUzytkownik.nazwa.empty()) {
                break;
            } else {
                if (uzytkowanieKsiazkiAdresowej(uzytkownicy, zalogowanyUzytkownik) == false) {
                    break;
                }
            }
        }
        case '3': {
            exit(0);
        }
        default: {
            cout <<  endl << "Nie istnieje taka opcja! Wcisnij dowolny klawisz, aby powtorzyc wybor.";
            getch();
        }
        }
    } while (wybor != 3);
    return 0;
}
