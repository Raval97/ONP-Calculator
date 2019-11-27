#ifndef LIBFILES_H
#define LIBFILES_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

//algorytm przeksztalcania wyrazen arytmetycznych i instrukcji przypisania z INF do ONP    file-plik bedacy zrodlem danych
void f_from_INF_to_ONP(ifstream &file);
//algorytm przeksztalcania wyrazen arytmetycznych i instrukcji przypisania z ONP do INF    file-plik bedacy zrodlem danych
void f_from_ONP_to_INF(ifstream &file);
// sprawdza poprawnosc wyrazenia arytmetycznego, zwraca z=true jezeli jest poprawne
// text->wyrazenie arytmetyczne; n-.dlugosc wyrazenia; notacja->rodzaj notacji (ONP lub INF)
bool f_poprawnosc(string text, int n, string notacja);
// funkcja zwraca piorytet w w zaleznosci od operatora->zmienna c
int f_ope_prio(string c);
// funkcja zwrca 1-dla operatorow prawostronnych lub 2-dla operatorow lewostronnych
int f_ope_lacz(string c);
//otwiera plik z dysku o podanej nazwie
void f_otworzplik(ifstream &plik, string nazwa);

#endif
#pragma once
