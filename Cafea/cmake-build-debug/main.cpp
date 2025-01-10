#include "Decision.h"
#include "Angajat.h"
#include "FunctionsProduse.h"
#include "FunctionsIngrediente.h"
#include "FunctionsComenzi.h"
#include "FunctionsEvenimente.h"
#include "DecisionsE.h"

int main() {
    char decizie;
    char decizie_personal;
    char decizie_stocuri;
    char decizie_produse;
    char decizie_ingrediente;
    char decizie_comenzi;
    char decizie_evenimente;
    char decizie_raport;

    bool going=false;
    bool going_personal;
    bool going_stocuri;
    bool going_produse;
    bool going_ingrediente;
    bool going_comenzi;
    bool going_evenimente;
    bool going_raport;
    string folder;
    string limba;


    cout<<"Bine ai venit!/Welcome!\n";

    while(true) {
        cout << "Alege limba/Choose your language: romanian/english\n";
        cin >> limba;
        if (limba == "romanian") {
            alegeriOras();
            cin >> folder;
            if (folder == "bucuresti" || folder == "iasi" || folder == "cluj" || folder == "brasov" ||
                folder == "timisoara")
                going = true;
            else if (folder == "q")
                break;
            else if (folder == "r")
                rapoarte();
            else
                cout << "Oras Invalid\n";
            while (going) {
                cout << "Te alfi in sistemul cafenelei din " << folder << endl;
                welcome();
                cin >> decizie;

                if (decizie == 'p') {
                    going_personal = true;
                    while (going_personal) {
                        alegeriPersonal();
                        cin >> decizie_personal;
                        if (decizie_personal == '+')
                            Angajat::introduAngajat(folder + "/angajati.csv");
                        else if (decizie_personal == '-') {
                            Angajat::stergeAngajat(folder + "/angajati.csv");
                        } else if (decizie_personal == 'a')
                            Angajat::afiseazaAngajati(folder + "/angajati.csv");
                        else if (decizie_personal == 'g') {
                            Angajat::gestioneazaProgramul(folder + "/angajati.csv");
                        } else if (decizie_personal == 'm') {
                            cout << "Ai revenit la meniu\n";
                            going_personal = false;
                        } else cout << "Optiune Invalida\n";
                    }
                } else if (decizie == 's') {
                    going_stocuri = true;
                    while (going_stocuri) {
                        alegeriStocuri();
                        cin >> decizie_stocuri;
                        if (decizie_stocuri == 'p') {
                            SistemProdus sistemP(folder + "/produse.csv");
                            going_produse = true;
                            while (going_produse) {
                                alegeriProduse();
                                cin >> decizie_produse;
                                if (decizie_produse == '+')
                                    sistemP.adaugaProdus(folder + "/produse.csv");
                                else if (decizie_produse == '-')
                                    sistemP.eliminaProdus(folder + "/produse.csv");
                                else if (decizie_produse == 'a')
                                    sistemP.afiseazaProduse();
                                else if (decizie_produse == 'e') {
                                    sistemP.modificaPretProdus(folder + "/produse.csv");
                                } else if (decizie_produse == 'm')
                                    going_produse = false;
                                else cout << "Optiune Invalida\n";
                            }
                        } else if (decizie_stocuri == 'i') {
                            SistemIngrediente sistemI(folder + "/ingrediente.csv");
                            going_ingrediente = true;
                            while (going_ingrediente) {
                                alegeriIngrediente();
                                cin >> decizie_ingrediente;
                                if (decizie_ingrediente == 'n')sistemI.adaugaIngredient(folder + "/ingrediente.csv");
                                else if (decizie_ingrediente == 's')
                                    sistemI.eliminaIngredient(folder + "/ingrediente.csv");
                                else if (decizie_ingrediente == '+')sistemI.modificaStoc(folder + "/ingrediente.csv");
                                else if (decizie_ingrediente == 'a')sistemI.afiseazaListaIngrediente();
                                else if (decizie_ingrediente == 'm')going_ingrediente = false;
                                else cout << "Optiune Invalida\n";
                            }
                        } else if (decizie_stocuri == 'm') {
                            cout << "Ai revenit la meniu\n";
                            going_stocuri = false;
                        } else cout << "Optiune Invalida\n";

                    }

                } else if (decizie == 'c') {
                    GestiuneComenzi gestiuneC(folder);
                    going_comenzi = true;
                    while (going_comenzi) {
                        alegeriComenzi();
                        cin >> decizie_comenzi;
                        if (decizie_comenzi == 'a')gestiuneC.afiseaza();
                        else if (decizie_comenzi == '+')gestiuneC.adauga();
                        else if (decizie_comenzi == '?') {
                            cout << "Pentru a deveni client fidel al cafenelei din "
                                 << folder << " trebuie sa realizezi aceste lucruri: \n";
                            reguliClientFidel();
                        } else if (decizie_comenzi == 'm') {
                            cout << "Ai revenit la meniu\n";
                            going_comenzi = false;
                        } else cout << "Optiune Invalida\n";
                    }
                } else if (decizie == 'e') {
                    GestiuneEvenimente gestiuneE(folder);
                    going_evenimente = true;
                    while (going_evenimente) {
                        alegeriEvenimente();
                        cin >> decizie_evenimente;
                        if (decizie_evenimente == 'a')gestiuneE.afiseaza();
                        else if (decizie_evenimente == '+')gestiuneE.adauga();
                        else if (decizie_evenimente == 'm') {
                            cout << "Ai revenit la meniu\n";
                            going_evenimente = false;
                        } else cout << "Optiune Invalida\n";
                    }

                } else if (decizie == 'r') {
                    going_raport = true;
                    while (going_raport) {
                        alegeriRaport();
                        cin >> decizie_raport;
                        if (decizie_raport == 'a') {
                            rapoarte();
                        } else if (decizie_raport == 'q') {
                            Angajat::calculeazaCosturiAngajati(folder + "/angajati.csv");
                            ifstream fisierIn("raport.csv");
                            int id = 1;

                            if (fisierIn.is_open()) {
                                string linie;
                                while (getline(fisierIn, linie)) {
                                    id++;
                                }
                                fisierIn.close();
                            }

                            ofstream fisierOut("raport.csv", ios::app);

                            if (fisierOut.is_open()) {
                                fisierOut << id << ","
                                          << VENIT_COMENZI << ","
                                          << VENIT_EVENIMENTE << ","
                                          << COSTURI_ANGAJATI << ","
                                          << COSTURI_RESTOCK << ","
                                          << folder << endl;
                                fisierOut.close();
                                cout << "Ziua " << id << " a fost finalizata\n";
                                cout << "Venituri din comenzi: " << VENIT_COMENZI << " LEI" << endl;
                                cout << "Venituri din evenimente: " << VENIT_EVENIMENTE << " LEI" << endl;
                                cout << "Costuri angajati: " << COSTURI_ANGAJATI << " LEI" << endl;
                                cout << "Costuri restock: " << COSTURI_RESTOCK << " LEI" << endl;
                                going = false;
                                VENIT_EVENIMENTE = 0;
                                VENIT_COMENZI = 0;
                                COSTURI_ANGAJATI = 0;
                                COSTURI_RESTOCK = 0;
                                ofstream fisierC(folder + "/comenzi.csv", ios::trunc);
                                ofstream fisierE(folder + "/evenimente.csv", ios::trunc);

                                if (fisierC.is_open() && fisierE.is_open()) {
                                    cout << "Fisierele au fost golite cu succes!" << endl;
                                    fisierC.close();
                                    fisierE.close();
                                } else {
                                    cout << "Nu am putut deschide fisierele." << endl;
                                }

                                break;
                            } else
                                cout << "Eroare";

                        } else if (decizie_raport == 'm') {
                            cout << "Ai revenit la meniu\n";
                            going_raport = false;
                        } else cout << "Optiune Invalida";
                    }
                } else cout << "Optiune Invalida\n";

            }
        }
        else if(limba=="english"){
            cityChoices();
            cin >> folder;
            string path = limba + "/" + folder + "/";

            if (folder == "bucuresti" || folder == "iasi" || folder == "cluj" || folder == "brasov" ||
                folder == "timisoara")
                going = true;
            else if (folder == "q")
                break;
            else if (folder == "r")
                rapoarteE();
            else
                cout << "Invalid city\n";

            while (going) {
                cout << "You are in the coffee shop system in " << folder << endl;
                welcomeE();
                cin >> decizie;

                if (decizie == 'p') {
                    going_personal = true;
                    while (going_personal) {
                        personalChoices();
                        cin >> decizie_personal;
                        if (decizie_personal == '+')
                            Angajat::introduAngajat(path + "angajati.csv");
                        else if (decizie_personal == '-') {
                            Angajat::stergeAngajat(path + "angajati.csv");
                        } else if (decizie_personal == 'a')
                            Angajat::afiseazaAngajati(path + "angajati.csv");
                        else if (decizie_personal == 'g') {
                            Angajat::gestioneazaProgramul(path + "angajati.csv");
                        } else if (decizie_personal == 'm') {
                            cout << "You have returned to the menu\n";
                            going_personal = false;
                        } else cout << "Invalid option\n";
                    }
                } else if (decizie == 's') {
                    going_stocuri = true;
                    while (going_stocuri) {
                        stockChoices();
                        cin >> decizie_stocuri;
                        if (decizie_stocuri == 'p') {
                            SistemProdus sistemP(path + "produse.csv");
                            going_produse = true;
                            while (going_produse) {
                                productChoices();
                                cin >> decizie_produse;
                                if (decizie_produse == '+')
                                    sistemP.adaugaProdus(path + "produse.csv");
                                else if (decizie_produse == '-')
                                    sistemP.eliminaProdus(path + "produse.csv");
                                else if (decizie_produse == 'a')
                                    sistemP.afiseazaProduse();
                                else if (decizie_produse == 'e') {
                                    sistemP.modificaPretProdus(path + "produse.csv");
                                } else if (decizie_produse == 'm')
                                    going_produse = false;
                                else cout << "Invalid option\n";
                            }
                        } else if (decizie_stocuri == 'i') {
                            SistemIngrediente sistemI(path + "ingrediente.csv");
                            going_ingrediente = true;
                            while (going_ingrediente) {
                                ingredientChoices();
                                cin >> decizie_ingrediente;
                                if (decizie_ingrediente == 'n')
                                    sistemI.adaugaIngredient(path + "ingrediente.csv");
                                else if (decizie_ingrediente == 's')
                                    sistemI.eliminaIngredient(path + "ingrediente.csv");
                                else if (decizie_ingrediente == '+')
                                    sistemI.modificaStoc(path + "ingrediente.csv");
                                else if (decizie_ingrediente == 'a')
                                    sistemI.afiseazaListaIngrediente();
                                else if (decizie_ingrediente == 'm')
                                    going_ingrediente = false;
                                else cout << "Invalid option\n";
                            }
                        } else if (decizie_stocuri == 'm') {
                            cout << "You have returned to the menu\n";
                            going_stocuri = false;
                        } else cout << "Invalid option\n";

                    }
                } else if (decizie == 'c') {
                    GestiuneComenzi gestiuneC(path);
                    going_comenzi = true;
                    while (going_comenzi) {
                        orderChoices();
                        cin >> decizie_comenzi;
                        if (decizie_comenzi == 'a')
                            gestiuneC.afiseaza();
                        else if (decizie_comenzi == '+')
                            gestiuneC.adauga();
                        else if (decizie_comenzi == '?') {
                            cout << "To become a loyal customer of the coffee shop in "
                                 << folder << " you need to do the following: \n";
                            loyaltyProgramRules();
                        } else if (decizie_comenzi == 'm') {
                            cout << "You have returned to the menu\n";
                            going_comenzi = false;
                        } else cout << "Invalid option\n";
                    }
                } else if (decizie == 'e') {
                    GestiuneEvenimente gestiuneE(path);
                    going_evenimente = true;
                    while (going_evenimente) {
                        eventChoices();
                        cin >> decizie_evenimente;
                        if (decizie_evenimente == 'a')
                            gestiuneE.afiseaza();
                        else if (decizie_evenimente == '+')
                            gestiuneE.adauga();
                        else if (decizie_evenimente == 'm') {
                            cout << "You have returned to the menu\n";
                            going_evenimente = false;
                        } else cout << "Invalid option\n";
                    }
                } else if (decizie == 'r') {
                    going_raport = true;
                    while (going_raport) {
                        reportChoices();
                        cin >> decizie_raport;
                        if (decizie_raport == 'a') {
                            rapoarteE();
                        } else if (decizie_raport == 'q') {
                            Angajat::calculeazaCosturiAngajati(path + "angajati.csv");
                            ifstream fisierIn("raport.csv");
                            int id = 1;

                            if (fisierIn.is_open()) {
                                string linie;
                                while (getline(fisierIn, linie)) {
                                    id++;
                                }
                                fisierIn.close();
                            }

                            ofstream fisierOut("raport.csv", ios::app);

                            if (fisierOut.is_open()) {
                                fisierOut << id << ","
                                          << VENIT_COMENZI << ","
                                          << VENIT_EVENIMENTE << ","
                                          << COSTURI_ANGAJATI << ","
                                          << COSTURI_RESTOCK << ","
                                          << folder << endl;
                                fisierOut.close();
                                cout << "Day " << id << " has been completed\n";
                                cout << "Order revenues: " << VENIT_COMENZI << " LEI" << endl;
                                cout << "Event revenues: " << VENIT_EVENIMENTE << " LEI" << endl;
                                cout << "Employee costs: " << COSTURI_ANGAJATI << " LEI" << endl;
                                cout << "Restock costs: " << COSTURI_RESTOCK << " LEI" << endl;
                                going = false;
                                VENIT_EVENIMENTE = 0;
                                VENIT_COMENZI = 0;
                                COSTURI_ANGAJATI = 0;
                                COSTURI_RESTOCK = 0;
                                ofstream fisierC(path + "comenzi.csv", ios::trunc);
                                ofstream fisierE(path + "evenimente.csv", ios::trunc);

                                if (fisierC.is_open() && fisierE.is_open()) {
                                    cout << "Files have been successfully emptied!" << endl;
                                    fisierC.close();
                                    fisierE.close();
                                } else {
                                    cout << "Unable to open the files." << endl;
                                }

                                break;
                            } else
                                cout << "Error";
                        } else if (decizie_raport == 'm') {
                            cout << "You have returned to the menu\n";
                            going_raport = false;
                        } else cout << "Invalid option";
                    }
                } else cout << "Invalid option\n";
            }
        }

        else cout<<"Error\n";




    }

    return 0;
}
