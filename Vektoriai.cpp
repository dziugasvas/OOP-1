#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::cin;
using std::vector;
using std::cout;
using std::left;
using std::right;
using std::setw;
using std::endl;

struct Studentas {
    string vardas, pavarde;
    vector <int> paz;
    int egz;
    double rez;
};

void inputas (vector <Studentas> &grupe, char pasirinkimas);
void outputas (const vector <Studentas> &grupe, char pasirinkimas);
double mediana(const vector<int>& paz);
int main() {
    vector <Studentas> grupe;

    char pasirinkimas;
    cout << "Skaiciuoti pagal vidurki (v) ar mediana (m): ";
    cin >> pasirinkimas;

    while (pasirinkimas != 'v' && pasirinkimas != 'm') {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Ivedete neteisingai, iveskite (v) arba (m): ";
    cin >> pasirinkimas;
}

    inputas(grupe, pasirinkimas);
    outputas(grupe, pasirinkimas);
}

void inputas (vector <Studentas> &grupe, char pasirinkimas){
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

        int sum = 0;

        while (true) {
            int nd;
            cout << "Iveskite " << ii << "-ojo studento " << A.paz.size() + 1 << "-aji namu darbo ivertinima (1-10, 0 - baigti): ";
            cin >> nd;

            if (!cin.fail() && nd == 0) {
                break;
            }

            if (!cin.fail() && nd >= 1 && nd <= 10) {
                A.paz.push_back(nd);
                sum += nd;
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
             sum += nd;
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

        double nd_rez;
        if (pasirinkimas == 'm') {
            nd_rez = mediana(A.paz);
        } else {
            nd_rez = sum * 1.0 / A.paz.size();
        }

        A.rez = 0.4 * nd_rez + 0.6 * A.egz;

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
        cout << setw(15) << A.rez << endl;
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
