#ifndef CAFEA_ANGAJAT_H
#define CAFEA_ANGAJAT_H

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>

double COSTURI_ANGAJATI=0.0;

using namespace std;
// Clasa Angajat - model general pentru toți angajații

class Angajat {
protected:
    string nume;
    int varsta;
    double salariuPeOra;
    string oraInceputTura;
    string oraFinalTura;
    string functia;

public:
    // Constructor pentru clasa Angajat

    Angajat(string nume,
            int varsta,
            double salariuPeOra,
            string oraInceputTura,
            string oraFinalTura,
            string functia
    ): nume(nume),
       varsta(varsta),
       salariuPeOra(salariuPeOra),
       oraInceputTura(oraInceputTura),
       oraFinalTura(oraFinalTura),
       functia(functia) {}

    // Destructor
    virtual ~Angajat() {}

    //Getters setters

    string getNume() const {
        return nume;
    }

    void setOraInceputTura(string oraNoua) {
        oraInceputTura = oraNoua;
    }

    void setOraFinalTura(string oraNoua) {
        oraFinalTura = oraNoua;
    }

    string getDetalii() const {
        return "Nume: " + nume + ", Varsta: " + to_string(varsta) + ", Salariu/h: " + to_string(salariuPeOra) +
               ", Tura: " + oraInceputTura + "-" + oraFinalTura + ", Functie: " + functia;
    }

    virtual string getCSVData() const {
        return nume + "," + to_string(varsta) + "," + to_string(salariuPeOra) + "," + oraInceputTura + "," + oraFinalTura + "," + functia;
    }

    static bool isValidTime(const string& timeStr) {
        if (timeStr.size() != 5 || timeStr[2] != ':') return false;

        string hourStr = timeStr.substr(0, 2);
        string minuteStr = timeStr.substr(3, 2);

        if (!isdigit(hourStr[0]) || !isdigit(hourStr[1]) ||
            !isdigit(minuteStr[0]) || !isdigit(minuteStr[1])) {
            return false;
        }

        int hour = stoi(hourStr);
        int minute = stoi(minuteStr);

        return (hour >= 0 && hour < 24) && (minute >= 0 && minute < 60);
    }

    static int verificaExistentaNume(const string& nume, const string& numeFisier) {
        ifstream fisier(numeFisier);
        string linie;
        bool luat = false;
        int count = 0;
        int v[10000] = {0};

        while (getline(fisier, linie)) {
            stringstream ss(linie);
            string numeLuat;
            int x;
            getline(ss, numeLuat, ',');

            string altString = numeLuat.substr(0, numeLuat.find('('));
            size_t xLen = numeLuat.length();
            string sufix;
            if (xLen > 2) {
                sufix = numeLuat[xLen - 2];
            }
            if (luat && nume == altString) {
                x = stoi(sufix);
            }
            if (nume == numeLuat) {
                v[0] = 1;
                luat = true;
            } else if (nume == altString && luat) {
                v[x] = 1;
            }
        }

        int i = 0;
        while (v[i]) {
            i++;
        }

        fisier.close();
        return i;
    }

    //Metode de organizare

    void salveazaAngajat(const string& numeFisier) {
        ofstream fisier(numeFisier, ios::app);
        if (!fisier.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul " << numeFisier << endl;
            return;
        }
        fisier << getCSVData() << endl;
        fisier.close();
    }

    static void afiseazaAngajati(const string& numeFisier) {
        ifstream fisier(numeFisier);

        if (!fisier.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul " << numeFisier << endl;
            return;
        }

        string linie;
        cout << left;
        cout << setw(20) << "Nume"
             << setw(10) << "Varsta"
             << setw(15) << "Salariu/h"
             << setw(15) << "Tura (inceput)"
             << setw(15) << "Tura (final)"
             << setw(15) << "Functie" << endl;

        cout << string(90, '-') << endl;

        while (getline(fisier, linie)) {
            stringstream ss(linie);
            string nume, varsta, salariuPeOra, oraInceputTura, oraFinalTura, functie;

            getline(ss, nume, ',');
            getline(ss, varsta, ',');
            getline(ss, salariuPeOra, ',');
            getline(ss, oraInceputTura, ',');
            getline(ss, oraFinalTura, ',');
            getline(ss, functie, ',');

            cout << setw(20) << nume
                 << setw(10) << varsta
                 << setw(15) << salariuPeOra
                 << setw(15) << oraInceputTura
                 << setw(15) << oraFinalTura
                 << setw(15) << functie << endl;
        }

        fisier.close();
    }

