#include "cos.h"

maciora *utworz_poczatek()
{
    maciora *m = (maciora *)malloc(sizeof(maciora));
    m->r = 11;
    m->c = 11;
    m->plus_r = 9;
    m->plus_c = 9;
    m->min_r = 2;
    m->min_c = 2;
    m->tab = (int **)calloc(m->r, sizeof(int *));
    for (int i = 0; i < m->r; i++)
        m->tab[i] = (int *)calloc(m->c, sizeof(int));

    m->tab2 = (int **)calloc(m->r, sizeof(int *));
    for (int i = 0; i < m->r; i++)
        m->tab2[i] = (int *)calloc(m->c, sizeof(int));

    return m;
}

int powiedz_czy_plik_istnieje(char *nazwa)
{
    FILE *plik;
    plik = fopen(nazwa, "r");
    if (plik)
    {
        fclose(plik);
        return 1;
    }
    return 0;
}

maciora *wczytaj(char *nazwa)
{
    FILE *plik;
    maciora *m = (maciora *)malloc(sizeof(maciora));
    plik = fopen(nazwa, "r");
    fscanf(plik, "%d", &m->plus_r);
    fscanf(plik, "%d", &m->plus_c);
    fscanf(plik, "%d", &m->min_r); //zapisuje przesunięcie do macierzy
    fscanf(plik, "%d", &m->min_c);
    fscanf(plik, "%d", &m->r); //zapisuje rozmiar macierzy
    fscanf(plik, "%d", &m->c);
    m->tab = (int **)calloc(m->r, sizeof(int *));
    for (int i = 0; i < m->r; i++)
        m->tab[i] = (int *)calloc(m->c, sizeof(int));
    // wczytanie
    for (int i = (m->r) - 1; i >= 0; i--)
    {
        for (int j = 0; j < m->c; j++)
        {
            fscanf(plik, "%d", &m->tab[i][j]);
        }
    }
    fclose(plik);
    return m;
}

void zapisz_do_pliku(maciora *m, char *nazwa_pliku)
{
    FILE *plik = fopen(nazwa_pliku, "w");

    fprintf(plik, "%d\n%d\n", m->plus_r, m->plus_c);
    fprintf(plik, "%d\n%d\n", m->min_r, m->min_c); //zapisuje przesunięcie
    fprintf(plik, "%d\n%d\n", m->r, m->c);         //zapisuje rozmiar macierzy
    for (int i = m->r - 1; i >= 0; i--)
        for (int j = 0; j < m->c; j++)
        {
            fprintf(plik, "%d\t", m->tab[i][j]);
            if (j + 1 == m->c)
                fprintf(plik, "\n");
        }
    fclose(plik);
}

void zwolnij_macierz(maciora *m)
{
    for (int i = 0; i < m->r; i++)
    {
        free(m->tab[i]);
        free(m->tab2[i]);
    }
    free(m->tab2);
    free(m->tab);
    free(m);
}