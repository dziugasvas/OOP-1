#ifndef SKAICIAVIMAI_H
#define SKAICIAVIMAI_H

#include "Studentas.h"
#include <vector>

double mediana(const std::vector<int>& paz);
double vidurkis(const std::vector<int>& paz);
void rusiavimas(std::vector<Studentas>& grupe, char budas);
void padalintiStudentus(const std::vector<Studentas>& grupe, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietakai, char budas);

#endif

