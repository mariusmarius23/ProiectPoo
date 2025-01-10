//
// Created by user on 12/26/2024.
//

#ifndef CAFEA_FUNCTIONSCOMENZI_H
#define CAFEA_FUNCTIONSCOMENZI_H
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "FunctionsIngrediente.h"
#include "Gestiune.h"
#include "Functions.h"

double VENIT_COMENZI=0.0;

using namespace std;

//clase si obiecte
class Produs {
private:
    int id;
    string nume;
    double pret;
    string ingrediente;

public:
    //constructor
    Produs() = default;

    Produs(int id, string nume, double pret, string ingrediente)
            : id(id), nume(nume), pret(pret), ingrediente(ingrediente) {}

            //Incapsulare
    int getId() const { return id; }
    string getNume() const { return nume; }
    double getPret() const { return pret; }
    string getIngrediente() const { return ingrediente; }

    static Produs fromCSV(const string& linie) {
        stringstream ss(linie);
        string temp;
        int id;
        string nume;
        double pret;
        string ingrediente;

        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, nume, ',');
        getline(ss, temp, ',');
        pret = stod(temp);
        getline(ss, ingrediente);

        return Produs(id, nume, pret, ingrediente);
    }

    void afiseaza() const {
        cout << id << ". " << nume << " - " << pret << " lei\n";
    }
};
//clase si obiecte
class Comanda {
private:
    int idClient;
    string numeClient;
    vector<int> idProduse;
    double costTotal;

public:
    //Constructor
    Comanda() : idClient(0), costTotal(0) {}

    //Getters setters
    void setIdClient(int id) { idClient = id; }
    void setNumeClient(const string& nume) { numeClient = nume; }

    void setCostTotal(double cost) { costTotal = cost; }
    double getCostTotal() const { return costTotal; }

    void adaugaProdus(int idProdus, double pret) {
        idProduse.push_back(idProdus);
        costTotal += pret;
    }

    string toCSV() const {
        stringstream ss;
        ss << idClient << "," << numeClient << "," << costTotal << ",";
        for (size_t i = 0; i < idProduse.size(); ++i) {
            ss << idProduse[i];
            if (i < idProduse.size() - 1) ss << ";";
        }
        return ss.str();
    }
};

//Design pattern observer
class Observer {
public:
    virtual ~Observer() {}
    virtual void update(const std::string& ingredient, int currentAmount, int maxCapacity) = 0;
};

class Subject {
private:
    vector<Observer*> observers;
    vector<vector<string>> ingredienteData;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const std::string& ingredient, int currentAmount, int maxCapacity) {
        for (Observer* observer : observers) {
            observer->update(ingredient, currentAmount, maxCapacity);
        }
    }

    void setIngredientData(const vector<vector<string>>& data) {
        ingredienteData = data;
    }

    vector<vector<string>> getIngredientData() {
        return ingredienteData;
    }
};

class IngredientObserver : public Observer {
public:
    void update(const std::string& ingredient, int currentAmount, int maxCapacity) override {
        cout << "Restocare necesara pentru ingredientul: " << ingredient
             << " (stoc curent: " << currentAmount -1<< ", capacitate maxima: " << maxCapacity << ")\n";
        int restockAmount = static_cast<int>(0.5 * maxCapacity - currentAmount);
        cout << "Restocam " << restockAmount - 1 << " unitati.\n";
    }
};


//Mostenire
class GestiuneComenzi : public Gestiune {
private:
    vector<Produs> produse;
    map<string, int> mapareClienti;
    int ultimulId;
    string folder;

    void incarcaProduse() {
        string caleFisier = folder + "/produse.csv";
        ifstream fin(caleFisier);
        string linie;

        while (getline(fin, linie)) {
            produse.push_back(Produs::fromCSV(linie));
        }

        fin.close();
    }

    void incarcaClienti() {
        string caleFisier = folder + "/comenzi.csv";

        if (esteFisierGol(caleFisier)) {
            cout << "Fisierul comenzi.csv este gol. Nu exista comenzi de incarcat.\n";
            return;
        }

        ifstream fin(caleFisier);
        string linie;
        ultimulId = 0;

        while (getline(fin, linie)) {
            stringstream ss(linie);
            string temp, numeClient;

            if (!getline(ss, temp, ',') || temp.empty()) continue;
            if (!getline(ss, numeClient, ',') || numeClient.empty()) continue;

            int id;
            try {
                id = stoi(temp);
            } catch (const invalid_argument& e) {
                cout << "Eroare: Linia contine un ID invalid: " << temp << "\n";
                continue;
            }

            mapareClienti[numeClient] = id;
            ultimulId = max(ultimulId, id);
        }

        fin.close();
    }


public:
    //Constructor
    GestiuneComenzi(const string& folderPath) : ultimulId(0), folder(folderPath) {
        incarcaProduse();
        incarcaClienti();
    }

