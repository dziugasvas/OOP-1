#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Studentas.h"
#include "skaiciavimai.h"
#include "ivestis.h"
#include "isvestis.h"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

const vector<string> vardai = {"Dovydas", "Matas", "Simonas", "Rokas", "Kajus", "Dziugas", "Virgilijus", "Vitalijus", "Alan", "Aleksas", "Jonas", "Domantas", "Arvydas", "Mantyvdas", "Gvidas"};
const vector<string> pavardes = {"Kazlauskas", "Buzelis", "Sabonis", "Tubelis", "Gudelis", "Macijauskas", "Alekna", "Vanagas", "Butkevicius", "Ulanovas", "Sirvydis", "Jasikevicius", "Jakucionis", "Kleiza", "Jonauskas"};

int main() {
    vector<Studentas> grupe;
    bool veikia = true;

    srand(time(NULL));

    while (veikia) {
        cout << "Pasirinkimu meniu: " << endl;
        cout << "1 - Ivesti studentus ranka" << endl;
        cout << "2 - Generuoti tik pazymius" << endl;
        cout << "3 - Generuoti studentus (vardas/pavarde/pazymiai)" << endl;
        cout << "4 - Nuskaityti studentus is failo" << endl;
        cout << "5 - Spausdinti rezultatus ir baigti" << endl;

        int p;
        cin >> p;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida: iveskite skaiciu 1-5" << endl;
            continue;
        }

        switch (p) {
            case 1:
                inputas(grupe);
                break;

            case 2: {
                int ii = 0;
                int kiek;
                cout << "Iveskite norima namu darbu pazymiu kieki: " << endl;
                cin >> kiek;

                while (cin.fail() || kiek <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Ivedete neteisingai. Iveskite teigiama skaiciu" << endl;
                    cin >> kiek;
                }

                while (true) {
                    Studentas A;
                    ii++;

                    cout << "Iveskite " << ii << "-ojo studento varda ('Baigti' - baigti ivedima): ";
                    cin >> A.vardas;

                    if (A.vardas == "Baigti") break;

                    cout << "Iveskite " << ii << "-ojo studento pavarde: ";
                    cin >> A.pavarde;

                    A.paz.clear();

                    for (int i = 0; i < kiek; i++) {
                        int nd = rand() % 10 + 1;
                        A.paz.push_back(nd);
                    }

                    A.egz = rand() % 10 + 1;
                    A.rez = 0;

                    grupe.push_back(A);

                    cout << "Sugeneruota: " << kiek << " ND pazymiai. Egzamino pazymys = " << A.egz << endl;
                }
                break;
            }

            case 3: {
                int m;
                cout << "Iveskite studentu skaiciu (1-15): ";
                cin >> m;

                while (cin.fail() || m < 1 || m > 15) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisingas skaicius. Iveskite skaiciu nuo 1 iki 15: ";
                    cin >> m;
                }

                int kiek;
                cout << "Iveskite namu darbu pazymiu kieki: ";
                cin >> kiek;

                while (cin.fail() || kiek <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisingas skaicius. Iveskite teigiama skaiciu: ";
                    cin >> kiek;
                }

                for (int i = 0; i < m; i++) {
                    Studentas A;

                    A.vardas = vardai[rand() % vardai.size()];
                    A.pavarde = pavardes[rand() % pavardes.size()];

                    int sum = 0;
                    for (int j = 0; j < kiek; j++) {
                        int nd = rand() % 10 + 1;
                        A.paz.push_back(nd);
                        sum += nd;
                    }

                    A.egz = rand() % 10 + 1;

                    double nd_vid = sum * 1.0 / A.paz.size();
                    A.rez = 0.4 * nd_vid + 0.6 * A.egz;

                    grupe.push_back(A);
                }

                cout << "Sugeneruoti " << m << " studentai." << endl;
                break;
            }

            case 4: {
                string failas;
                cout << "Iveskite failo pavadinima: ";
                cin >> failas;

                auto pradzia = std::chrono::high_resolution_clock::now();
                nuskaitymas(grupe, failas);
                auto laikas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - pradzia).count();

                cout << "Nuskaitymo laikas: " << std::fixed << std::setprecision(3) << laikas << " s" << endl;
                break;
            }

            case 5: {
                char budas;
                cout << "Kaip skaiciuoti galutini? (v - vidurkis, m - mediana): ";
                cin >> budas;

                while (budas != 'v' && budas != 'm') {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisinga ivestis. Iveskite 'v' arba 'm': ";
                    cin >> budas;
                }

                rusiavimas(grupe, budas);

                char kur;
                cout << "Ar norite faila isvesti i terminala (t) ar i faila (f): ";
                cin >> kur;

                while (kur != 't' && kur != 'f') {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisinga ivestis. Iveskite 't' arba 'f': ";
                    cin >> kur;
                }

                if (kur == 'f') {
                    spausdinimas(grupe, budas);
                } else {
                    outputas(grupe, budas);
                }

                veikia = false;
                break;
            }

            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                break;
        }
    }

    return 0;
}