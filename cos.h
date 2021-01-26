#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

int moj_globalny_int;
char moj_globalny_char; //h

typedef struct dane
{
    int x[3];
    int y[3];
    int field[3];
    char kierunek_lufy;
    int website_x;
    int website_y;
    int ile_min_y;
    int ile_min_x;

} Dane;

typedef struct Maciora
{
    int plus_r; //wiersze macierzy na plusie
    int plus_c; //kolumny macierzy na minusie
    int min_r;  //wiersze na minusie
    int min_c;  //kolumny na minusie
    int r;
    int c;
    int **tab;      // ŚCIANA- 1  TRAWA-2  PIACH-3[r][c]
    int **tab2;     //mapa gdzie byłem czołgiem jeżeli zero to nie byłem jeżeli 1 to byłem
    int zwrot_lufy; // S-1,W-2,N-3,E-4
    int my_r;
    int my_c;

} maciora;

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

char *info(char *token, maciora *p, Dane *z);
char *explore(char *token, maciora *p, Dane *z);
char *move(char *token,maciora *p, Dane *z);
char *rotate(char *token, char *direction,maciora *p, Dane *z);

void pokaz_macierz(maciora *m);
void przesun_prawo(maciora *m);
void przesun_gora(maciora *m);
void dodaj_wiersz(maciora *m);
void dodaj_kolumne(maciora *m);
int ewentualna_realokacja(maciora *m, int x, int y);
void wizualizacja(maciora *m, int x, int y, int pole, char kierunek_lufy);
void wizualizacja2(maciora *m, int x, int y, int pole, char kierunek_lufy);
void uzupelnienie_explore(Dane *odczyt, maciora *plansza);
void uzupelnienie_info(Dane *odczyt, maciora *plansza);
maciora *utworz_poczatek();
int powiedz_czy_plik_istnieje(char *nazwa);
maciora *wczytaj(char *nazwa);
void zapisz_do_pliku(maciora *m, char *nazwa_pliku);
void zwolnij_macierz(maciora *m);
int sprawdz_wypelnione(maciora *m);
int check_border(maciora *m);
int can_I_go(maciora *m);
int check_front(maciora *m, Dane *D);
int go_aroud(maciora *m, Dane *D, char *tok);
int have_you_been_here(maciora *m);
void make_fram(maciora *m, Dane *D, char *tok);
void algorytm_ruchu2(maciora *m, Dane *D, char *tok);
void pokaz_macierz_jak_jest(maciora*m);

Dane *interpret_response(const char *const chunk, Dane *dane);
char *make_request(char *url);