    //Abstractizare
    void actualizeazaStocuri(const vector<int>& idProduse) {

        string caleFisierIngrediente = folder + "/ingrediente.csv";
        ifstream fin(caleFisierIngrediente);
        vector<vector<string>> ingrediente;
        string linie;

        while (getline(fin, linie)) {
            stringstream ss(linie);
            vector<string> campuri;
            string camp;

            while (getline(ss, camp, ',')) {
                campuri.push_back(camp);
            }
            ingrediente.push_back(campuri);
        }
        fin.close();

        Subject subject;
        IngredientObserver observer;
        subject.attach(&observer);
        subject.setIngredientData(ingrediente);

        for (int idProdus : idProduse) {
            auto itProdus = find_if(produse.begin(), produse.end(),
                                    [idProdus](const Produs& p) { return p.getId() == idProdus; });

            if (itProdus != produse.end()) {
                string ingredienteProdus = itProdus->getIngrediente();
                stringstream ss(ingredienteProdus);
                string ingredient;

                while (getline(ss, ingredient, ',')) {
                    for (auto& ing : ingrediente) {
                        if (ing[1] == ingredient) {
                            int stocCurent = stoi(ing[4]);
                            int capacitateMaxima = stoi(ing[3]);
                            double pretRestock = stod(ing[2]);

                            if (stocCurent > 0) {
                                ing[4] = to_string(stocCurent - 1);
                            } else {
                                cout << "Stoc epuizat pentru ingredientul: " << ingredient << "\n";
                            }

                            if (stocCurent - 1 < 0.1 * capacitateMaxima) {
                                int restockAmount = static_cast<int>(0.5 * capacitateMaxima - (stocCurent - 1));
                                ing[4] = to_string(stocCurent - 1 + restockAmount);

                                subject.notify(ingredient, stocCurent, capacitateMaxima);

                                double costRestock = restockAmount * pretRestock;
                                COSTURI_RESTOCK += costRestock;
                            }
                            break;
                        }
                    }
                }
            }
        }

        ofstream fout(caleFisierIngrediente);
        for (const auto& ing : ingrediente) {
            fout << ing[0] << "," << ing[1] << "," << ing[2] << "," << ing[3] << "," << ing[4] << "\n";
        }
        fout.close();
    }


//polimorfism
    bool verificaDisponibilitateaIngredientului(const string& ingredient) {
        string caleFisierIngrediente = folder + "/ingrediente.csv";
        ifstream fin(caleFisierIngrediente);
        string linie;

        while (getline(fin, linie)) {
            stringstream ss(linie);
            string denumire,temp;

            getline(ss, temp, ',');
            getline(ss, denumire, ',');
            getline(ss, temp, ',');
            getline(ss, temp, ',');
            getline(ss, temp, ',');

            if (denumire == ingredient)
                return true;

        }

        fin.close();
        return false;
    }
//polimorfism
    void adauga() {
        Comanda comanda;

        cout << "Introduceti numele complet al clientului (sau tastati 'x' pentru a anula): ";
        string numeClient;
        cin.ignore();
        getline(cin, numeClient);

        if (numeClient.empty()) {
            cout << "Eroare: Numele nu poate fi gol. Reincercati." << endl;
            return;
        }


        if (numeClient == "x") {
            cout << "\nComanda a fost anulata.\n";
            return;
        }

        ifstream fisierC(folder+"/clienti.csv");
        int id=1;
        if (fisierC.is_open()) {
            string linie;
            while (getline(fisierC, linie)) {
                stringstream ss(linie);
                string temp,nume;
                getline(ss,temp,',');
                getline(ss,nume,',');
                if(nume==numeClient)
                    break;
                else
                    id++;
            }
            fisierC.close();
        }


        int idClient = id;
        comanda.setNumeClient(numeClient);
        comanda.setIdClient(idClient);

        cout << "\nProduse disponibile:\n";
        for (const auto& p : produse) {
            p.afiseaza();
        }

        cout << "\nIntroduceti ID-urile produselor (tastati 'x' pentru a anula sau 0 pentru a termina):\n";
        vector<int> idProduseComandate;
        bool comandaValida = true;

        while (true) {
            string input;
            cout << "ID produs: ";
            cin >> input;

            if (input == "x") {
                cout << "\nComanda a fost anulata.\n";
                return;
            }

            int idProdus = stoi(input);
            if (idProdus == 0) break;

            auto it = find_if(produse.begin(), produse.end(),
                              [idProdus](const Produs& p) { return p.getId() == idProdus; });

            if (it != produse.end()) {
                string ingredienteProdus = it->getIngrediente();
                stringstream ss(ingredienteProdus);
                string ingredient;
                bool ingredienteDisponibile = true;

                while (getline(ss, ingredient, ',')) {
                    if (!verificaDisponibilitateaIngredientului(ingredient)) {
                        cout << "Nu exista in sistem ingredientul:  " << ingredient << ". Comanda va fi anulata.\n";
                        ingredienteDisponibile = false;
                        break;
                    }
                }

                if (ingredienteDisponibile) {
                    comanda.adaugaProdus(idProdus, it->getPret());
                    idProduseComandate.push_back(idProdus);
                } else {
                    comandaValida = false;
                    break;
                }
            } else {
                cout << "Produs invalid!\n";
            }
        }

        if (idProduseComandate.empty()) {
            cout << "\nNu au fost selectate produse. Comanda a fost anulata.\n";
            return;
        }

        string caleFisierClienti = folder + "/clienti.csv";
        int numarComenzi = 0;
        ifstream finClienti(caleFisierClienti);
        string linie;
        vector<string> clienti;

        while (getline(finClienti, linie)) {
            stringstream ss(linie);
            string id, nume, comenzi;

            getline(ss, id, ',');
            getline(ss, nume, ',');
            getline(ss, comenzi, ',');

            if (numeClient==nume) {
                numarComenzi = stoi(comenzi);
            }

            clienti.push_back(linie);
        }
        finClienti.close();

        double reducere = 0;
        if (numarComenzi >= 15) {
            reducere = 0.15;
        } else if (numarComenzi >= 10) {
            reducere = 0.10;
        } else if (numarComenzi >= 5) {
            reducere = 0.05;
        }

        double costTotal = comanda.getCostTotal();
        costTotal -= costTotal * reducere;
        comanda.setCostTotal(costTotal);
        VENIT_COMENZI=VENIT_COMENZI+costTotal;
        bool clientGasit = false;
        ofstream foutClienti(caleFisierClienti);
        for (const auto& linieClient : clienti) {
            stringstream ss(linieClient);
            string id, nume, comenzi;

            getline(ss, id, ',');
            getline(ss, nume, ',');
            getline(ss, comenzi, ',');

            if (nume==numeClient) {
                foutClienti << id << "," << nume << "," << (numarComenzi + 1) << "\n";
                clientGasit = true;
            } else {
                foutClienti << linieClient << "\n";
            }
        }

        if (!clientGasit) {
            foutClienti << idClient << "," << numeClient << ",1\n";
        }
        foutClienti.close();

        string caleFisierComenzi = folder + "/comenzi.csv";
        ofstream foutComenzi(caleFisierComenzi, ios::app);
        foutComenzi << comanda.toCSV() << "\n";
        foutComenzi.close();

        actualizeazaStocuri(idProduseComandate);

        cout << "\nComanda a fost adaugata cu succes!\n";
        if (reducere > 0) {
            cout << "Ai primit o reducere de " << reducere * 100 << "%! Costul final este: " << costTotal << " lei.\n";
        }
    }