    static void stergeAngajat(const string& numeFisier) {
        ifstream fisierIn(numeFisier);
        if (!fisierIn.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul " << numeFisier << endl;
            return;
        }

        vector<string> linii;
        string linie;
        bool gasit = false;

        bool fisierGol = true;

        while (getline(fisierIn, linie)) {
            fisierGol = false;
            linii.push_back(linie);
        }
        fisierIn.close();

        if (fisierGol) {
            cout << "Fisierul este gol. Nu exista angajati de sters." << endl;
            return;
        }

        cout << "Angajatii existenti:\n";
        for (const auto& linie : linii) {
            stringstream ss(linie);
            string nume, varsta, salariuPeOra, oraInceputTura, oraFinalTura, functie;

            getline(ss, nume, ',');
            getline(ss, varsta, ',');
            getline(ss, salariuPeOra, ',');
            getline(ss, oraInceputTura, ',');
            getline(ss, oraFinalTura, ',');
            getline(ss, functie, ',');

            cout << setw(20) << nume
                 << setw(10) << varsta
                 << setw(15) << salariuPeOra
                 << setw(15) << oraInceputTura
                 << setw(15) << oraFinalTura
                 << setw(15) << functie << endl;
        }

        string numeAngajatSters;
        cout << "Introduceti numele angajatului pe care doriti sa-l stergeti: ";
        cin.ignore();
        getline(cin, numeAngajatSters);

        for (const auto& linie : linii) {
            stringstream ss(linie);
            string numeAngajat;
            getline(ss, numeAngajat, ',');
            if (numeAngajat == numeAngajatSters) {
                gasit = true;
                break;
            }
        }

        if (!gasit) {
            cout << "Nu a fost gasit un angajat cu numele " << numeAngajatSters << "." << endl;
            return;
        }

        ofstream fisierOut(numeFisier, ios::trunc);
        if (!fisierOut.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul pentru scriere " << numeFisier << endl;
            return;
        }

        for (const auto& linie : linii) {
            stringstream ss(linie);
            string numeAngajat;
            getline(ss, numeAngajat, ',');
            if (numeAngajat != numeAngajatSters) {
                fisierOut << linie << endl;
            }
        }
        fisierOut.close();

        cout << "Angajatul " << numeAngajatSters << " a fost sters cu succes." << endl;
    }

    static void gestioneazaProgramul(const string& numeFisier) {
        ifstream fisierIn(numeFisier);
        if (!fisierIn.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul " << numeFisier << endl;
            return;
        }

        vector<Angajat> angajati;
        string linie;

        while (getline(fisierIn, linie)) {
            stringstream ss(linie);
            string nume, varstaStr, salariuStr, oraInceputStr, oraFinalStr, functie;
            getline(ss, nume, ',');
            getline(ss, varstaStr, ',');
            getline(ss, salariuStr, ',');
            getline(ss, oraInceputStr, ',');
            getline(ss, oraFinalStr, ',');
            getline(ss, functie, ',');

            int varsta = stoi(varstaStr);
            double salariuPeOra = stod(salariuStr);

            angajati.emplace_back(nume, varsta, salariuPeOra, oraInceputStr, oraFinalStr, functie);
        }
        fisierIn.close();

        if (angajati.empty()) {
            cout << "Fisierul este gol. Nu exista angajati." << endl;
            return;
        }

        cout << "Angajatii existenti:\n";
        for (const auto& angajat : angajati) {
            cout << angajat.getDetalii() << endl;
        }

        string numeAngajat;
        cout << "Introduceti numele angajatului caruia doriti sa ii modificati programul: ";
        cin.ignore();
        getline(cin, numeAngajat);

        bool gasit = false;
        for (auto& angajat : angajati) {
            if (angajat.getNume() == numeAngajat) {
                gasit = true;
                break;
            }
        }

        if (!gasit) {
            cout << "Angajatul cu numele " << numeAngajat << " nu a fost gasit." << endl;
            return;
        }


        string oraNouaInceput, oraNouaFinal;
        while (true) {
            cout << "Introduceti noua ora de inceput a turei (format XX:YY): ";
            cin >> oraNouaInceput;
            if (isValidTime(oraNouaInceput)) {
                break;
            } else {
                cout << "Eroare: Ora invalida. Reincercati." << endl;
            }
        }

        while (true) {
            cout << "Introduceti noua ora de final a turei (format XX:YY): ";
            cin >> oraNouaFinal;
            if (isValidTime(oraNouaFinal)) {
                break;
            } else {
                cout << "Eroare: Ora invalida. Reincercati." << endl;
            }
        }

        gasit = false;
        for (auto& angajat : angajati) {
            if (angajat.getNume() == numeAngajat) {
                gasit = true;
                angajat.setOraInceputTura(oraNouaInceput);
                angajat.setOraFinalTura(oraNouaFinal);
                cout << "Programul angajatului " << numeAngajat << " a fost actualizat." << endl;
                break;
            }
        }

        if (!gasit) {
            cout << "Angajatul cu numele " << numeAngajat << " nu a fost gasit." << endl;
            return;
        }

        ofstream fisierOut(numeFisier, ios::trunc);
        if (!fisierOut.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul pentru scriere " << numeFisier << endl;
            return;
        }

        for (const auto& angajat : angajati) {
            fisierOut << angajat.getCSVData() << endl;
        }
        fisierOut.close();
    }

