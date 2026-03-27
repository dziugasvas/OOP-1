#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Studentas.h"
#include "funkcijos.h"

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
        cout << "5 - Generuoti studentu faila" << endl;
        cout << "6 - Tyrimas 1 (failu kurimu greitis)" << endl;
        cout << "7 - Tyrimas 2 (duomenu apdorojimo greitis)" << endl;
        cout << "8 - Konteineriu tyrimai (vector/list/deque)" << endl;
        cout << "9 - Spausdinti rezultatus" << endl;
        cout << "10 - Baigti darba" << endl;

        int p;
        cin >> p;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida: iveskite skaiciu 1-10" << endl;
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
                cout << "Turimi failai: ";
                system("ls *.txt");
                cin >> failas;

                try {
                    auto pradzia = std::chrono::high_resolution_clock::now();
                    nuskaitymas(grupe, failas);

                    if(!grupe.empty()) {
                        auto laikas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - pradzia).count();

                        cout << "Nuskaitymo laikas: " << std::fixed << std::setprecision(3) << laikas << " s" << endl;
                    }
                } catch (std::exception& e) {
                    cout << "Klaida: " << e.what() << endl;
                }
                break;
            }

            case 5: {
                int kiekStudentu;
                int ndKiekis;

                cout << "Iveskite kiek studentu norite sugeneruoti: ";
                cin >> kiekStudentu;

                while (cin.fail() || kiekStudentu <=0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisinga ivestis. Iveskite teigiama skaiciu: ";
                    cin >> kiekStudentu;
                }

                cout << "Iveskite namu darbu kieki: ";
                cin >> ndKiekis;

                while (cin.fail() || ndKiekis <=0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisinga ivestis. Iveskite teigiama skaiciu: ";
                    cin >> ndKiekis;
                }

                string failoPavadinimas = "studentai" + std::to_string(kiekStudentu) + ".txt";
                generuotiFaila(failoPavadinimas, kiekStudentu, ndKiekis);
                
                grupe.clear();

                nuskaitymas(grupe, failoPavadinimas);

                cout << "Sugeneruotas ir nuskaitytas failas: " << failoPavadinimas << endl;

                break;
            }

            case 6: {

                int ndKiekis;
                cout << "Iveskite ND kieki generuojamuose failuose: ";
                cin >> ndKiekis;

                while (cin.fail() || ndKiekis <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisinga ivestis. Iveskite teigiama skaiciu: ";
                    cin >> ndKiekis;
                }

                vector<int> dydžiai = {1000, 10000, 100000, 1000000, 10000000};
                for (int d : dydžiai) {
                    string fn = "test_" + std::to_string(d) + ".txt";
                    tyrimas1(fn, d, ndKiekis);
                }
                break;
            }

            case 7: {

                char budas;
                cout << "Kaip skaiciuoti galutini? (v - vidurkis, m - mediana): ";
                cin >> budas;

                while (budas != 'v' && budas != 'm') {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisinga ivestis. Iveskite 'v' arba 'm': ";
                    cin >> budas;
                }

                vector<int> dydžiai = {1000, 10000, 100000, 1000000, 10000000};
                for (int d : dydžiai) {
                    string fn = "test_" + std::to_string(d) + ".txt";
                    tyrimas2(fn, budas);
                }
                break;
            }

            case 8: {
                cout << "Konteineriu tyrimai (bus dar prideta)" << endl;
                break;
            }

            case 9: {

                char budas;
                cout << "Kaip skaiciuoti galutini? (v - vidurkis, m - mediana): ";
                cin >> budas;

                while (budas != 'v' && budas != 'm') {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisinga ivestis. Iveskite 'v' arba 'm': ";
                    cin >> budas;
                }

                if (grupe.empty()) {
                    cout << "Nera failu. Pirmiausia iveskite arba nuskaitykite studentus." << endl;
                    break;
                }
                 
                auto start = std::chrono::high_resolution_clock::now();

                rusiavimas(grupe, budas);

                vector<Studentas> vargsiukai;
                vector<Studentas> kietakai;

                auto split_start = std::chrono::high_resolution_clock::now();
                padalintiStudentus1(grupe, vargsiukai, kietakai, budas);
                auto split_end = std::chrono::high_resolution_clock::now();
                
                auto file_start = std::chrono::high_resolution_clock::now();
                spausdintiIFaila(vargsiukai, "vargsiukai.txt", budas);
                spausdintiIFaila(kietakai, "kietakai.txt", budas);
                auto file_end = std::chrono::high_resolution_clock::now();

                cout << "Vargsiuku: " << vargsiukai.size() << endl;
                cout << "Kietaku: " << kietakai.size() << endl;
                cout << "Duomenys issaugoti i failus vargsiukai.txt ir kietakai.txt" << endl;

                cout << "Studentu skirstymo laikas: " << std::fixed << std::setprecision(3) << std::chrono::duration<double>(split_end - split_start).count() << " s" << endl;

                cout << "Isvedimo i failus laikas: " << std::fixed << std::setprecision(3) << std::chrono::duration<double>(file_end - file_start).count() << " s" << endl;

                auto end = std::chrono::high_resolution_clock::now();
                double visas_laikas = std::chrono::duration<double>(end - start).count();

                cout << "Visos programos veikimo laikas: " << std::fixed << std::setprecision(3) << visas_laikas << " s" << endl;

            }

            case 10: {
                cout << "Programa baigiama." << endl;
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

