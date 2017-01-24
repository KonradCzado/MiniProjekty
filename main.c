#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student
{
    char imie[20];
    char nazwisko[30];
    int numer;
    double oceny[5];
    double srednia;
};

void wydruk(char* nazwa);
void dodaj(char* nazwa);
void popraw(char* nazwa);
void dodajtxt(char*nazwa);
struct Student* najlepsi(char* nazwa);
int usun(char* nazwa);
struct Student srednia(struct Student student);
int main(void)
{

    dodaj("dane.bin");
    dodaj("dane.bin");
    dodaj("dane.bin");
    popraw("dane.bin");
    if(usun("dane.bin"))
    {


        wydruk("dane.bin");
    }
    else
    {
        fprintf(stderr, "brak pliku do odczytu!");
    }
    struct Student* mistrzowie = najlepsi("dane.bin");


    return 0;
}
void dodaj(char* nazwa)
{
    FILE* plik;
    plik = fopen(nazwa, "a+b");
    int i;
    struct Student nowy;
    fflush(stdin);
    printf("Podaj imie: ");
    scanf("%19s", nowy.imie);
    fflush(stdin);
    printf("\nPodaj nazwisko: ");
    scanf("%29s", nowy.nazwisko);
    fflush(stdin);
    printf("\nPodaj numer w dzienniku: ");
    scanf("%d", &nowy.numer);
    fflush(stdin);
    for(i = 0 ; i<5; i++)
    {
        printf("\nPodaj ocene %d dla %s %s: ", i+1, nowy.imie, nowy.nazwisko);
        scanf("%lf", &nowy.oceny[i]);
        fflush(stdin);
    }
    nowy = srednia(nowy);
    fwrite(&nowy, sizeof(struct Student), 1, plik);
    fclose(plik);

}

struct Student srednia(struct Student student)
{
    int i;
    double suma = 0;
    for(i = 0; i<5; i++)
    {
        suma+= student.oceny[i];
    }

    student.srednia = suma/5;
    return student;
}
struct Student* najlepsi(char* nazwa)
{
    struct Student* Best = NULL;
    FILE*plik = fopen(nazwa, "rb");
    int i = 0;
    struct Student temp;
    while(fread(&temp, sizeof(struct Student), 1, plik) == 1)
    {
        if(temp.srednia >3.5)
        {
            i++;
        }
    }
    rewind(plik);
    Best = (struct Student*)malloc(i * sizeof(struct Student));
    i = 0;
    while(fread(&temp, sizeof(struct Student), 1, plik) == 1)
    {
        if(temp.srednia > 3.5)
        {
            Best[i] = temp;
            i++;
        }
    }
    fclose(plik);

    return Best;
}

int usun(char* nazwa)
{
    FILE* plik = fopen(nazwa, "rb");
    FILE* temp_f;
    temp_f = fopen("temp.bin", "wb");
    struct Student temp;
    int i = 0;
    while(fread(&temp, sizeof(struct Student),1, plik) == 1)
    {
        if(temp.srednia > 3.5)
        {
            i++;
            fwrite(&temp, sizeof(struct Student),1, temp_f);
        }
    }

    fclose(plik);
    fclose(temp_f);
    remove(nazwa);
    rename("temp.bin", nazwa);
    if(temp_f)
        return 1;
    return 0;

}
void wydruk(char* nazwa)
{
    FILE*plik = fopen(nazwa, "a+b");
    struct Student dane;
    while(fread(&dane, sizeof(struct Student), 1, plik) == 1)
    {
        printf("Imie: %s\n", dane.imie);
        printf("Nazwisko: %s\n", dane.nazwisko);
        printf("Srednia: %.2lf\n", dane.srednia);

    }

    fclose(plik);
}

void popraw(char* nazwa)
{
    FILE*plik = fopen(nazwa, "r+");
    struct Student dane;
    printf("\nPodaj imie osoby, ktorej dane chcesz zmienic");
    fflush(stdin);
    char imie[20];
    fflush(stdin);
    scanf("%19s", imie);
    while(fread(&dane, sizeof(struct Student), 1, plik) ==  1)
    {


        if(strcmp(imie, dane.imie) == 0)
        {
            fseek(plik, -(sizeof(struct Student)), SEEK_CUR);
            printf("Podaj nowe imie dla %s: ", dane.imie);
            fflush(stdin);
            scanf("%19s", dane.imie);
            fwrite(&dane, sizeof(struct Student),1, plik);
            fclose(plik);
        }

    }


}


