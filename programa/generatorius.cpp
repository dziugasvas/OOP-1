#include "generatorius.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using std::ofstream;
using std::cout;
using std::endl;

void generuotiFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis) {

    ofstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        cout << "Nepavyko sukurti failo!" << endl;
        return;
    }
    
    failas << "Vardas" << " " << "Pavarde";

    for (int i = 0; i < ndKiekis; i++) {
        failas << " " << "ND" << i + 1;
    }

    failas << " " << "Egz." << endl;

    for (int i = 0, i < studentuKiekis; i++) {
        failas << "Vardas" << i + 1<< " " << "Pavarde" << i + 1;

        for (int j = 0; j < ndKiekis; j++) {
            int paz = rand() % 10 + 1;
            failas << " " << paz;
        }

        int egz = rand() % 10 + 1;
        failas << " " << egz << endl;
    }

    failas.close();

    cout << "Failas sugeneruotas: " << failoPavadinimas << endl;
}