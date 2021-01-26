#include "cos.h"

int sprawdz_wypelnione(maciora *m)
{
    int j, i;
    i = 0;
    j = 0;
    for (i; i < m->r; i++)
    {
        for (j; j < m->c; j++)
        {
            if (m->tab[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

int check_border(maciora *m)
{

    for (int i = 0; i < m->c; i++)
    {
        if (m->tab[0][i] != 1)
            return 0;
        if (m->tab[m->r-1][i] != 1)
            return 0;
    }
    for (int i = 0; i < m->r; i++)
    {
        if (m->tab[i][0] != 1)
            return 0;
        if (m->tab[i][m->c-1] != 1)
            return 0;
    }
    return 1;
}

int can_I_go(maciora *m)
{
    printf("zwrot lufy: %d\n",m->zwrot_lufy);

    if (m->zwrot_lufy == 1)
    {
        printf("sprawdzam pole x:%d y:%d\n",m->my_r ,m->my_c+1);
        if (m->tab[m->my_r][m->my_c+1] == 1)
            return 0;
        else
            return 1;
        ;
    }
    if (m->zwrot_lufy == 2)
    {
        printf("sprawdzam pole x:%d y:%d\n",m->my_r+1,m->my_c);
        if (m->tab[m->my_r+1][m->my_c] == 1)
            return 0;
        else
            return 1;
    }
    if (m->zwrot_lufy == 3)
    {
        printf("sprawdzam pole x:%d y:%d\n",m->my_r+2,m->my_c+1);
        if (m->tab[m->my_r + 2][m->my_c+1] == 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (m->zwrot_lufy == 4)
    {
        printf("sprawdzam pole x:%d y:%d\n",m->my_r+1,m->my_c+2);
        if (m->tab[m->my_r+1][m->my_c + 2] == 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int check_front(maciora *m, Dane *D)
{
    if (m->zwrot_lufy == 1)
    {
        if (m->tab[m->my_r - 1][m->my_c - 1] != 1)
        {
            if (m->tab[m->my_r - 1][m->my_c + 1] == 1)
                return 1;
            else
                return 2;
        }
        else
        {
            if (m->tab[m->my_r][m->my_c - 1] == 1)
                return 4;
            else
                return 3;
        }
    }
    if (m->zwrot_lufy == 2)
    {
        if (m->tab[m->my_r][m->my_c - 1] != 1)
        {
            if (m->tab[m->my_r - 1][m->my_c - 1] == 1)
                return 1;
            else
                return 2;
        }
        else
        {
            if (m->tab[m->my_r + 1][m->my_c] == 1)
                return 4;
            else
                return 3;
        }
    }
    if (m->zwrot_lufy == 3)
    {
        if (m->tab[m->my_r + 1][m->my_c] != 1)
        {
            if (m->tab[m->my_r + 1][m->my_c - 1] == 1)
                return 1;
            else
                return 2;
        }
        else
        {
            if (m->tab[m->my_r][m->my_c + 1] == 1)
                return 4;
            else
                return 3;
        }
    }
    if (m->zwrot_lufy == 4)
    {
        if (m->tab[m->my_r][m->my_c + 1] != 1)
        {
            if (m->tab[m->my_r + 1][m->my_c + 1] == 1)
                return 1;
            else
                return 2;
        }
        else
        {
            if (m->tab[m->my_r - 1][m->my_c] == 1)
                return 4;
            else
                return 3;
        }
    }
}

int go_aroud(maciora *m, Dane *D, char *tok)
{

    if (check_front(m, D) == 1)
    {
        move(tok, m, D);
        explore(tok, m, D);
        info(tok, m, D);
    }
    if (check_front(m, D) == 2)
    {
        move(tok, m, D);
        rotate(tok, "left",m, D);
        explore(tok, m, D);
        info(tok, m, D);
    }
    if (check_front(m, D) == 3)
    {
        rotate(tok, "right",m, D);
        move(tok, m, D);
        explore(tok, m, D);
        info(tok, m, D);
    }
    if (check_front(m, D) == 4)
    {
        rotate(tok, "right",m, D);
        rotate(tok, "right",m, D);
        move(tok, m, D);
        rotate(tok, "right",m, D);
        info(tok, m, D);
    }
}

int have_you_been_here(maciora *m)
{
    if (m->zwrot_lufy == 1)
    {
        if (m->tab2[m->my_r - 1][m->my_c - 1] == 0)
            return 0;
        else
            return 1;
    }
    if (m->zwrot_lufy == 2)
    {
        if (m->tab2[m->my_r][m->my_c - 1] == 0)
            return 0;
        else
            return 1;
    }
    if (m->zwrot_lufy == 3)
    {
        if (m->tab2[m->my_r + 1][m->my_c] == 0)
            return 0;
        else
            return 1;
    }
    if (m->zwrot_lufy == 4)
    {
        if (m->tab2[m->my_r][m->my_c + 1] == 0)
            return 0;
        else
            return 1;
    }
}

void make_fram(maciora *m, Dane *D, char *tok)
{
    rotate(tok, "right",m, D);
    info(tok, m, D);
    explore(tok, m, D);
    int x = m->my_r;
    int y = m->my_c;
    printf("x %d   y%d\n", x, y);
    while (m->my_r != x)
    {
        while (m->my_c != y)
        {
            explore(tok, m, D);
            go_aroud(m, D, tok);
        }
        rotate(tok, "right",m, D);
    }
}

void algorytm_ruchu2(maciora*m,Dane*D,char*tok)
{

    info(tok,m,D);
    printf("my c  my r  %d  %d",m->my_c , m->my_r);
    /*while (check_border(m)!=1) 
    { ;     
        info(tok,m,D);
        explore(tok,m,D);
        pokaz_macierz(m);
        while (sprawdz_wypelnione(m)==0) 
        { 
            while (can_I_go(m)==1)
            {
                move(tok,m,D);
                info(tok,m,D);
                explore(tok,m,D);
            } 
                make_fram(m,D,tok);
    printf ("gotowe");
    }
    }*/
}
  
 /// łabądź 690224936
