#include "testavimas.h"
#include "Studentas.h"
#include "ivestis.h"
#include "skaiciavimai.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <cstdlib>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ofstream;

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