    void afiseaza() {
        string caleFisier = folder + "/comenzi.csv";

        if (esteFisierGol(caleFisier)) {
            cout << "Nu exista comenzi de afisat (fisierul comenzi.csv este gol).\n";
            return;
        }

        ifstream fin(caleFisier);
        string linie;

        cout << "\n=== COMENZI ===\n";
        cout << string(50, '=') << "\n\n";

        while (getline(fin, linie)) {
            stringstream ss(linie);
            string idClient, numeClient, costTotal, produseIds;

            if (!getline(ss, idClient, ',') || idClient.empty()) continue;
            if (!getline(ss, numeClient, ',') || numeClient.empty()) continue;
            if (!getline(ss, costTotal, ',') || costTotal.empty()) continue;
            if (!getline(ss, produseIds)) continue;

            cout << "Client: " << numeClient << "\n";
            cout << "Cost Total: " << costTotal << " lei\n";
            cout << "Produse:\n";

            stringstream ssProducts(produseIds);
            string idProdus;
            while (getline(ssProducts, idProdus, ';')) {
                int id;
                try { //Excpetions
                    id = stoi(idProdus);
                } catch (const invalid_argument& e) {
                    cout << "Eroare: ID produs invalid: " << idProdus << "\n";
                    continue;
                }
                auto it = find_if(produse.begin(), produse.end(),
                                  [id](const Produs& p) { return p.getId() == id; });
                if (it != produse.end()) {
                    cout << "  - " << it->getNume() << " (" << it->getPret() << " lei)\n";
                }
            }
            cout << string(50, '-') << "\n";
        }

        fin.close();
    }

};



#endif //CAFEA_FUNCTIONSCOMENZI_H