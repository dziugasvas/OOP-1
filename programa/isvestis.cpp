#include "isvestis.h"
#include "skaiciavimai.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::ofstream;

void outputas(const vector<Studentas>& grupe, char pasirinkimas) {
    cout << std::fixed << std::setprecision(2);

    cout << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";

    if (pasirinkimas == 'm') {
        cout << setw(15) << "Galutinis (Med.)" << endl;
    } else {
        cout << setw(15) << "Galutinis (Vid.)" << endl;
    }

    cout << string(50, '-') << endl;

    for (const auto& A : grupe) {
        cout << left << setw(15) << A.vardas << left << setw(20) << A.pavarde;
        double nd_rez = (pasirinkimas == 'm') ? mediana(A.paz) : vidurkis(A.paz);
        double galutinis = 0.4 * nd_rez + 0.6 * A.egz;
        cout << setw(15) << galutinis << endl;
    }
}

void spausdinimas(const vector<Studentas>& grupe, char pasirinkimas) {
    ofstream file("rezultatai.txt");

    if (!file.is_open()) {
        cout << "Nepavyko sukurti failo!" << endl;
        return;
    }

    file << std::fixed << std::setprecision(2);
    file << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";

    if (pasirinkimas == 'm') {
        file << setw(15) << "Galutinis (Med.)" << endl;
    } else {
        file << setw(15) << "Galutinis (Vid.)" << endl;
    }

    file << string(50, '-') << endl;

    for (const auto& A : grupe) {
        file << left << setw(15) << A.vardas << left << setw(20) << A.pavarde;
        double nd_rez = (pasirinkimas == 'm') ? mediana(A.paz) : vidurkis(A.paz);
        double galutinis = 0.4 * nd_rez + 0.6 * A.egz;
        file << setw(15) << galutinis << endl;
    }

    cout << "Rezultatai irasyti i faila 'rezultatai.txt'" << endl;
}