#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

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

void inputas (vector <Studentas> &grupe);
void outputas (const vector <Studentas> &grupe);
int main() {
    vector <Studentas> grupe;
    inputas(grupe);
    outputas(grupe);
}

void inputas (vector <Studentas> &grupe){
    for(int ii = 0; ii < 2; ii++) {
    Studentas A;
    cout << "Iveskite studento vardo ir pavarde: ";
    cin >> A.vardas >> A.pavarde;
    cout << "Iveskite semestro ivertinimus. Kiek ju bus? ";
    int n, sum = 0;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int temp;
        cout << "Iveskite " << i + 1 << "-aji pazymi is " << n << ": ";
        cin >> temp;
        A.paz.push_back(temp); sum += temp;
        }
    cout << "Iveskite egzamina: "; cin >> A.egz;
    A.rez = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
    grupe.push_back(A);
    A.paz.clear();
    }
}
void outputas(const vector <Studentas> &grupe) {
    cout << std::fixed << std::setprecision(2);

    for(const auto& A: grupe){
        cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
        cout << setw(10) << A.rez;
    }
}