    static void introduAngajat(const string& numeFisier) {
        string nume;
        int varsta;
        double salariuPeOra;
        string oraInceputTuraStr, oraFinalTuraStr;

        cout << "Introduceti numele angajatului: ";
        cin.ignore();
        getline(cin, nume);

        if (nume.empty()) {
            cout << "Eroare: Numele nu poate fi gol. Reincercati." << endl;
            return;
        }

        int sufix = verificaExistentaNume(nume, numeFisier);
        if (sufix > 0) {
            nume += "(" + to_string(sufix) + ")";
        }

        while (true) {
            cout << "Introduceti varsta: ";
            cin >> varsta;
            if (cin.fail() || varsta <= 0 || varsta > 100) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Eroare: Varsta invalida. Reincercati." << endl;
            } else {
                break;
            }
        }

        while (true) {
            cout << "Introduceti salariul pe ora: ";
            cin >> salariuPeOra;
            if (cin.fail() || salariuPeOra <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Eroare: Salariu invalid. Reincercati." << endl;
            } else {
                break;
            }
        }

        while (true) {
            cout << "Introduceti ora de inceput a turei (format XX:YY): ";
            cin >> oraInceputTuraStr;
            if (isValidTime(oraInceputTuraStr)) {
                break;
            } else {
                cout << "Eroare: Ora invalida. Reincercati." << endl;
            }
        }

        while (true) {
            cout << "Introduceti ora de final a turei (format XX:YY): ";
            cin >> oraFinalTuraStr;
            if (isValidTime(oraFinalTuraStr)) {
                break;
            } else {
                cout << "Eroare: Ora invalida. Reincercati." << endl;
            }
        }

        cout << "Selectati functia angajatului: 1. Barista, 2. Manager, 3. Ospatar. Optiune: ";
        int optiune;
        string functie;
        while (true) {
            cin >> optiune;
            if (cin.fail() || (optiune < 1 || optiune > 3)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Optiune invalida. Reincercati: ";
            } else {
                functie = (optiune == 1) ? "Barista" : (optiune == 2) ? "Manager" : "Ospatar";
                break;
            }
        }

        Angajat angajat(nume, varsta, salariuPeOra, oraInceputTuraStr, oraFinalTuraStr, functie);
        angajat.salveazaAngajat(numeFisier);
        cout << "Angajat adaugat cu succes." << endl;
    }

    static void calculeazaCosturiAngajati(const string& numeFisier) {
        ifstream fisier(numeFisier);

        if (!fisier.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul " << numeFisier << endl;
            return;
        }

        string linie;
        COSTURI_ANGAJATI = 0.0;

        while (getline(fisier, linie)) {
            stringstream ss(linie);
            string nume, varstaStr, salariuStr, oraInceputStr, oraFinalStr, functie;

            if (!getline(ss, nume, ',')) continue;
            if (!getline(ss, varstaStr, ',')) continue;
            if (!getline(ss, salariuStr, ',')) continue;
            if (!getline(ss, oraInceputStr, ',')) continue;
            if (!getline(ss, oraFinalStr, ',')) continue;
            if (!getline(ss, functie, ',')) continue;

            try {
                double salariuPeOra = stod(salariuStr);

                int oraInceput = stoi(oraInceputStr.substr(0, 2));
                int minutInceput = stoi(oraInceputStr.substr(3, 2));
                int oraFinal = stoi(oraFinalStr.substr(0, 2));
                int minutFinal = stoi(oraFinalStr.substr(3, 2));

                int totalMinute = (oraFinal * 60 + minutFinal) - (oraInceput * 60 + minutInceput);
                if (totalMinute < 0) {
                    totalMinute += 24 * 60;
                }

                double oreLucrate = totalMinute / 60.0;

                COSTURI_ANGAJATI += oreLucrate * salariuPeOra;
            } catch (const exception& e) {
                cout << "Eroare la procesarea liniei: " << linie << endl;
                cout << "Detalii: " << e.what() << endl;
                continue;
            }
        }

        fisier.close();
    }
};

class Ospatar : public Angajat {
public:
    Ospatar(
            string nume,
            int varsta,
            double salariuPeOra,
            string oraInceputTura,
            string oraFinalTura
    ): Angajat(
            nume,
            varsta,
            salariuPeOra,
            oraInceputTura,
            oraFinalTura,
            "Ospatar"
    ) {}

};

class Barista : public Angajat {
public:
    Barista(
            string nume,
            int varsta,
            double salariuPeOra,
            string oraInceputTura,
            string oraFinalTura
    ): Angajat(
            nume,
            varsta,
            salariuPeOra,
            oraInceputTura,
            oraFinalTura,
            "Barista"
    ) {}
};

class Manager : public Angajat {
public:

    Manager(
            string nume,
            int varsta,
            double salariuPeOra,
            string oraInceputTura,
            string oraFinalTura
    ): Angajat(
            nume,
            varsta,
            salariuPeOra,
            oraInceputTura,
            oraFinalTura,
            "Manager"
    ) {}

};



#endif //CAFEA_ANGAJAT_H
