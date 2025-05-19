#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>

using namespace std;

FILE *file;
struct Film
{
    char judul[100];
    int tahunRilis;
    char genre[50];
    float rating;
    Film *kanan;
    Film *kiri;
};
Film *awal = nullptr;
Film *akhir = nullptr;

bool listKosong()
{
    return (awal == nullptr);
}

void sisipFilm(char judulBaru[100], int tahun, char genreBaru[50], float ratingBaru)
{

    Film *NB = new Film;
    strcpy(NB->judul, judulBaru);
    NB->tahunRilis = tahun;
    strcpy(NB->genre, genreBaru);
    NB->rating = ratingBaru;
    NB->kanan = nullptr;
    NB->kiri = nullptr;

    if (listKosong())
    {
        awal = NB;
        akhir = NB;
    }
    else if (tahun <= awal->tahunRilis)
    {
        NB->kanan = awal;
        awal->kiri = NB;
        awal = NB;
    }
    else
    {
        Film *bantu = awal;
        while (bantu->kanan != nullptr && tahun > bantu->kanan->tahunRilis)
        {
            bantu = bantu->kanan;
        }
        NB->kanan = bantu->kanan;
        if (bantu->kanan != nullptr)
        {
            bantu->kanan->kiri = NB;
        }
        else
        {
            akhir = NB;
        }
        NB->kiri = bantu;
        bantu->kanan = NB;
    }
}

int main (){


    return 0;
}