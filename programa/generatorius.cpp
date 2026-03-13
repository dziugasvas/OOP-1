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

    failas.close();

    cout << "Failas sugeneruotas: " << failoPavadinimas << endl;
}