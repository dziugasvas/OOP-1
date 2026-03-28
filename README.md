# Projekto aprašymas

Ši programa skirta studentų duomenų apdorojimui ir analizavimui. Vartotojas gali:
- įvesti studentų duomenis ranka;
- automatiškai sugeneruoti pažymius arba studentų įrašus;
- nuskaityti studentų duomenis iš failo;
- sugeneruoti testinius failus;
- atlikti skirtingų konteinerių ir studentų skirstymo strategijų veikimo spartos tyrimu.

Programoje taip pat realizuotos trys studentų skirstymo strategijos, kurių veikimo laikas lyginamas su skirtingo dydžio duomenų failais ir naudojant vector, list bei deque konteinerius.

# Diegimas ir paleidimas
1. Nusiklonuokite repozitoriją:
```
git clone https://github.com/dziugasvas/OOP-1.git
cd OOP-1
```
2. Įsidiekite reikalingus įrankius (jei jų dar neturite):

macOS:
```
xcode-select --install
```

Linux (Ubuntu/Debian):
```
sudo apt update
sudo apt install build-essential
```
3. Sukompiliuokite programą:
```
make
```
4. Paleiskite programą:
```
make run
```

# Naudojimosi instrukcija

Paleidus programą pateikiamas meniu, kuriame galima pasirinkti norimą veiksmą.

Pagrindiniai pasirinkimai:
- įvesti studentų duomenis ranka;
- generuoti pažymius arba studentų įrašus;
- nuskaityti studentus iš failo;
- generuoti testinius failus;
- atlikti veikimo spartos tyrimus su skirtingais konteineriais ir strategijomis;
- išvesti rezultatus.

Pasirinkus atitinkamą meniu punktą, programa pateikia papildomas instrukcijas ekrane.

# Kompiuterio specifikacijos

|       CPU                |  RAM |    SSD     | 
|--------------------------|------|------------| 
| Apple M4 (10 branduolių) | 24GB | NVMe 512GB |      
------------------------------------------------

## Tyrimo rezultatai ir strategijų aprašymas

Šiame tyrime analizuojamas skirtingų konteinerių (`vector`, `list`, `deque`) efektyvumas apdorojant studentų duomenis. Eksperimentuose naudojami skirtingo dydžio failai (nuo 1000 iki 10 000 000 studentų įrašų).

Studentų skirstymui į dvi grupes („vargšiukus“ ir „kietiakus“) realizuotos trys strategijos:

1. **1 strategija**  
   Studentai iš bendro konteinerio kopijuojami į du naujus („vargšiukai“ ir „kietakai“).

2. **2 strategija**  
   Nepažangūs studentai perkeliami į naują konteinerį ir pašalinami iš pradinio.

3. **3 strategija**  
   2 strategija optimizuojama naudojant STL algoritmus (pvz., `std::partition`).

# 1 Strategiija

1000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.0127175 s | 0.000961917 s | 0.000669542 s | 0.0143489 s |
| list   | 0.0122115 s | 0.000588541 s | 0.00066275 s  | 0.0134627 s |
| deque  | 0.0138493 s | 0.000847916 s | 0.000378166 s | 0.0150754 s |

10000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.0756614 s | 0.00258688 s | 0.00231525 s | 0.0805635 s |
| list   | 0.0739396 s | 0.00239837 s | 0.00178629 s | 0.0781243 s |
| deque  | 0.0704445 s | 0.00298854 s | 0.00155887 s | 0.0749919 s |

100000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.621659 s | 0.0227759 s | 0.0231665 s | 0.667601 s |
| list   | 0.636845 s | 0.026863 s  | 0.0205911 s | 0.684299 s |
| deque  | 0.629813 s | 0.0262714 s | 0.0167996 s | 0.672884 s |

1000000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 3.71343 s | 0.21343 s  | 0.278081 s | 4.20494 s |
| list   | 3.67831 s | 0.534339 s | 0.184011 s | 4.39666 s |
| deque  | 3.66872 s | 0.238101 s | 0.187751 s | 4.09457 s |

10000000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 16.8683 s | 1.2659 s  | 1.53455 s | 19.6688 s |
| list   | 16.8212 s | 4.84151 s | 1.13089 s | 22.7936 s |
| deque  | 16.9776 s | 1.42435 s | 1.28207 s | 19.684 s |

# 2 Strategiija

1000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.0337968 s | 0.000322 s | 0.000191917 s | 0.0343108 s |
| list   | 0.0137755 s | 0.000348292 s | 0.00049475 s | 0.0146185 s |
| deque  | 0.0124172 s | 0.000975791 s | 0.00085475 s | 0.0142477 s |

10000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.0558264 s | 0.00267442 s | 0.00187083 s | 0.0603716 s |
| list   | 0.0745975 s | 0.00240125 s | 0.00221579 s | 0.0792145 s |
| deque  | 0.0737392 s | 0.00295646 s | 0.00241783 s | 0.0791135 s |

100000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.670281 s | 0.0244201 s | 0.0198922 s | 0.714593 s |
| list   | 0.636034 s | 0.0343023 s | 0.0430024 s | 0.713338 s |
| deque  | 0.644662 s | 0.0282162 s | 0.02596 s   | 0.698838 s |

1000000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 3.86553 s | 0.219079 s | 0.175061 s | 4.25967 s |
| list   | 3.76082 s | 0.595179 s | 0.68381 s  | 5.03981 s |
| deque  | 3.73485 s | 0.242478 s | 0.23595 s  | 4.21328 s |

10000000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 17.4246 s | 1.31459 s | 1.17426 s | 19.9134 s |
| list   | 17.2439 s | 5.02083 s | 6.00398 s | 28.2688 s |
| deque  | 17.3232 s | 1.43107 s | 1.43701 s | 20.1913 s |

# 3 Strategiija

1000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.0109262 s | 0.000935958 s | 0.000520667 s | 0.0123828 s |
| list   | 0.0168377 s | 0.000425334 s | 0.000271583 s | 0.0175347 s |
| deque  | 0.011223 s  | 0.00113017 s  | 0.000275458 s | 0.0126286 s |

10000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.0769198 s | 0.00262871 s | 0.00088325 s | 0.0804318 s |
| list   | 0.0623636 s | 0.00223296 s | 0.00104267 s | 0.0656392 s |
| deque  | 0.0588062 s | 0.00303237 s | 0.000904541 s | 0.0627431 s |

100000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 0.646407 s | 0.0240402 s | 0.0105628 s | 0.68101 s |
| list   | 0.663809 s | 0.0286556 s | 0.0142682 s | 0.706733 s |
| deque  | 0.681715 s | 0.02741 s   | 0.0114262 s | 0.720551 s |

1000000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 3.81083 s | 0.224106 s | 0.10299 s | 4.13793 s |
| list   | 3.83585 s | 0.572952 s | 0.23537 s | 4.64417 s |
| deque  | 3.95477 s | 0.251961 s | 0.103977 s | 4.31071 s |

10000000 studentų

| Konteineris | Nuskaitymas | Rikiavimas | Skirstymas | Visas laikas |
|:--|:--|:--|:--|:--|
| vector | 17.5431 s | 1.32179 s | 0.760116 s | 19.6251 s |
| list   | 17.3734 s | 5.3177 s  | 1.49927 s  | 24.1903 s |
| deque  | 17.4429 s | 1.44892 s | 0.732903 s | 19.6247 s |
