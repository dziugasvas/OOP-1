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

const string vardai[] = {"Dovydas", "Matas", "Simonas", "Rokas", "Kajus", "Dziugas", "Virgilijus", "Vitalijus", "Alan", "Aleksas", "Jonas", "Domantas", "Arvydas", "Mantyvdas", "Gvidas"};
const string pavardes[] = {"Kazlauskas", "Buzelis", "Sabonis", "Tubelis", "Gudelis", "Macijauskas", "Alekna", "Vanagas", "Butkevicius", "Ulanovas", "Sirvydis", "Jasikevicius", "Jakucionis", "Kleiza", "Jonauskas"};

const int vardu_kiek = 15;
const int pavard_kiek = 15;

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
void generuotiStudentus(Studentas*& A, int& m);
double vidurkis(const Studentas& S);
double mediana(const Studentas& S);

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
            generuotiStudentus(A, m);
            break;

            case 4: {
                char budas;
                cout << "Kaip skaiciuoti galutini? (v - vidurkis, m - mediana): ";
                cin >> budas;

                while (budas != 'v' && budas != 'm') {
                    cout << "Neteisinga ivestis. Iveskite 'v' arba 'm': ";
                    cin >> budas;
                }

                outputas(A, m, budas);

                veikia = false;
                break;
            }

            default:
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
            break;
        }
    }
    
    for (int i = 0; i < m; i++) {
    delete[] A[i].nd;
}

    delete[] A;
    A = nullptr;

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

void generuotiStudentus(Studentas*& A, int& m) {
    int mGen;
    cout << "Iveskite studentu skaiciu (1-15): ";
    cin >> mGen;

    while (cin.fail() || mGen < 1 || mGen > 15) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Neteisingas skaicius. Iveskite skaiciu nuo 1 iki 15: ";
        cin >> mGen;
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

    for (int i = 0; i < mGen; i++) {
        Studentas S;

        S.vardas = vardai[rand() % vardu_kiek];
        S.pavarde = pavardes[rand() % pavard_kiek];

        S.kiek = kiek;
        S.nd = new int[kiek];
        for (int j = 0; j < kiek; j++) {
            S.nd[j] = rand() % 10 + 1;
        }

        S.egz = rand() % 10 + 1;
        S.rez = 0;

        // padidinam A (m -> m+1)
        Studentas* tempStud = new Studentas[m + 1];

        // perkopijuojam senus
        for (int k = 0; k < m; k++) {
            tempStud[k].vardas = A[k].vardas;
            tempStud[k].pavarde = A[k].pavarde;
            tempStud[k].egz = A[k].egz;
            tempStud[k].rez = A[k].rez;

            tempStud[k].kiek = A[k].kiek;
            tempStud[k].nd = (A[k].kiek > 0) ? new int[A[k].kiek] : nullptr;
            for (int t = 0; t < A[k].kiek; t++)
                tempStud[k].nd[t] = A[k].nd[t];
        }

        // įdedam naują
        tempStud[m].vardas = S.vardas;
        tempStud[m].pavarde = S.pavarde;
        tempStud[m].egz = S.egz;
        tempStud[m].rez = S.rez;
        tempStud[m].kiek = S.kiek;
        tempStud[m].nd = new int[S.kiek];
        for (int t = 0; t < S.kiek; t++)
            tempStud[m].nd[t] = S.nd[t];

        // išvalom seną A
        for (int k = 0; k < m; k++)
            delete[] A[k].nd;
        delete[] A;

        A = tempStud;
        m++;

        delete[] S.nd;
        S.nd = nullptr;
    }

    cout << "Sugeneruoti " << mGen << " studentai." << endl;
}

double vidurkis(const Studentas& S) {
    if (S.kiek == 0) return 0.0;
    int sum = 0;
    for (int i = 0; i < S.kiek; i++) sum += S.nd[i];
    return 1.0 * sum / S.kiek;
}

double mediana(const Studentas& S) {
    if (S.kiek == 0) return 0.0;

    int* temp = new int[S.kiek];
    for (int i = 0; i < S.kiek; i++) temp[i] = S.nd[i];

    std::sort(temp, temp + S.kiek);

    double rez;
    if (S.kiek % 2 == 1) rez = temp[S.kiek / 2];
    else rez = (temp[S.kiek / 2 - 1] + temp[S.kiek / 2]) / 2.0;

    delete[] temp;
    return rez;
}

void outputas(Studentas* A, int m, char pasirinkimas) {
    cout << std::fixed << std::setprecision(2);

    cout << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";

    if (pasirinkimas == 'm') {
        cout << setw(15) << "Galutinis (Med.)" << endl;
    } else {
        cout << setw(15) << "Galutinis (Vid.)" << endl;
    }

    cout << string(50, '-') << endl;

    for (int i = 0; i < m; i++) {
        cout << left << setw(15) << A[i].vardas << left << setw(20) << A[i].pavarde;

        double nd_rez = (pasirinkimas == 'm') ? mediana(A[i]) : vidurkis(A[i]);
        double galutinis = 0.4 * nd_rez + 0.6 * A[i].egz;

        cout << setw(15) << galutinis << endl;
    }
}