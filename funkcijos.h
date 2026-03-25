#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "Studentas.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

void generuotiFaila(const std::string& failoPavadinimas, int kiekStudentu, int ndKiekis);
void outputas(const std::vector<Studentas>& grupe, char pasirinkimas);
void spausdinimas(const std::vector<Studentas>& grupe, char pasirinkimas);
void inputas(std::vector<Studentas>& grupe);
// void nuskaitymas(std::vector<Studentas>& grupe, std::string failas);
double mediana(const std::vector<int>& paz);
double vidurkis(const std::vector<int>& paz);
void rusiavimas(std::vector<Studentas>& grupe, char budas);
void padalintiStudentus(const std::vector<Studentas>& grupe, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietakai, char budas);
void spausdintiIFaila(const std::vector<Studentas>& grupe, const std::string& failoPavadinimas, char budas);
void tyrimas1(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis);
void tyrimas2(const std::string& failoPavadinimas, char budas);

template <typename konteineris>
void nuskaitymas(konteineris& grupe, string failas) {
    ifstream input(failas);

    try {
        if (!input.is_open()) {
            throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
        }
    } catch (std::exception& e) {
        cout << "Klaida: " << e.what() << endl;
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


#endif
