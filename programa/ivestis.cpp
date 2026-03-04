#include "ivestis.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::getline;
using std::stringstream;

void inputas(vector<Studentas>& grupe) {
    int ii = 0;

    while (true) {
        Studentas A;
        ii++;

        cout << "Iveskite " << ii << "-ojo studento varda ('Baigti' - baigti ivedima): ";
        cin >> A.vardas;

        if (A.vardas == "Baigti") {
            break;
        }

        cout << "Iveskite " << ii << "-ojo studento pavarde: ";
        cin >> A.pavarde;

        while (true) {
            int nd;
            cout << "Iveskite " << ii << "-ojo studento " << A.paz.size() + 1 << "-aji namu darbo ivertinima (1-10, 0 - baigti): ";
            cin >> nd;

            if (!cin.fail() && nd == 0) {
                break;
            }

            if (!cin.fail() && nd >= 1 && nd <= 10) {
                A.paz.push_back(nd);
            } else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ivedete neteisingai, bandykite dar karta! (1-10, 0 - baigti)" << endl;
            }
        }

        while (A.paz.empty()) {
            int nd;
            cout << "Neivestas nei vienas ND. Iveskite bent viena pazymi (1-10): ";
            cin >> nd;

            if (!cin.fail() && nd >= 1 && nd <= 10) {
                A.paz.push_back(nd);
                break;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ivedete neteisingai, bandykite dar karta! (1-10)" << endl;
        }

        while (true) {
            cout << "Iveskite studento egzamino rezultata (0-10): ";
            cin >> A.egz;

            if (!cin.fail() && A.egz >= 0 && A.egz <= 10) {
                break;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ivedete neteisingai, bandykite dar karta! (0-10)" << endl;
        }

        A.rez = 0;
        grupe.push_back(A);
    }
}

void nuskaitymas(vector<Studentas>& grupe, string failas) {
    ifstream input(failas);

    if (!input.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    grupe.clear();

    string eilute;
    getline(input, eilute);

    while (getline(input, eilute)) {
        if (eilute.empty()) {
            continue;
        }

        stringstream ss(eilute);
        Studentas s;

        ss >> s.vardas >> s.pavarde;

        if (s.vardas.empty() || s.pavarde.empty()) {
            continue;
        }

        vector<int> paz;
        int x;

        while (ss >> x) {
            paz.push_back(x);
        }

        if (paz.empty()) {
            continue;
        }

        s.egz = paz.back();
        paz.pop_back();
        s.paz = paz;
        s.rez = 0;

        grupe.push_back(s);
    }

    cout << "Nuskaityta studentu: " << grupe.size() << endl;
}