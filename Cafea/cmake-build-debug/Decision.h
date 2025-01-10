//
// Created by user on 12/25/2024.
//

#ifndef CAFEA_DECISION_H
#define CAFEA_DECISION_H
#include <iostream>
using namespace std;

void alegeriPersonal(){
    cout<<"Pentru a adauga angajati tasteaza '+'\n";
    cout<<"Pentru a sterge angajati tasteaza '-'\n";
    cout<<"Pentru a gestiona programul unui angajat tasteaza 'g'\n";
    cout<<"Pentru a afisa toti angajatii tasteaza 'a'\n";
    cout<<"Pentru a reveni la meniu tasteaza 'm'\n";
}
void welcome(){
    cout<<"Pentru a organiza personalul tasteaza 'p'\n";
    cout<<"Pentru a gestiona stocurile tasteaza 's'\n";
    cout<<"Pentru a organiza inregistrarile de comenzi tasteaza 'c'\n";
    cout<<"Pentru a organiza evenimentele speciale tasteaza 'e'\n";
    cout<<"Pentru a primi raportul sau a vizializa alte raporturi tasteaza 'r'\n";



}

void alegeriStocuri(){
    cout<<"Pentru a gestiona produsele tasteaza 'p'\n";
    cout<<"Pentru a gestiona ingredientele tasteaza 'i'\n";
    cout<<"Pentru a reveni la meniu tasteaza 'm'\n";
}

void alegeriProduse(){
    cout<<"Pentru a adauga un produs nou, tasteaza '+'\n";
    cout<<"Pentru a elimina un produs, tasteaza '-'\n";
    cout<<"Pentru a afisa lista de produse tasteaza 'a'\n";
    cout<<"Pentru a modifica pretul unui produs tasteaza 'e'\n";
    cout<<"Pentru a te intoarce la meniul de stocuri tasteaza 'm'\n";
}

void alegeriIngrediente(){
    cout<<"Pentru a adauga un ingredient nou tasteaza 'n'\n";
    cout<<"Pentru a sterge un ingredient tasteaza 's'\n";
    cout<<"Pentru a comanda stocuri noi de ingrediente tasteaza '+'\n";
    cout<<"Pentru a afisa ingredientele tasteaza 'a'\n";
    cout<<"Pentru a te intoarce la meniul de stocuri tasteaza 'm'\n";

}

void alegeriOras(){
    cout<<"Pentru a alege sa gestionezi cafeneaua din Bucuresti, introduce 'bucuresti'\n";
    cout<<"Pentru a alege sa gestionezi cafeneaua din Iasi, introduce 'iasi'\n";
    cout<<"Pentru a alege sa gestionezi cafeneaua din Cluj-Napoca, introduce 'cluj'\n";
    cout<<"Pentru a alege sa gestionezi cafeneaua din Timisoara, introduce 'timisoara'\n";
    cout<<"Pentru a alege sa gestionezi cafeneaua din Brasov, introduce 'brasov'\n";
    cout<<"Pentru a vedea rapoartele tasteaza 'r'\n";
    cout<<"Pentru a iesi din program tasteaza 'q'\n";
}

void alegeriComenzi(){
    cout<<"Pentru a afisa comenzile tasteaza 'a'\n";
    cout<<"Pentru a inregistra o comanda noua tasteaza '+'\n";
    cout<<"Pentru a afisa regulile de a deveni client fidel tasteaza '?'\n";
    cout<<"Pentru a reveni la meniu tasteaza 'm'\n";

}

void reguliClientFidel (){
    cout<<"-5% reducere din costul total pentru clientii cu 5+ comenzi\n";
    cout<<"-10% reducere din costul total pentru clientii cu 10+ comenzi\n";
    cout<<"-15% reducere din costul total pentru clientii cu peste 15 comenzi\n";
}

void alegeriEvenimente(){
    cout<<"Pentru a creea un eveniment special tasteaza '+'\n";
    cout<<"Pentru a afisa evenimentele tasteaza 'a'\n";
    cout<<"Pentru a reveni la meniu tasteaza 'm'\n";

}

void alegeriRaport(){
    cout<<"Pentru a vizualiza un raport trecut tasteaza 'a'\n";
    cout<<"Pentru a incheia ziua si sa primesti raportul tasteaza 'q'\n";
    cout<<"Pentru a reveni la meniu tasteaza 'm'\n";
}

#endif //CAFEA_DECISION_H
