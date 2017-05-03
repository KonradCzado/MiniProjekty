#include <stdio.h>
#include <stdlib.h>

int dlugosc(char* lan);

int sprawdz(char* tekst, char* wzor);

int* sprawdz_w(char* tekst, char* wzor, int* ilosc);

int main()
{

    char tekst[80];
    char wzor[80];
    int wynik = 1;
    int result = 0;
    int powtorzenia = 0;
    int i = 0;
    while(wynik)
    {
        fflush(stdin);
        printf("\nPodaj tekst: ");
        gets(tekst);
        fflush(stdin);
        printf("\nPodaj wzor: ");
        {
           gets(wzor);
        }

        wynik = sprawdz(tekst, wzor);
        int* wyniki = sprawdz_w(tekst, wzor, &powtorzenia);
        printf("Powtorzenia: %d", powtorzenia);
        for(i = 0 ; i<powtorzenia; i++)
        {
            printf("\nZnaleziony wzor zaczyna sie na indeksie: %d", wyniki[i]);
        }
        if(wynik != -1)
        {
            printf("\nZnaleziono wzorzec w tekscie na indeksie: %d", wynik);
            result++;
        }
    }

    if(result == 0)
    {
        printf("\nNie znaleziono wzorca!");
    }


    return 0;
}

int dlugosc(char* lan)
{
    int i = 0;
    while(*lan++)
    {
        i++;
    }

    return i;
}

int sprawdz(char* tekst, char* wzor)
{
    int dlugoscTekstu = dlugosc(tekst);
    int dlugoscWzoru = dlugosc(wzor);

    printf("%d", dlugoscWzoru);
    int i = 0;
    int j = 0;
    while(i<= dlugoscTekstu - dlugoscWzoru)
    {
        while((j< dlugoscWzoru) && (wzor[j] == tekst[i+j]))
        {
            j++;
        }
        if(j == dlugoscWzoru)
        {
            return i;
        }
        i++;
        printf("%d", i);
    }

    return -1;
}

int* sprawdz_w(char* tekst, char* wzor, int* ilosc)
{
    int wynik = 0;
    int w = 0;
    int* tabIndeksow = NULL;
    int dlugoscTekstu = dlugosc(tekst);
    int dlugoscWzoru = dlugosc(wzor);

    printf("%d", dlugoscWzoru);
    int i = 0;
    int j = 0;
    while(i<= dlugoscTekstu - dlugoscWzoru)
    {
        while((j< dlugoscWzoru) && (wzor[j] == tekst[i+j]))
        {
            j++;
        }
        if(j == dlugoscWzoru)
        {
            j = 0;
            wynik = wynik+1;
            tabIndeksow = realloc(tabIndeksow, wynik * sizeof(int));
            tabIndeksow[w++] = i;
        }
        i++;
      //  printf("%d", i);
    }
    *ilosc = wynik;
    return tabIndeksow;
}
