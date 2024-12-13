# Autor: Tymoteusz Roźmiarek
## Projekt implementuje trzy warianty algorytmu Dijkstry, służącego do znajdywania najkrótszych ścieżek w grafie:
1) wariant podstawowy, wykorzystujący kolejkę priorytetową,
2) algorytm Diala wykorzystujący C+1 kubełków,
3) wersja podstawowa wykorzystująca strukturę Radix Heap.

Graf jest reprezentowany przez listę sąsiedztwa (implenetacja grafu znajduje się w pliku `Graph.hpp`).

Funkcje `dijkstra`, `dial`, `radix_heap` zostały zdefiniowane w pliku `Graph.hpp`, natomiast definicja struktury Radix Heap znajduje się w pliku `RadixHeap.hpp`.
Pliki `dial.cpp`, `dijkstra.cpp`, `radix_heap.cpp` odpowiadają za odpowiednie wczytanie danych wejściowych, pomiar czasu wykonania algorytmów oraz zapis danych wyjściowych do pliku wynikowego.

Projekt można skompilować poleceniem `make`. Spowoduje to skompilowanie plików żródłowych i umieszczenie plików wykonywalnych w katalogu build.
