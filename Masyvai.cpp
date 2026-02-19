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
void generuotiPazymius (Studentas*& A, int& m);

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
            inputas (A, m);
            break;

            case 2:
            generuotiPazymius(A, m);
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

void inputas(Studentas*& A, int& m) {
    int ii = 0;

    while (true) {
        Studentas S;
        ii++;

        cout << "Iveskite " << ii << "-ojo studento varda ('Baigti' - baigti ivedima): ";
        cin >> S.vardas;

        if (S.vardas == "Baigti") {
            break;
        }

        cout << "Iveskite " << ii << "-ojo studento pavarde: ";
        cin >> S.pavarde;

        int* nd_laikinas = nullptr;
        int n = 0;

        while (true) {
            int nd;
            cout << "Iveskite " << ii << "-ojo studento " << (n+1) << "-aji namu darbo ivertinima (1-10, 0 - baigti): ";
            cin >> nd;

            if (!cin.fail() && nd == 0) {
                break;
            }

            if (!cin.fail() && nd >= 1 && nd <= 10) {
                int* temp = new int[n + 1];
                for (int j = 0; j < n; j++) {
                    temp[j] = nd_laikinas[j];  
                }

                    temp[n] = nd;

                    delete[] nd_laikinas;
                    nd_laikinas = temp;
                    n++;
                } else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ivedete neteisingai, bandykite dar karta! (1-10, 0 - baigti)" << endl;
            }
        }

        while (n == 0) {
            int nd;
            cout << "Neivestas nei vienas ND. Iveskite bent viena pazymi (1-10): ";
            cin >> nd;

            if (!cin.fail() && nd >= 1 && nd <= 10) {
               nd_laikinas = new int[1];
               nd_laikinas[0] = nd;
               n = 1;
               break;
            }

                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ivedete neteisingai, bandykite dar karta! (1-10)" << endl;
            }

            while (true) {
                cout << "Iveskite studento egzamino rezultata (0-10): ";
                cin >> S.egz;
                
                if (!cin.fail() && S.egz >= 0 && S.egz <= 10) {
                    break;
            }
            
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ivedete neteisingai, bandykite dar karta! (0-10)" << endl;
        }

        S.kiek = n;
        S.nd = new int[n];
        for (int j = 0; j < n; j++) S.nd[j] = nd_laikinas[j];
        delete[] nd_laikinas;
        nd_laikinas = nullptr;

        S.rez = 0;

        
        Studentas* tempStud = new Studentas[m + 1];

        
        for (int i = 0; i < m; i++) {
            tempStud[i].vardas = A[i].vardas;
            tempStud[i].pavarde = A[i].pavarde;
            tempStud[i].egz = A[i].egz;
            tempStud[i].rez = A[i].rez;

            tempStud[i].kiek = A[i].kiek;
            tempStud[i].nd = (A[i].kiek > 0) ? new int[A[i].kiek] : nullptr;
            for (int j = 0; j < A[i].kiek; j++) tempStud[i].nd[j] = A[i].nd[j];
        }

        tempStud[m].vardas = S.vardas;
        tempStud[m].pavarde = S.pavarde;
        tempStud[m].egz = S.egz;
        tempStud[m].rez = S.rez;
        tempStud[m].kiek = S.kiek;
        tempStud[m].nd = (S.kiek > 0) ? new int[S.kiek] : nullptr;
        for (int j = 0; j < S.kiek; j++) tempStud[m].nd[j] = S.nd[j];

        for (int i = 0; i < m; i++) {
            delete[] A[i].nd;
        }
        delete[] A;

        A = tempStud;
        m++;

        delete[] S.nd;
        S.nd = nullptr;
    }
}

void generuotiPazymius(Studentas*& A, int& m) {
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
        Studentas S;
        ii++;

        cout << "Iveskite " << ii << "-ojo studento varda ('Baigti' - baigti ivedima): ";
        cin >> S.vardas;

        if (S.vardas == "Baigti") {
            break;
        }

        cout << "Iveskite " << ii << "-ojo studento pavarde: ";
        cin >> S.pavarde;

        S.kiek = kiek;
        S.nd = new int[kiek];
        for (int i = 0; i < kiek; i++) {
            S.nd[i] = rand() % 10 + 1;
        }

        S.egz = rand() % 10 + 1;
        S.rez = 0;

        Studentas* tempStud = new Studentas[m + 1];

        for (int i = 0; i < m; i++) {
            tempStud[i].vardas = A[i].vardas;
            tempStud[i].pavarde = A[i].pavarde;
            tempStud[i].egz = A[i].egz;
            tempStud[i].rez = A[i].rez;

            tempStud[i].kiek = A[i].kiek;
            tempStud[i].nd = (A[i].kiek > 0) ? new int[A[i].kiek] : nullptr;
            for (int j = 0; j < A[i].kiek; j++) tempStud[i].nd[j] = A[i].nd[j];
        }

        tempStud[m].vardas = S.vardas;
        tempStud[m].pavarde = S.pavarde;
        tempStud[m].egz = S.egz;
        tempStud[m].rez = S.rez;
        tempStud[m].kiek = S.kiek;
        tempStud[m].nd = new int[S.kiek];
        for (int j = 0; j < S.kiek; j++) tempStud[m].nd[j] = S.nd[j];

        for (int i = 0; i < m; i++) delete[] A[i].nd;
        delete[] A;

        A = tempStud;
        m++;

        cout << "Sugeneruota: " << kiek << " ND pazymiai. Egzamino pazymys = " << S.egz << endl;

        delete[] S.nd;
        S.nd = nullptr;
    }
}