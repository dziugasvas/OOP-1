#include "funkcijos.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>

using std::ofstream;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::vector;
using std::string;
using std::right;
using std::sort;
using std::fixed;
using std::setprecision;

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

    try {
        if (!file.is_open()) {
        throw std::runtime_error("Nepavyko sukurti failo");
    }
    } catch (std::exception& e) {
        cout << "Klaida: " << e.what() << endl;
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

void padalintiStudentus(const vector<Studentas>& grupe, vector<Studentas>& vargsiukai, vector<Studentas>& kietakai, char budas) {
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

void spausdintiIFaila(const vector<Studentas>& grupe, const string& failoPavadinimas, char budas) {
    ofstream failas(failoPavadinimas);

    failas << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis" << endl;

    failas << "---------------------------------------------" << endl;

    for (const auto& A : grupe) {

        double nd_rez = (budas == 'm') ? mediana(A.paz) : vidurkis(A.paz);
        double galutinis = 0.4 * nd_rez + 0.6 * A.egz;

        failas << left << setw(15) << A.vardas << setw(15) << A.pavarde << setw(20) << fixed << setprecision(2) << galutinis << endl;
    }

    failas.close();
}

void tyrimas1(const string& failoPavadinimas, int studentuKiekis, int ndKiekis) {
    cout << "Pirmo tyrimo failo kurimas: " << failoPavadinimas << endl;

    auto t1 = std::chrono::high_resolution_clock::now();

    ofstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Klaida: nepavyko sukurti failo!" << endl;
        return;
    }

    failas << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
    for (int i = 0; i < ndKiekis; i++) {
        failas << std::setw(5) << ("ND" + std::to_string(i + 1));
    }
    failas << std::setw(5) << "Egz." << endl;

    for (int i = 0; i < studentuKiekis; i++) {
        failas << std::left << std::setw(20) << ("Vardas" + std::to_string(i + 1)) << std::setw(20) << ("Pavarde" + std::to_string(i + 1));
        for (int j = 0; j < ndKiekis; j++) {
            failas << std::setw(5) << (rand() % 10 + 1);
        }
        failas << std::setw(5) << (rand() % 10 + 1) << endl;
    }

    failas.close();

    auto t2 = std::chrono::high_resolution_clock::now();
    cout << "Failo kurimo laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t2 - t1).count() << " s" << endl;
}

void tyrimas2(const string& failoPavadinimas, char budas) {
    cout << "Antro tyrimo duomenu apdorojimas: " << failoPavadinimas << endl;

    vector<Studentas> grupe;

    auto t_start = std::chrono::high_resolution_clock::now();
    nuskaitymas(grupe, failoPavadinimas);
    auto t2 = std::chrono::high_resolution_clock::now();
    cout << "Nuskaitymo laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t2 - t_start).count() << " s" << endl;

    vector<Studentas> vargsiukai, kietakai;

    auto t3 = std::chrono::high_resolution_clock::now();
    padalintiStudentus(grupe, vargsiukai, kietakai, budas);
    auto t4 = std::chrono::high_resolution_clock::now();
    cout << "Rusiavimo laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t4 - t3).count() << " s" << endl;

    auto t5 = std::chrono::high_resolution_clock::now();
    spausdintiIFaila(vargsiukai, "vargsiukai.txt", budas);
    spausdintiIFaila(kietakai, "kietakai.txt", budas);
    auto t6 = std::chrono::high_resolution_clock::now();
    cout << "Isvedimo laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t6 - t5).count() << " s" << endl;

    cout << "Bendras laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t6 - t_start).count() << " s" << endl;
    cout << "Vargsiukai: " << vargsiukai.size() << " | Kietakai: " << kietakai.size() << endl;
}