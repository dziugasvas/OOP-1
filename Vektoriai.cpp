#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <fstream>
#include <sstream>


using std::string;
using std::cin;
using std::vector;
using std::cout;
using std::left;
using std::right;
using std::setw;
using std::endl;
using std::ifstream;
using std::getline;
using std::stringstream;

const vector<string> vardai = {"Dovydas", "Matas", "Simonas", "Rokas", "Kajus", "Dziugas", "Virgilijus", "Vitalijus", "Alan", "Aleksas", "Jonas", "Domantas", "Arvydas", "Mantyvdas", "Gvidas"};
const vector<string> pavardes = {"Kazlauskas", "Buzelis", "Sabonis", "Tubelis", "Gudelis", "Macijauskas", "Alekna", "Vanagas", "Butkevicius", "Ulanovas", "Sirvydis", "Jasikevicius", "Jakucionis", "Kleiza", "Jonauskas"};

struct Studentas {
    string vardas, pavarde;
    vector <int> paz;
    int egz;
    double rez;
};

void inputas (vector <Studentas> &grupe);
void outputas (const vector <Studentas> &grupe, char pasirinkimas);
double mediana(const vector<int>& paz);
double vidurkis(const vector<int>& paz);
void nuskaitymas(vector<Studentas>& grupe, string failas);

int main() {
    vector <Studentas> grupe;
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
            inputas (grupe);
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

                    if (A.vardas == "Baigti") {
                        break;
                    }

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
            nuskaitymas(grupe, failas);
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

                outputas (grupe, budas);
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

void inputas (vector <Studentas> &grupe) {
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
void outputas(const vector <Studentas> &grupe, char pasirinkimas) {
    cout << std::fixed << std::setprecision(2);

    cout << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";

    if (pasirinkimas == 'm') {
        cout << setw(15) << "Galutinis (Med.)" << endl;
    } else {
        cout << setw(15) << "Galutinis (Vid.)" << endl;
    }

    cout << string(50, '-') << endl;

    for(const auto& A: grupe){
        cout << left << setw(15) << A.vardas << left << setw(20) << A.pavarde;
        double nd_rez = (pasirinkimas == 'm') ? mediana(A.paz) : vidurkis(A.paz);
        double galutinis = 0.4 * nd_rez + 0.6 * A.egz;
        cout << setw(15) << galutinis << endl;
    }
}

double mediana(const vector<int>& paz) {
    int n = paz.size();

    if (n == 0) {
        return 0.0;
    }

    vector <int> temp = paz;
    std::sort(temp.begin(), temp.end());

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

void nuskaitymas(vector<Studentas>& grupe, string failas) {
    ifstream input (failas);
    
    if (!input.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    grupe.clear();

    string eilute;
    getline(input, eilute);

    while (getline(input,eilute)) {
        stringstream ss(eilute);
        Studentas s;

        ss >> s.vardas >> s.pavarde;

        vector <int> paz;
        int x;

        while (ss >> x) {
            paz.push_back(x);
        }

        s.egz = paz.back();
        paz.pop_back();
        s.paz = paz;
        s.rez = 0;

        grupe.push_back(s);

    }

    cout << "Nuskaityta studentu: " << grupe.size() << endl;

}

