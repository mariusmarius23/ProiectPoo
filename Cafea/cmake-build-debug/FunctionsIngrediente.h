//
// Created by user on 12/26/2024.
//

#ifndef CAFEA_FUNCTIONSINGREDIENTE_H
#define CAFEA_FUNCTIONSINGREDIENTE_H

using namespace std;

#include "Functions.h"
double COSTURI_RESTOCK = 0.0;


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//clase
class Ingredient {
private:
    int id;
    string nume;
    double pretRestock;
    int capacitateMaxima;
    int stocCurent;

public:
    //constructor
    Ingredient(int id, string nume, double pretRestock, int capacitateMaxima, int stocCurent)
            : id(id), nume(nume), pretRestock(pretRestock), capacitateMaxima(capacitateMaxima), stocCurent(stocCurent) {}

            //getters setters
    int getId() const { return id; }

    string getNume() const { return nume; }

    double getPretRestock() const { return pretRestock; }

    int getCapacitateMaxima() const { return capacitateMaxima; }

    int getStocCurent() const { return stocCurent; }

    void setStocCurent(int stoc) { stocCurent = stoc; }

    void setPretRestock(double pret) { pretRestock = pret; }

    void setCapacitateMaxima(int capacitate) { capacitateMaxima = capacitate; }

    void setNume(const string& numeNou) { nume = numeNou; }

    void afiseaza() const {
        cout << "| ID: " << id << " | Produs: " << nume << " | Pret Restock: " << pretRestock
             << " | Stocuri: " << stocCurent << "/" << capacitateMaxima << " |" << endl;
    }

    void salveazaInFisier(ofstream& fisierOut) const {
        fisierOut << id << "," << nume << "," << pretRestock << "," << capacitateMaxima << "," << stocCurent << endl;
    }

    static Ingredient fromCSV(const string& linie) {
        stringstream ss(linie);
        string idStr, nume, pret, capacitateMaxStr, stocStr;
        getline(ss, idStr, ',');
        getline(ss, nume, ',');
        getline(ss, pret, ',');
        getline(ss, capacitateMaxStr, ',');
        getline(ss, stocStr, ',');

        int id = stoi(idStr);
        double pretRestock = stod(pret);
        int capacitateMaxima = stoi(capacitateMaxStr);
        int stocCurent = stoi(stocStr);

        return Ingredient(id, nume, pretRestock, capacitateMaxima, stocCurent);
    }
};

//clase
class SistemIngrediente {
private:
    vector<Ingredient> ingrediente;

    void citesteDinFisier(const string& numeFisier) {
        ifstream fisierIn(numeFisier);
        if (!fisierIn.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul " << numeFisier << endl;
            return;
        }

        string linie;
        while (getline(fisierIn, linie)) {
            ingrediente.push_back(Ingredient::fromCSV(linie));
        }

        fisierIn.close();
    }

    void salveazaInFisier(const string& numeFisier) {
        ofstream fisier(numeFisier,ios::trunc);
        if (!fisier.is_open()) {
            cout << "Eroare: Nu se poate deschide fisierul " << numeFisier << endl;
            return;
        }

        for (const auto& ingredient : ingrediente) {
            fisier << ingredient.getId() << "," << ingredient.getNume() << ","
                   << fixed << setprecision(2) << ingredient.getPretRestock() << ","
                   << ingredient.getCapacitateMaxima() << ","<<ingredient.getStocCurent()<<endl;
        }

        fisier.close();
    }

    bool esteIntValid(int& numar) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

    bool esteDoubleValid(double& numar) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

public:
    //constructor
    SistemIngrediente(const string& numeFisier) {
        citesteDinFisier(numeFisier);
    }
    void afiseazaListaIngrediente() const {
        if (ingrediente.empty()) {
            cout << "Lista de ingrediente este goala!" << endl;
            return;
        }

        cout << "\nLista de Ingrediente:\n";
        cout << "--------------------\n";
        for (const auto& ingredient : ingrediente) {
            ingredient.afiseaza();
        }
    }

