#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>

using std::string;
using std::cin;
using std::cout;
using std::left;
using std::right;
using std::setw;
using std::endl;

struct Studentas {
    string vardas, pavarde;
    int* nd = nullptr;
    int kiek = 0;
    int egz = 0;
    double rez = 0;
};

void inputas (Studentas*& A, int & m);
void outputas (Studentas* A, int m, char pasirinkimas);

int main() {
    Studentas* A = nullptr;
    int m = 0;

    srand(time(NULL));

    bool veikia = true;

    while (veikia) {
        cout << "Pasirinkimu meniu: " << endl;
        cout << "1 - Ivesti studentus ranka" << endl;
        cout << "2 - Generuoti tik pazymius" << endl;
        cout << "3 - Generuoti studentus (vardas/pavarde/pazymiai)" << endl;
        cout << "4 - Spausdinti rezultatus ir baigti" << endl;
    
        int p;
        cin >> p;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida: iveskite skaiciu 1-4" << endl;
            continue;
        }

        switch (p) {
            case 1:
            cout << "dar bus daryta" << endl;
            break;

            case 2:
            cout << "dar bus daryta" << endl;
            break;

            case 3:
            cout << "dar bus daryta" << endl;
            break;

            case 4: {
                char budas;
                cout << "Kaip skaiciuoti galutini? (v - vidurkis, m - mediana): ";
                cin >> budas;

                while (budas != 'v' && budas != 'm') {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neteisinga ivestis. Iveskite 'v' arba 'm': ";
                    cin >> budas;
                }

                cout << "dar bus padaryta" << endl;

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