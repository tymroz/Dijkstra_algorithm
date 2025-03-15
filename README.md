## [PL]
## Projekt implementuje trzy warianty algorytmu Dijkstry, służącego do znajdywania najkrótszych ścieżek w grafie:
1) wariant podstawowy, wykorzystujący kolejkę priorytetową,
2) algorytm Diala wykorzystujący C+1 kubełków,
3) wersja podstawowa wykorzystująca strukturę Radix Heap.

Graf jest reprezentowany przez listę sąsiedztwa (implenetacja grafu znajduje się w pliku `graph.hpp`).

Funkcje `dijkstra`, `dial`, `radix_heap` zostały zdefiniowane w pliku `graph.hpp`, natomiast definicja struktury Radix Heap znajduje się w pliku `radixHEAP.hpp`.
Pliki `dial.cpp`, `dijkstra.cpp`, `radix_heap.cpp` odpowiadają za odpowiednie wczytanie danych wejściowych, pomiar czasu wykonania algorytmów oraz zapis danych wyjściowych do pliku wynikowego.

Projekt można skompilować poleceniem `make`. Spowoduje to skompilowanie plików żródłowych i umieszczenie plików wykonywalnych w katalogu build.

Przykładowe uruchomienie: 
```
dijkstra -d graph.gr -ss sources.ss -oss results.ss.res
```
Program wyznaczy średni czas znajdowania najkrótszych ścieżek w grafie.

Istnieje również opcja uruchomienia z flagą -p2p. Przykład:
```
dijkstra -d graph.gr -ss pairs.p2p -oss results.p2p.res
```
Program wyznaczy długość najkrótszej ścieżki między parą wierzchołków.

Programy były testowane na danych z [9th DIMACS Implementation Challenge – Shortest Paths](https://www.diag.uniroma1.it/challenge9/download.shtml)

## [EN]
## The project implements three variants of Dijkstra's algorithm for finding the shortest paths in a graph:
1) A basic variant using a priority queue,
2) The Dial algorithm using C+1 buckets,
3) A basic version utilizing the Radix Heap structure.

The graph is represented by an adjacency list (the graph implementation is located in the `graph.hpp`).

The functions `dijkstra`, `dial`, `radix_heap` are defined in `graph.hpp`, while the definition of the Radix Heap structure is found in `radixHEAP.hpp`.
The files `dial.cpp`, `dijkstra.cpp`, `radix_heap.cpp` handle reading input data, measuring algorithm execution time, and saving output data to a results file.

The project can be compiled using the `make`. command, which will compile the source files and place the executable files in the `build` directory.

Example execution: 
```
dijkstra -d graph.gr -ss sources.ss -oss results.ss.res
```
The program will determine the average time required to find the shortest paths in the graph.

There is also an option to run the program with the `-p2p` flag. Example:
```
dijkstra -d graph.gr -ss pairs.p2p -oss results.p2p.res
```
The program will determine the length of the shortest path between a pair of vertices.

The programs were tested on data from the [9th DIMACS Implementation Challenge – Shortest Paths](https://www.diag.uniroma1.it/challenge9/download.shtml)
