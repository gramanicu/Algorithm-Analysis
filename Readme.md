# Shortest-Path Problem

Costul minim intre oricare doua noduri (Floyd-Warshall, Dijkstra, BellmanFord, Johnson)

## Structura proiectului

### algo_test.cpp

Ruleaza testele din folderul `/in`. Se foloseste de `algo.cpp` si `algo.h`, functiile folosite ce fac parte din schelet.

### SRC

In acest folder se afla implementarea grafurilor si a algoritmului.

- Graph - definirea tipului abstract de graf
- FastGraph - o implementare de grafuri bazata pe matrici de adiacenta (time-optimised)
- SmallGraph - o implementare de grafuri bazata pe liste de adiacenta (space-optimised)
- GraphDriver - initial, se folosea pentru a citi datele de la input, iar apoi, pe baza unor calcule, determina ce implementare de graf sa foloseasca. Pentru a-l adapta la schelet, i-am adaugat o metoda ce accepta o lista de adiacenta, nemaifiind necesar sa citeasca datele de la input.

Cei trei algoritmi tratati (Dijkstra, Johnson si Floyd-Warshall) se regasesc in ambele clase (FastGraph si SmallGraph), avand implementari usor diferite, dar nu cu mult.

Nota - in urma testarii programului pe grafuri de diferite dimensiuni am observat faptul ca matricile de adiacenta nu sunt mai eficiente. Pentru grafuri mari, atunci cand viteza de access devine importanta, dimensiunea matricii devine o problema. Din acest motiv, doar implementarea cu liste de adiacenta va fi folosita.

### Generator

In acest folder se afla implementarea unui generator de teste. Are o documentatie separata, in care este detaliat modul de functionare. Nu este inca terminat, deoarece prezinta probleme mari de performanta. Pentru faza actuala a proiectului, poate genera teste satisfacatoare.

### Alte fisiere

- ./in - testele pentru grafuri. Primele 5 sunt grafuri cu muchii de lungime 1, urmatoarele 4 sunt grafuri cu muchii de lungimi variabile (pozitive, max ~ 1000000), iar ultimul test are muchii de lungimi aleatoare, in intervalul 0 -> INT32_MAX - 1.
- ./out - rezultatele testelor
- ./other_tests - nu a fost inclus in arhiva trimisa. Contine o multitudine de teste, folosite pentru a evalua performantele algoritmilor. In acest folder sunt puse rezultatele date de fiecare test pentru testele precizate anterior, precum si timpii de rulare.
- Makefile - diferite reguli folosite pentru compilare, coding-style, profilare, etc. O mica observatie : deoarece fisierul obiect algo.o depinde de alte cateva fisere, regula build le creeaza si pe acestea. Pentru a folosi algo.o intr-un program, trebuie incluse si celealte fisere (src/FastGraph.o src/SmallGraph.o src/GraphDriver.o)
  
© 2019 Grama Nicolae, 322CA
