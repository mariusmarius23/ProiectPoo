//
// Created by user on 1/3/2025.
//

#ifndef CAFEA_GESTIUNE_H
#define CAFEA_GESTIUNE_H
#include "FunctionsProduse.h"
#include "FunctionsComenzi.h"
#include "Functions.h"
#include "FunctionsIngrediente.h"
//clase si obiecte
class Gestiune {
public:

    //Abstractizare
    virtual void actualizeazaStocuri(const vector<int>& idProduse)=0;

    virtual bool verificaDisponibilitateaIngredientului(const string& ingredient) {
        string caleFisierIngrediente="unknown";
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

    virtual void adauga(){
        cout<<"Nimic de adaugat";
    }

    virtual void afiseaza(){
        cout<<"Nimic de afisat";
    }

    //destructor
    virtual ~Gestiune() {}

};



#endif //CAFEA_GESTIUNE_H
