# Autor: Tymoteusz Roźmiarek
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
