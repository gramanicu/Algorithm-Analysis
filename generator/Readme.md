# Graph Generator

Acesta este un program folosit pentru a genera grafuri. Initial, generatorul era altul, dar din cauza unor probleme legate de performanta (si care limita dimensiunea grafurilor ce pot fi generate), programul a fost simplificat si optimizat. Una dintre caracteristicile principale ale acestei versiuni o reprezinta folosirea mai multor fire de executie.

De asemenea, fata de versinea anterioara, acest generator creeaza doar grafurile, nu si solutia problemei celui mai scurt drum.

Formatul fisierelor generate este urmatorul:
  
```c
node_count edge_count
source_node_1 target_node_1 edge_cost_1
source_node_2 target_node_2 edge_cost_2
source_node_3 target_node_3 edge_cost_3
...
source_node_k target_node_k edge_cost_k
...
```

## Constante

Deoarece acest generator nu mai citeste date dintr-un fisier, setarile lui pot fi modificate alterand constante:

- `INPUTS_FOLDER` - folderul unde sunt stocate "grafurile"
- `MAX_NODE_COUNT` - numarul maxim de noduri ce sunt generate
- `MAX_EDGE_COUNT` - numarul maxim de muchii ce vor fi generate
- `NUM_OF_TESTS` - numarul de teste (grafuri) generate
- `MIN_DISTANCE` - lungimea minima a unei muchii (poate avea si valori negative)
- `MAX_DISTANCE` - lungimea maxima a unei muchii (poate avea si valori negative)

Pentru a genera un graf cu muchii de lungime constanta, MIN_DISTANCE se seteaza egal cu MAX_DISTANCE

## Mod de functionare

Cum am precizat anterior, acest generator este o varianta mult mai simpla a primei iteratii. Cand generatorul este initializat, acesta va determina numarul de threaduri ale sistemului. Apoi, imparte numarul maxim de noduri ale unui graf la numarul de teste ce vor fi generate, pentru a genera teste de dimensiune crescatoare. Pentru fiecare test, determina numarul de muchii ale grafului (min(10^6, noduri^2)), si apoi imparte numarul de muchii (numarul de linii din fisierele .in) la numarul de threaduri, pentru a distribui in mod egal sarcina.

Fiecare thread genereaza muchii dintr-un interval prestabilit si le stocheaza intr-un vector de grafuri (pentru a nu "suprapune" threadurile). Lungimea muchiilor este generata aleator din intervalul setat. Fata de versiunea anterioara a generatorului, care avea grija ca nodurile sa aiba un numar similar de muchii care vin/pleaca, acesta va genera noduri din care plec muchii spre toate celelalte noduri (in general). De asemenea, o alta diferenta este faptul ca grafurile generate cu acest program au intotdeauna densitatea maxima (conform limitelor impuse: numar noduri si numar muchii).

## RNG - EasyRand

Pentru a genera numere aleatoare, acest program foloseste aceasta [biblioteca](https://github.com/gramanicu/EasyRand), pe care am dezvoltat-o cu ceva timp in ruma. Rezolva cateva [probleme](https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful) pe care metodele uzuale de randomizare, `rand()` sau `srand()` le au.

Am preferat sa folosesc fisierul .cpp si .h direct, deoarece includerea bibliotecii in forma ei originala (si compilarea ei) ar fi facut mult mai complexa structura proiectului.

© 2019 Grama Nicolae, 322CA
