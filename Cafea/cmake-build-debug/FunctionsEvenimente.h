

#ifndef CAFEA_FUNCTIONSEVENIMENTE_H
#define CAFEA_FUNCTIONSEVENIMENTE_H

#include <unordered_map>
#include "FunctionsComenzi.h"

double VENIT_EVENIMENTE=0.0;

//clase si obiecte
class Eveniment {
private:
    int id;
    string nume;
    string descriere;
    double costSuplimentar;
    double costProduse;
    vector<int> idProduse;

public:
    //constructor
    Eveniment() : id(0), costSuplimentar(0), costProduse(0) {}
    //getters setters
    void setId(int id) { this->id = id; }
    void setNume(const string& nume) { this->nume = nume; }
    void setDescriere(const string& descriere) { this->descriere = descriere; }
    void setCostSuplimentar(double cost) { this->costSuplimentar = cost; }
    void setCostProduse(double cost) { this->costProduse = cost; }

    double getCostProduse(){ return costProduse; }



    void adaugaProdus(int idProdus, double pret) {
        idProduse.push_back(idProdus);
        costProduse += pret;
    }

    string toCSV() const {
        stringstream ss;
        ss << id << "," << nume << "," << descriere << "," << costSuplimentar << "," << costProduse << ",";
        for (size_t i = 0; i < idProduse.size(); ++i) {
            ss << idProduse[i];
            if (i < idProduse.size() - 1) ss << ";";
        }
        return ss.str();
    }
};
//mostenire
class GestiuneEvenimente : public Gestiune {
private:
    vector<Produs> produse;
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

    bool esteFisierGol(const string& caleFisier) {
        ifstream fisier(caleFisier, ios::ate);
        return fisier.tellg() == 0;
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
    GestiuneEvenimente(const string& folderPath) : ultimulId(0), folder(folderPath) {
        incarcaProduse();
    }
//polimorfism
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

                                double costRestock = restockAmount * pretRestock;
                                COSTURI_RESTOCK += costRestock;

                                cout << "Restocare pentru ingredientul: " << ingredient
                                     << " (+" << restockAmount << " unitati, stoc actual: "
                                     << ing[4] << ")\n";
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

    void adauga() {
        Eveniment eveniment;

        cout << "Introduceti numele evenimentului (sau tastati 'x' pentru a anula): ";
        string numeEveniment, descriereEveniment;
        cin.ignore();
        getline(cin, numeEveniment);

        if (numeEveniment == "x") {
            cout << "\nEvenimentul a fost anulat.\n";
            return;
        }

        cout << "Introduceti descrierea evenimentului (sau tastati 'x' pentru a anula): ";
        getline(cin, descriereEveniment);

        if (descriereEveniment == "x") {
            cout << "\nEvenimentul a fost anulat.\n";
            return;
        }

        eveniment.setNume(numeEveniment);
        eveniment.setDescriere(descriereEveniment);
        eveniment.setId(++ultimulId);

        cout << "\nProduse disponibile:\n";
        for (const auto& p : produse) {
            p.afiseaza();
        }

        cout << "\nIntroduceti ID-urile produselor (tastati 'x' pentru a anula sau 0 pentru a termina):\n";
        vector<int> idProduseComandate;
        bool evenimentValid = true;
        while (true) {
            string input;
            cout << "ID produs: ";
            cin >> input;

            if (input == "x") {
                cout << "\nEvenimentul a fost anulat.\n";
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
                        cout << "Nu exista in sistem ingredientul:  " << ingredient << ". Evenimentul va fi anulat.\n";
                        ingredienteDisponibile = false;
                        break;
                    }
                }

                if (ingredienteDisponibile) {
                    eveniment.adaugaProdus(idProdus, it->getPret());
                    idProduseComandate.push_back(idProdus);
                } else {
                    evenimentValid = false;
                    break;
                }
            } else {
                cout << "Produs invalid!\n";
            }
        }

        if (idProduseComandate.empty()) {
            cout << "\nNu au fost selectate produse. Evenimentul a fost anulat.\n";
            return;
        }

        double costSuplimentar;
        do {
            cout << "Introduceti costurile suplimentare pentru eveniment: ";
            cin >> costSuplimentar;
        } while (!esteDoubleValid(costSuplimentar));
        VENIT_EVENIMENTE=VENIT_EVENIMENTE+costSuplimentar;
        eveniment.setCostSuplimentar(costSuplimentar);

        int temp=eveniment.getCostProduse();
        VENIT_EVENIMENTE=VENIT_EVENIMENTE+temp;


        string caleFisierEvenimente = folder + "/evenimente.csv";
        ofstream fout(caleFisierEvenimente, ios::app);
        fout << eveniment.toCSV() << "\n";
        fout.close();

        actualizeazaStocuri(idProduseComandate);

        cout << "\nEvenimentul a fost adaugat cu succes!\n";
    }

    void afiseaza() {
        string caleFisier = folder + "/evenimente.csv";

        if (esteFisierGol(caleFisier)) {
            cout << "Nu exista evenimente de afisat (fisierul evenimente.csv este gol).\n";
            return;
        }

        ifstream fin(caleFisier);
        string linie;

        cout << "\n=== EVENIMENTE ===\n";
        cout << string(50, '=') << "\n\n";

        while (getline(fin, linie)) {
            stringstream ss(linie);
            string idEveniment, numeEveniment, descriereEveniment, costSuplimentar, costProduse, produseIds;

            if (!getline(ss, idEveniment, ',') || idEveniment.empty()) continue;
            if (!getline(ss, numeEveniment, ',') || numeEveniment.empty()) continue;
            if (!getline(ss, descriereEveniment, ',') || descriereEveniment.empty()) continue;
            if (!getline(ss, costSuplimentar, ',') || costSuplimentar.empty()) continue;
            if (!getline(ss, costProduse, ',') || costProduse.empty()) continue;
            if (!getline(ss, produseIds)) continue;

            cout << "Eveniment: " << numeEveniment << "\n";
            cout << "Descriere: " << descriereEveniment << "\n";
            cout << "Cost Suplimentar: " << costSuplimentar << " lei\n";
            cout << "Cost Produse: " << costProduse << " lei\n";
            cout << "Produse:\n";

            stringstream ssProducts(produseIds);
            string idProdus;
            unordered_map<string, int> produseFrecventa;

            while (getline(ssProducts, idProdus, ';')) {
                int id;
                try { //exceptions
                    id = stoi(idProdus);
                } catch (const invalid_argument& e) {
                    cout << "Eroare: ID produs invalid: " << idProdus << "\n";
                    continue;
                }
                auto it = find_if(produse.begin(), produse.end(),
                                  [id](const Produs& p) { return p.getId() == id; });
                if (it != produse.end()) {
                    produseFrecventa[it->getNume()] += 1;
                }
            }

            for (const auto& produs : produseFrecventa) {
                cout << produs.second << " x " << produs.first
                     << " (" << produs.second * (find_if(produse.begin(), produse.end(),
                                                         [produs](const Produs& p) { return p.getNume() == produs.first; }))->getPret() << " lei)\n";
            }

            cout << string(50, '-') << "\n";
        }

        fin.close();
    }



};




#endif //CAFEA_FUNCTIONSEVENIMENTE_H
