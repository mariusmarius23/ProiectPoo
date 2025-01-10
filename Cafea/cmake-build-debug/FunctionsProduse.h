#ifndef CAFEA_FUNCTIONSPRODUSE_H
#define CAFEA_FUNCTIONSPRODUSE_H
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "FunctionsComenzi.h"
using namespace std;


//clasa
class SistemProdus {
private:
    vector<Produs> produse;

    void incarcaDinFisier(const string& numeFisier) {
        ifstream fisier(numeFisier);
        if (!fisier.is_open()) {
            cerr << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        string linie;
        while (getline(fisier, linie)) {
            produse.push_back(Produs::fromCSV(linie));
        }
        fisier.close();
    }

    void salveazaInFisier(const string& numeFisier) const {
        ofstream fisier(numeFisier, ios::trunc);
        if (!fisier.is_open()) {
            cerr << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        for (const auto& produs : produse) {
            fisier << produs.getId() << "," << produs.getNume() << ","
                   << fixed << setprecision(2) << produs.getPret() << ","
                   << produs.getIngrediente() << endl;
        }

        fisier.close();
    }

public:
    //constructor
    SistemProdus(const string& numeFisier) {
        incarcaDinFisier(numeFisier);
    }

    void afiseazaProduse() const {
        if (produse.empty()) {
            cout << "Nu exista produse disponibile.\n";
            return;
        }

        cout << "Lista produselor:\n";
        for (const auto& produs : produse) {
            produs.afiseaza();
            cout << "Ingrediente: " << produs.getIngrediente() << endl;
            cout << "--------------------------" << endl;
        }
    }
//templates
    template<typename T>
    T citesteInput(const string& mesaj) {
        T valoare;
        cout << mesaj;
        while (!(cin >> valoare)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Introduceti un numar valid: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return valoare;
    }

    void adaugaProdus(const string& numeFisier) {
        string numeProdus;
        double pret;
        int numarIngrediente;
        vector<string> ingrediente;

        cout << "Introduceti numele produsului: ";
        cin.ignore();
        getline(cin, numeProdus);

        pret = citesteInput<double>("Introduceti pretul produsului: ");

        numarIngrediente = citesteInput<int>("Introduceti numarul de ingrediente: ");

        cout << "Introduceti ingredientele, separate prin ENTER:\n";

        for (int i = 0; i < numarIngrediente; ++i) {
            string ingredient;
            getline(cin, ingredient);
            ingrediente.push_back(ingredient);
        }

        int id = (produse.empty()) ? 1 : produse.back().getId() + 1;
        stringstream ingredienteCSV;
        for (size_t i = 0; i < ingrediente.size(); ++i) {
            ingredienteCSV << ingrediente[i];
            if (i < ingrediente.size() - 1) {
                ingredienteCSV << ",";
            }
        }

        Produs produsNou(id, numeProdus, pret, ingredienteCSV.str());
        produse.push_back(produsNou);

        salveazaInFisier(numeFisier);

        cout << "Produsul " << numeProdus << " a fost adaugat cu ID-ul " << id << ".\n";
    }

    void eliminaProdus(const string& numeFisier) {

        if (produse.empty()) {
            cout << "Fisierul este gol. Nu sunt produse de sters.\n";
            return;
        }

        afiseazaProduse();

        cout << "Introduceti ID-ul produsului de sters: ";
        int idDeSters;
        cin >> idDeSters;

        auto it = remove_if(produse.begin(), produse.end(),
                            [idDeSters](const Produs& p) { return p.getId() == idDeSters; });

        if (it == produse.end()) {
            cout << "Produsul cu ID-ul " << idDeSters << " nu a fost gasit.\n";
            return;
        }

        produse.erase(it, produse.end());

        for (int i = 0; i < produse.size(); ++i) {
            produse[i] = Produs(i + 1, produse[i].getNume(), produse[i].getPret(), produse[i].getIngrediente());
        }

        salveazaInFisier(numeFisier);
        cout << "Produsul cu ID-ul " << idDeSters << " a fost eliminat.\n";
    }

    void modificaPretProdus(const string& numeFisier) {
        if (produse.empty()) {
            cout << "Fisierul este gol. Nu sunt produse de modificat.\n";
            return;
        }

        afiseazaProduse();

        cout << "Introduceti ID-ul produsului pentru modificarea pretului: ";
        int idDeModificat;
        cin >> idDeModificat;

        bool gasit = false;
        for (auto& produs : produse) {
            if (produs.getId() == idDeModificat) {
                gasit = true;
                break;
            }
        }

        if (!gasit) {
            cout << "Produsul cu ID-ul " << idDeModificat << " nu a fost gasit.\n";
            return;
        }


        double pretNou;
        cout << "Introduceti noul pret: ";
        while (!(cin >> pretNou)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Introduceti un pret valid: ";
        }

        for (auto& produs : produse) {
            if (produs.getId() == idDeModificat) {
                produs = Produs(produs.getId(), produs.getNume(), pretNou, produs.getIngrediente());
                break;
            }
        }

        salveazaInFisier(numeFisier);
        cout << "Pretul produsului cu ID-ul " << idDeModificat << " a fost modificat la " << pretNou << " lei.\n";
    }

};


#endif //CAFEA_FUNCTIONSPRODUSE_H
