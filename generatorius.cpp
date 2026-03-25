#include "generatorius.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using std::ofstream;
using std::cout;
using std::endl;
using std::setw;
using std::left;

void generuotiFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis) {

    ofstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        cout << "Nepavyko sukurti failo!" << endl;
        return;
    }
    
    failas << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";

    for (int i = 0; i < ndKiekis; i++) {
        failas << left << setw(5) << ("ND" + std::to_string(i + 1));
    }

    failas << left << setw(5) << "Egz." << endl;

    for (int i = 0; i < studentuKiekis; i++) {
        failas << left << setw(20) << ("Vardas" + std::to_string(i + 1)) << left << setw(20) << ("Pavarde" + std::to_string(i + 1));

        for (int j = 0; j < ndKiekis; j++) {
            int paz = rand() % 10 + 1;
            failas << left << setw(5) << paz;
        }

        int egz = rand() % 10 + 1;
        failas << left << setw(5) << egz << endl;
    }

    failas.close();

    cout << "Failas sugeneruotas: " << failoPavadinimas << endl;
}