    void adaugaIngredient(const string& numeFisier) {
        int id = ingrediente.empty() ? 1 : ingrediente.back().getId() + 1;
        string nume;
        double pretRestock;
        int capacitateMaxima;
        int stocCurent;

        cout << "Introduceti numele ingredientului: ";
        cin.ignore();
        getline(cin, nume);

        do {
            cout << "Introduceti pretul ingredientului pentru restock: ";
            cin >> pretRestock;
        } while (!esteDoubleValid(pretRestock) || pretRestock <= 0);

        do {
            cout << "Introduceti capacitatea maxima de stocuri: ";
            cin >> capacitateMaxima;
        } while (!esteIntValid(capacitateMaxima) || capacitateMaxima <= 0);

        do {
            cout << "Introduceti stocul curent: ";
            cin >> stocCurent;
        } while (!esteIntValid(stocCurent) || stocCurent < 0 || stocCurent > capacitateMaxima);

        if (stocCurent > capacitateMaxima) {
            cout << "Stocul nu poate depasi capacitatea maxima!" << endl;
            return;
        }

        Ingredient ingredientNou(id,nume,pretRestock,capacitateMaxima,stocCurent);
        ingrediente.push_back(ingredientNou);
        salveazaInFisier(numeFisier);
        cout << "Ingredientul "<< nume <<" a fost adaugat cu succes!" << endl;
    }

    void eliminaIngredient(const string& numeFisier) {

        if (ingrediente.empty()) {
            cout << "Fisierul este gol. Nu sunt produse de sters.\n";
            return;
        }

        afiseazaListaIngrediente();

        int id;
        cout << "Introduceti ID-ul ingredientului de sters: ";
        cin >> id;

        auto it = find_if(ingrediente.begin(), ingrediente.end(), [id](const Ingredient& ing) {
            return ing.getId() == id;
        });

        if (it != ingrediente.end()) {
            ingrediente.erase(it);
            cout << "Ingredientul cu ID-ul " << id << " a fost sters!" << endl;
        } else {
            cout << "Ingredientul cu ID-ul " << id << " nu a fost gasit!" << endl;
        }

        for (int i = 0; i < ingrediente.size(); ++i) {
            ingrediente[i] = Ingredient(i + 1, ingrediente[i].getNume(), ingrediente[i].getPretRestock(), ingrediente[i].getCapacitateMaxima(),ingrediente[i].getStocCurent());
        }
        salveazaInFisier(numeFisier);


    }

    void modificaStoc(const string& numeFisier) {

        if (ingrediente.empty()) {
            cout << "Fisierul este gol. Nu sunt produse de modificat.\n";
            return;
        }

        afiseazaListaIngrediente();

        int id;
        cout << "Introduceti ID-ul ingredientului pentru a modifica stocul: ";
        cin >> id;

        auto it = find_if(ingrediente.begin(), ingrediente.end(), [id](const Ingredient& ing) {
            return ing.getId() == id;
        });

        if (it != ingrediente.end()) {
            int cantitateAdaugata;
            cout << "Introduceti cantitatea pe care doriti sa o adaugati la stoc: ";
            cin >> cantitateAdaugata;

            int nouStoc = it->getStocCurent() + cantitateAdaugata;
            if (nouStoc > it->getCapacitateMaxima()) {
                cout << "Stocul depaseste capacitatea maxima!" << endl;
            } else {
                double costRestock = cantitateAdaugata * it->getPretRestock();
                COSTURI_RESTOCK += costRestock;
                it->setStocCurent(nouStoc);
                cout << "Stocul a fost actualizat cu succes!" << endl;
                cout << "Costul pentru acest restock: " << fixed << setprecision(2) << costRestock << " lei." << endl;
            }
        } else {
            cout << "Ingredientul cu ID-ul " << id << " nu a fost gasit!" << endl;
        }

        salveazaInFisier(numeFisier);

    }


};

#endif //CAFEA_FUNCTIONSINGREDIENTE_H
