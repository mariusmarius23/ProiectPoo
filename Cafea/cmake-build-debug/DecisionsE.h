//
// Created by user on 1/4/2025.
//

#ifndef CAFEA_DECISIONSE_H
#define CAFEA_DECISIONSE_H

#include <iostream>
using namespace std;

void personalChoices() {
    cout << "To add employees, type '+'\n";
    cout << "To remove employees, type '-'\n";
    cout << "To manage an employee's schedule, type 'g'\n";
    cout << "To display all employees, type 'a'\n";
    cout << "To return to the menu, type 'm'\n";
}

void welcomeE() {
    cout << "To organize personnel, type 'p'\n";
    cout << "To manage stocks, type 's'\n";
    cout << "To manage orders, type 'c'\n";
    cout << "To organize special events, type 'e'\n";
    cout << "To receive reports or view other reports, type 'r'\n";
}

void stockChoices() {
    cout << "To manage products, type 'p'\n";
    cout << "To manage ingredients, type 'i'\n";
    cout << "To return to the menu, type 'm'\n";
}

void productChoices() {
    cout << "To add a new product, type '+'\n";
    cout << "To remove a product, type '-'\n";
    cout << "To display the product list, type 'a'\n";
    cout << "To modify the price of a product, type 'e'\n";
    cout << "To return to the stock menu, type 'm'\n";
}

void ingredientChoices() {
    cout << "To add a new ingredient, type 'n'\n";
    cout << "To remove an ingredient, type 's'\n";
    cout << "To order new stock for ingredients, type '+'\n";
    cout << "To display ingredients, type 'a'\n";
    cout << "To return to the stock menu, type 'm'\n";
}

void cityChoices() {
    cout << "To manage the cafe in Bucharest, enter 'bucuresti'\n";
    cout << "To manage the cafe in Iasi, enter 'iasi'\n";
    cout << "To manage the cafe in Cluj-Napoca, enter 'cluj'\n";
    cout << "To manage the cafe in Timisoara, enter 'timisoara'\n";
    cout << "To manage the cafe in Brasov, enter 'brasov'\n";
    cout << "To view reports, type 'r'\n";
    cout << "To exit the program, type 'q'\n";
}

void orderChoices() {
    cout << "To display orders, type 'a'\n";
    cout << "To register a new order, type '+'\n";
    cout << "To display loyalty program rules, type '?' \n";
    cout << "To return to the menu, type 'm'\n";
}

void loyaltyProgramRules() {
    cout << "-5% discount on the total cost for customers with 5+ orders\n";
    cout << "-10% discount on the total cost for customers with 10+ orders\n";
    cout << "-15% discount on the total cost for customers with over 15 orders\n";
}

void eventChoices() {
    cout << "To create a special event, type '+'\n";
    cout << "To display events, type 'a'\n";
    cout << "To return to the menu, type 'm'\n";
}

void reportChoices() {
    cout << "To view a past report, type 'a'\n";
    cout << "To close the day and receive a report, type 'q'\n";
    cout << "To return to the menu, type 'm'\n";
}

#endif //CAFEA_DECISIONSE_H
