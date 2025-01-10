//
// Created by user on 12/25/2024.
//

#ifndef CAFEA_FUNCTIONS_H
#define CAFEA_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>
#include "Angajat.h"

using namespace std;

void rapoarte() {
    ifstream fisierA("raport.csv");

    if (fisierA.is_open()) {
        if (fisierA.peek() == ifstream::traits_type::eof()) {
            cout << "Fisierul raport.csv este gol." << endl;
            fisierA.close();
            return;
        }

        string linie;
        while (getline(fisierA, linie)) {
            stringstream ss(linie);
            string idStr, venitCstr, venitEstr, orasStr, costuriAstr,costuriRstr;
            getline(ss, idStr, ',');
            getline(ss, venitCstr, ',');
            getline(ss, venitEstr, ',');
            getline(ss, costuriAstr, ',');
            getline(ss,costuriRstr,',');
            getline(ss, orasStr, ',');

            cout << "------------------------------------------" << endl;
            cout << "Raport pentru ziua " << idStr << " - Oras: " << orasStr << endl;
            cout << "------------------------------------------" << endl;
            cout << "Venituri din comenzi:          " << venitCstr << " lei" << endl;
            cout << "Venituri din evenimente:      " << venitEstr << " lei" << endl;
            cout << "Costuri angajati:             " << costuriAstr << " lei" << endl;
            cout << "Costuri restock ingrediente:  " << costuriRstr << " lei" << endl;
            cout << "------------------------------------------" << endl;

        }
        fisierA.close();
    } else {
        cout << "Eroare la deschiderea fisierului raport.csv" << endl;
    }
}

void rapoarteE()
{
ifstream fisierA("raport.csv");

if (fisierA.is_open()) {
if (fisierA.peek() == ifstream::traits_type::eof()) {
cout << "The raport.csv file is empty." << endl;
fisierA.close();
return;
}

string linie;
while (getline(fisierA, linie)) {
stringstream ss(linie);
string idStr, venitCstr, venitEstr, cityStr, costuriAstr, costuriRstr;
getline(ss, idStr, ',');
getline(ss, venitCstr, ',');
getline(ss, venitEstr, ',');
getline(ss, costuriAstr, ',');
getline(ss, costuriRstr, ',');
getline(ss, cityStr, ',');

cout << "------------------------------------------" << endl;
cout << "Report for day " << idStr << " - City: " << cityStr << endl;
cout << "------------------------------------------" << endl;
cout << "Order revenues:             " << venitCstr << " lei" << endl;
cout << "Event revenues:            " << venitEstr << " lei" << endl;
cout << "Employee costs:             " << costuriAstr << " lei" << endl;
cout << "Restock ingredient costs:  " << costuriRstr << " lei" << endl;
cout << "------------------------------------------" << endl;

}
fisierA.close();
} else {
cout << "Error opening raport.csv file" << endl;
}
}


bool esteFisierGol(const string& caleFisier) {
    ifstream fisier(caleFisier, ios::ate);
    return fisier.tellg() == 0;
}


#endif //CAFEA_FUNCTIONS_H
