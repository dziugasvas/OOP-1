#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "Studentas.h"
#include <vector>
#include <string>

void generuotiFaila(const std::string& failoPavadinimas, int kiekStudentu, int ndKiekis);
void outputas(const std::vector<Studentas>& grupe, char pasirinkimas);
void spausdinimas(const std::vector<Studentas>& grupe, char pasirinkimas);
void inputas(std::vector<Studentas>& grupe);
void nuskaitymas(std::vector<Studentas>& grupe, std::string failas);
double mediana(const std::vector<int>& paz);
double vidurkis(const std::vector<int>& paz);
void rusiavimas(std::vector<Studentas>& grupe, char budas);
void padalintiStudentus(const std::vector<Studentas>& grupe, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietakai, char budas);
void spausdintiIFaila(const std::vector<Studentas>& grupe, const std::string& failoPavadinimas, char budas);
void tyrimas1(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis);
void tyrimas2(const std::string& failoPavadinimas, char budas);

#endif
