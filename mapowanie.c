#include "cos.h"

void pokaz_macierz(maciora *m)
{
    //printf("Plus r:%d\nPlus c:%d\n", m->plus_r, m->plus_c);
    //printf("Min r:%d\nMin c:%d\n", m->min_r, m->min_c); //zapisuje przesunięcie
    printf("Ogólne r:%d     Ogólne c:%d\n", m->r, m->c);   //zapisuje rozmiar macierzy
    for (int i = m->r - 1; i >= 0; i--)
        for (int j = 0; j < m->c; j++)
        {
            printf("%d\t", m->tab[i][j]);
            if (j + 1 == m->c)
                printf("\n");
        }
}

void przesun_prawo(maciora *m)
{

    for (int i = 0; i < m->r; i++)
        for (int j = m->c - 1; j >= 0; j--)
        {
            m->tab[i][j] = m->tab[i][j - 1];
        }

    for (int i = 0; i < m->r; i++)
        for (int j = m->c - 1; j >= 0; j--)
        {
            m->tab2[i][j] = m->tab2[i][j - 1];
        }
}

void przesun_gora(maciora *m)
{

    for (int i = m->r - 1; i >= 0; i--)
        for (int j = m->c - 1; j >= 0; j--)
        {
            if (i == 0)
                m->tab[i][j] = 0;
            else
                m->tab[i][j] = m->tab[i - 1][j];
        }

    for (int i = m->r - 1; i >= 0; i--)
        for (int j = m->c - 1; j >= 0; j--)
        {
            if (i == 0)
                m->tab2[i][j] = 0;
            else
                m->tab2[i][j] = m->tab2[i - 1][j];
        }
}

void dodaj_wiersz(maciora *m)
{

    m->tab = (int **)realloc(m->tab, sizeof(int *) * m->r);
    m->tab[m->r - 1] = (int *)calloc(m->c, sizeof(int));

    m->tab2 = (int **)realloc(m->tab2, sizeof(int *) * m->r);
    m->tab2[m->r - 1] = (int *)calloc(m->c, sizeof(int));
}

void dodaj_kolumne(maciora *m)
{
    for (int i = 0; i < m->r; i++)
    {
        m->tab[i] = (int *)realloc(m->tab[i], sizeof(int) * m->c);
        m->tab2[i] = (int *)realloc(m->tab2[i], sizeof(int) * m->c);
    }
}

int ewentualna_realokacja(maciora *m, int x, int y)
{
    //zapisuje poprzednie wymiary macierzy
    int old_min_r = m->min_r;
    int old_min_c = m->min_c;
    int old_r = m->r;
    int old_c = m->c;
    // 1 sprawdzam dodatnie
    if (x <= 0)
        if (m->min_r < -x + 1)
            m->min_r = -x + 1;
    if (y <= 0)
        if (m->min_c < -y + 1)
            m->min_c = -y + 1;
    // 2 sprawdzam dodatnie
    if (x > 0)
        if (m->plus_r < x)
            m->plus_r = x;
    if (y > 0)
        if (m->plus_c < y)
            m->plus_c = y;
    // 3 wprowadzam nowe wymiary macierzy
    m->r = (m->plus_r) + (m->min_r);
    m->c = (m->plus_c) + (m->min_c);

    if (m->r > old_r) //jeśli wiersze się zwiekszyły
        dodaj_wiersz(m);
    if (m->min_r > old_min_r) //jeśli wiersze się zwiększyły na minusie to przesuń
        przesun_gora(m);
    if (m->c > old_c)
        dodaj_kolumne(m);
    if (m->min_c > old_min_c)
        przesun_prawo(m);
}

void wizualizacja(maciora *m, int x, int y, int pole, char kierunek_lufy)
{
    ewentualna_realokacja(m, x, y);

    if (pole == 1)
    { //sciana   // ŚCIANA- 1  TRAWA-2  PIACH-3[r][c]
        m->tab[x + m->min_r - 1][y + m->min_c - 1] = 1;
    }
    if (pole == 2)
    { // trawa

        m->tab[x + m->min_r - 1][y + m->min_c - 1] = 2;
    }
    if (pole == 3)
    { // piach
        m->tab[x + m->min_r - 1][y + m->min_c - 1] = 3;
    }
}

void wizualizacja2(maciora *m, int x, int y, int pole, char kierunek_lufy)
{
    ewentualna_realokacja(m, x, y);
    if (pole == 1)
    { // ŚCIANA- 1  TRAWA-2  PIACH-3[r][c]
        m->tab2[x + m->min_r - 1][y + m->min_c - 1] = 1;
        m->tab[x + m->min_r - 1][y + m->min_c - 1] = 1;
    }
    if (pole == 2)
    {
        m->tab2[x + m->min_r - 1][y + m->min_c - 1] = 1;
        m->tab[x + m->min_r - 1][y + m->min_c - 1] = 2;
    }
    if (pole == 3)
    {
        m->tab2[x + m->min_r - 1][y + m->min_c - 1] = 1;
        m->tab[x + m->min_r - 1][y + m->min_c - 1] = 3;
    }

    m->my_c = y + m->min_c - 1; //teraz to zamieniałem 00:15 26.02.2021
    m->my_r = y + m->min_r - 1;

    if (kierunek_lufy == 'S') //S-1,W-2,N-3,E-4
        m->zwrot_lufy = 1;
    if (kierunek_lufy == 'W')
        m->zwrot_lufy = 2;
    if (kierunek_lufy == 'N')
        m->zwrot_lufy = 3;
    if (kierunek_lufy == 'E')
        m->zwrot_lufy = 4;
}

void uzupelnienie_explore(Dane *odczyt, maciora *plansza)
{
    for (int i = 0; i < 3; i++)
    {
        wizualizacja(plansza, odczyt->x[i], odczyt->y[i], odczyt->field[i], odczyt->kierunek_lufy);
    }
    plansza->my_c = odczyt->website_x;
    plansza->my_r = odczyt->website_y;
    pokaz_macierz(plansza);
}

void uzupelnienie_info(Dane *odczyt, maciora *plansza)
{
    wizualizacja2(plansza, odczyt->x[0], odczyt->y[0], odczyt->field[0], odczyt->kierunek_lufy);
    pokaz_macierz(plansza);
    plansza->my_c = odczyt->website_x;
    plansza->my_r = odczyt->website_y;
}
