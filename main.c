#include "cos.h"

int main()
{
    char *chunk = (char *)malloc(sizeof(char *));
    char *nazwa_pliku = "macierztestowa.txt";
    maciora *plansza;
    Dane *D = (Dane *)malloc(sizeof(Dane));
    if (powiedz_czy_plik_istnieje(nazwa_pliku) == 1)
    {
        plansza = wczytaj(nazwa_pliku);
    }
    else
    {
        plansza = utworz_poczatek();
    }

    algorytm_ruchu2(plansza, D, "qwerty_20");
    printf("zapisano:\n");
    pokaz_macierz(plansza);
    zapisz_do_pliku(plansza, nazwa_pliku);
    zwolnij_macierz(plansza);
    free(D);
}
