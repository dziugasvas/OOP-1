#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "Studentas.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <list>
#include <iomanip>

void generuotiFaila(const std::string& failoPavadinimas, int kiekStudentu, int ndKiekis);
void outputas(const std::vector<Studentas>& grupe, char pasirinkimas);
void spausdinimas(const std::vector<Studentas>& grupe, char pasirinkimas);
void inputas(std::vector<Studentas>& grupe);
// void nuskaitymas(std::vector<Studentas>& grupe, std::string failas);
double mediana(const std::vector<int>& paz);
double vidurkis(const std::vector<int>& paz);
// void rusiavimas(std::vector<Studentas>& grupe, char budas);
// void padalintiStudentus(const std::vector<Studentas>& grupe, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietakai, char budas);
// void spausdintiIFaila(const std::vector<Studentas>& grupe, const std::string& failoPavadinimas, char budas);
void tyrimas1(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis);
void tyrimas2(const std::string& failoPavadinimas, char budas);

template <typename konteineris>
void nuskaitymas(konteineris& grupe, std::string failas) {
    std::ifstream input(failas);

    try {
        if (!input.is_open()) {
            throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
        }
    } catch (std::exception& e) {
        std::cout << "Klaida: " << e.what() << std::endl;
        return;
    }

    grupe.clear();

    std::string eilute;
    std::getline(input, eilute);

    while (std::getline(input, eilute)) {
        if (eilute.empty()) {
            continue;
        }

        std::stringstream ss(eilute);
        Studentas s;

        ss >> s.vardas >> s.pavarde;

        if (s.vardas.empty() || s.pavarde.empty()) {
            continue;
        }

        std::vector<int> paz;
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

    std::cout << "Nuskaityta studentu: " << grupe.size() << std::endl;
}

template <typename konteineris>
void padalintiStudentus1(const konteineris& grupe, konteineris& vargsiukai, konteineris& kietakai, char budas) {
    vargsiukai.clear();
    kietakai.clear();

    for (const auto& A : grupe) {
        double nd_rez = (budas == 'm') ? mediana(A.paz) : vidurkis(A.paz);
        double galutinis = 0.4 * nd_rez + 0.6 * A.egz;

        if (galutinis < 5.0) {
            vargsiukai.push_back(A);
        } else {
            kietakai.push_back(A);
        }
    }
}

template <typename konteineris>
void rusiavimas(konteineris& grupe, char budas) {
    int kriterijus;
    while (true) {
        std::cout << "Pasirinkite kriteriju pagal kuri norite rusiuoti:" << std::endl;
        std::cout << "1 - Vardas" << std::endl;
        std::cout << "2 - Pavarde" << std::endl;
        std::cout << "3 - Galutinis (vidurkis arba mediana)" << std::endl;
        std::cin >> kriterijus;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Klaida: iveskite skaiciu 1-3" << std::endl;
            continue;
        }

        if (kriterijus == 1 || kriterijus == 2 || kriterijus == 3) {
            break;
        }
        std::cout << "Neteisinga ivestis. Bandykite dar karta!" << std::endl;
    }

    if constexpr (std::is_same_v<konteineris, std::list<Studentas>>) {
        switch (kriterijus) {
            case 1:
                grupe.sort([](const Studentas& A, const Studentas& B) {
                    return A.vardas < B.vardas;
                });
                break;
            case 2:
                grupe.sort([](const Studentas& A, const Studentas& B) {
                    return A.pavarde < B.pavarde;
                });
                break;
            case 3:
                if (budas == 'v') {
                    grupe.sort([](const Studentas& A, const Studentas& B) {
                        double galutinisA = 0.4 * vidurkis(A.paz) + 0.6 * A.egz;
                        double galutinisB = 0.4 * vidurkis(B.paz) + 0.6 * B.egz;
                        return galutinisA > galutinisB;
                    });
                } else {
                    grupe.sort([](const Studentas& A, const Studentas& B) {
                        double galutinisA = 0.4 * mediana(A.paz) + 0.6 * A.egz;
                        double galutinisB = 0.4 * mediana(B.paz) + 0.6 * B.egz;
                        return galutinisA > galutinisB;
                    });
                }
            break;
    }
} else {
    switch (kriterijus) {
        case 1:
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
            return A.vardas < B.vardas;
        });
           break;
        case 2:
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
            return A.pavarde < B.pavarde;
        });
           break;
        case 3:
        if (budas == 'v') {
            std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                double galutinisA = 0.4 * vidurkis(A.paz) + 0.6 * A.egz;
                double galutinisB = 0.4 * vidurkis(B.paz) + 0.6 * B.egz;
                return galutinisA > galutinisB;
            });
        } else {
            std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                double galutinisA = 0.4 * mediana(A.paz) + 0.6 * A.egz;
                double galutinisB = 0.4 * mediana(B.paz) + 0.6 * B.egz;
                return galutinisA > galutinisB;
            });
        }
         break;
        }
    }
}

template <typename konteineris>
void spausdintiIFaila(const konteineris& grupe, const std::string& failoPavadinimas, char budas) {
    std::ofstream failas(failoPavadinimas);

    failas << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(20) << "Galutinis" << std::endl;

    failas << "---------------------------------------------" << std::endl;

    for (const auto& A : grupe) {

        double nd_rez = (budas == 'm') ? mediana(A.paz) : vidurkis(A.paz);
        double galutinis = 0.4 * nd_rez + 0.6 * A.egz;

        failas << std::left << std::setw(15) << A.vardas << std::setw(15) << A.pavarde << std::setw(20) << std::fixed << std::setprecision(2) << galutinis << std::endl;
    }

    failas.close();
}


#endif
