#include "skaiciavimai.h"
#include <algorithm>

using std::vector;
using std::sort;
using std::cout;
using std::cin;
using std::endl;

double mediana(const vector<int>& paz) {
    int n = paz.size();

    if (n == 0) {
        return 0.0;
    }

    vector<int> temp = paz;
    sort(temp.begin(), temp.end());

    if (n % 2 != 0) {
        return temp[n / 2];
    } else {
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
}

double vidurkis(const vector<int>& paz) {
    if (paz.empty()) {
        return 0.0;
    }
    int sum = 0;
    for (int x : paz) {
        sum += x;
    }
    return sum * 1.0 / paz.size();
}

void rusiavimas(vector<Studentas>& grupe, char budas) {
    int kriterijus;
    while (true) {
        cout << "Pasirinkite kriteriju pagal kuri norite rusiuoti:" << endl;
        cout << "1 - Vardas" << endl;
        cout << "2 - Pavarde" << endl;
        cout << "3 - Galutinis (vidurkis arba mediana)" << endl;
        cin >> kriterijus;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida: iveskite skaiciu 1-3" << endl;
            continue;
        }

        if (kriterijus == 1 || kriterijus == 2 || kriterijus == 3) {
            break;
        }
        cout << "Neteisinga ivestis. Bandykite dar karta!" << endl;
    }

    switch (kriterijus) {
        case 1:
            sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                return A.vardas < B.vardas;
            });
            break;
        case 2:
            sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                return A.pavarde < B.pavarde;
            });
            break;
        case 3:
            if (budas == 'v') {
                sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                    double galutinisA = 0.4 * vidurkis(A.paz) + 0.6 * A.egz;
                    double galutinisB = 0.4 * vidurkis(B.paz) + 0.6 * B.egz;
                    return galutinisA > galutinisB;
                });
            } else {
                sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                    double galutinisA = 0.4 * mediana(A.paz) + 0.6 * A.egz;
                    double galutinisB = 0.4 * mediana(B.paz) + 0.6 * B.egz;
                    return galutinisA > galutinisB;
                });
            }
            break;
    }
}