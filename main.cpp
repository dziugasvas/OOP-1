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
    for(int ii = 0; ii < 2; ii++) {
    Studentas A;
    cout << "Iveskite " << ii + 1 << "-ojo studento vardo ir pavarde: ";
    cin >> A.vardas >> A.pavarde;

    int n, sum = 0;

while (true) {
    cout << "Iveskite studento namu darbu ivertinimus. Kiek ju bus: ";
    cin >> n;

    if (!cin.fail() && n > 0) {
        break;
    }

    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Ivedete neteisingai, bandykite dar karta!" << endl;;
}


    for(int i = 0; i < n; i++) {
        int temp;
        while (true) {
        cout << "Iveskite " << i + 1 << "-aji ivertinima (0-10): ";
        cin >> temp;

        if (!cin.fail() && temp >= 0 && temp <= 10) break;

        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ivedete neteisingai, bandykite dar karta!\n";
    }

        A.paz.push_back(temp); 
        sum += temp;
        }
        
    while (true) {
    cout << "Iveskite studento egzamino rezultata (0-10): ";
    cin >> A.egz;

    if (!cin.fail() && A.egz >= 0 && A.egz <= 10) break;

    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Ivedete neteisingai, bandykite dar karta!\n";
}

    double nd_rez;
    if (pasirinkimas == 'm') {
        nd_rez = mediana(A.paz);
    } else {
        nd_rez = sum * 1.0 / n;
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
